/* Sample code fragments and template for Assignment 1 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h> 
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/tty.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/device.h>

static char my_devname[]= "poll_dev"; // appears in /proc/devices

#define  N 23
static char rbuf[N+1];  // You can also use kmalloc() memory for your device 
static int  use_count;
static int  ir, iw;
static spinlock_t lock;
static struct device *poll_cdev;
static struct class *poll_class;
int poll_minor_base=1;

#define DEV_MAJOR   249 // for static  major and minor device node 
#define DEV_MINOR   5

static DECLARE_WAIT_QUEUE_HEAD(readers_Q); // Wait queue head for read event 
static DECLARE_WAIT_QUEUE_HEAD(writers_Q); // Wait queue head for write event 
static struct semaphore sema;

static int is_buffer_empty(void)
{
   if (ir == iw)
      return 1;
   return 0;
}

static int is_buffer_full(void)
{
   if (iw > (ir + N) )
      return 1;
   return 0;
}

static unsigned int device_poll(struct file *filp, poll_table *wait)
{
   unsigned int mask=0;

   poll_wait(filp, &readers_Q, wait);
   poll_wait(filp, &writers_Q, wait);

   /* Serialize access */
   spin_lock(&lock);

   if (!is_buffer_empty()) {
      printk ("%s - POLLIN EVENT:ir=%d|iw=%d\n", my_devname,ir,iw);
      mask |= POLLIN | POLLRDNORM;  /* fd is readable */
   }

   if (!is_buffer_full()) {
      printk ("%s - POLLIN EVENT:ir=%d|iw=%d\n", my_devname,ir,iw);
      mask |= POLLOUT | POLLWRNORM;  /* fd is writeable */
   }

   spin_unlock(&lock);
   return mask;
}


static ssize_t device_read(struct file *filp, 
                           char *buffer, size_t len, loff_t *offs)
{
   unsigned int i=0;

   if (is_buffer_empty()) /* no data to read */
      if (filp->f_flags & O_NONBLOCK) 
         return -EAGAIN;

   wait_event_interruptible( readers_Q, (ir != iw) );

   if (is_buffer_empty()) /* no data to read */
      return -ERESTARTSYS;

   if (down_interruptible(&sema))
      return -ERESTARTSYS;

   while (i<len) {
      if (ir==iw) 
         break;
     put_user(rbuf[ir++], buffer++);
     i++; 
     if (ir==N)  // end of device, reset the ir pointer to begining
       ir=0;
  }
  printk("\n %s read - %d bytes \r\n", my_devname, i);
  up(&sema);

// add code to wake up writers. Writers are not blocked in this version 

  return i;
}

static ssize_t device_write(struct file *filp, 
                            const char *buffer, size_t len, loff_t *offs)
{

   unsigned int i=0;
   int ih;

   if (is_buffer_full()) 
      if (filp->f_flags & O_NONBLOCK)
         return -EAGAIN;
   
   wait_event_interruptible( writers_Q, (iw <= ir+N) );

   if (is_buffer_full()) 
      return -ERESTARTSYS;

   if (down_interruptible(&sema))  // serialize access to device 
      return -ERESTARTSYS;

  ih=ir-1; 
  if(ih<0) ih+=N;

   while(i<len){
      if (iw==ih) break;
      get_user(rbuf[iw++], buffer++);
      i++; 
      if (iw==N) iw=0;
  }

  printk(" %s write - %d bytes \r\n", my_devname, i);

  up(&sema);

  /* Wake up readers since device has atleast one byte of data*/
  if (i>0) wake_up_interruptible(&readers_Q);

  return i;
}

static int device_open(struct inode *inode, struct file *filp)
{
   int use;

   spin_lock(&lock);
   if( use_count == 0 )
   {
     ir=iw=0;
   }
   use_count++; use=use_count;
   spin_unlock(&lock);

   printk(" %s open - count: %d \r\n", my_devname, use);
   return 0;
}

static int device_release(struct inode *inode, struct file *filp)
{
   int use;

   spin_lock(&lock);
   use = --use_count;
   spin_unlock(&lock);
   
   printk(" %s close - count %d \r\n", my_devname, use);
   return 0;
} 

//......................................................

static struct file_operations fops = {
   owner:   THIS_MODULE,
   read:    device_read,       
   write:   device_write,
   poll:    device_poll,
   open:    device_open,
   release: device_release,
};

static        dev_t   dev;
static struct cdev   *my_cdev;

unsigned int wait_major;
unsigned int wait_minor;

static int __init my_init(void)
{
   int res=0, major; 

   sema_init(&sema,1); 
   spin_lock_init(&lock);

   poll_class = class_create(THIS_MODULE, "poll_class");
   res = alloc_chrdev_region(&dev, poll_minor_base, 1, my_devname);
   if (res<0) { 
      return res; 
   }

   major = MAJOR(dev);

   /* allocate cdev structure and point to our device fops*/
   my_cdev = cdev_alloc();
   cdev_init(my_cdev, &fops);
   my_cdev->owner = THIS_MODULE;

   /* connect major to cdev struct */
   res = cdev_add(my_cdev, dev, 1);
   if (res<0){
     unregister_chrdev_region(dev, 1);
     return res;
   }
   /* initialize use count */
   use_count = 0;
   printk(" %s init - major: %d  \r\n", my_devname, major);

   poll_cdev = device_create(poll_class, NULL, dev, NULL, "poll_dev");
   if (IS_ERR_OR_NULL(poll_cdev)) {
      pr_err("%s:%d error code %lu\n", __func__, __LINE__, PTR_ERR(poll_cdev));
   } else {
      printk("successfully created poll device %p %p \n", poll_cdev, poll_cdev->of_node);
   }

   return res;
}

static void __exit my_exit(void)
{
   device_destroy(poll_class, dev);
   class_destroy(poll_class);
   cdev_del(my_cdev);
   unregister_chrdev_region(dev, 1);
   printk(" %s remove \r\n", my_devname);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Bhagat Jana");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Description");

