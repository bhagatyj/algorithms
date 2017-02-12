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
#include <linux/kthread.h>

static char my_devname[]= "poll_dev"; // appears in /proc/devices

static struct device *poll_cdev;
static struct class *poll_class;
int poll_minor_base=1;

static DECLARE_WAIT_QUEUE_HEAD(workQ); // Wait queue head for read event 

//......................................................

static struct file_operations fops = {
	owner:   THIS_MODULE,
};

static		 dev_t   dev;
static struct cdev	*my_cdev;
struct task_struct *my_thread = NULL;
static int my_thread_fn(void * data);
unsigned int wait_major;
unsigned int wait_minor;

unsigned long long 
timespec_delta(struct timespec *t1, struct timespec *t2) {
	unsigned long long delta;

	delta = (t2->tv_sec - t1->tv_sec) * 1000 * 1000 * 1000;
	delta += (t2->tv_nsec - t1->tv_nsec);
	return delta;
}

void yield_for_nsecs( unsigned long long yield_time ) {
	struct timespec start, stop;
	static unsigned long count = 0;

	set_current_state(TASK_INTERRUPTIBLE);
	getnstimeofday(&start);
	getnstimeofday(&stop);
	while ( timespec_delta(&start, &stop) < yield_time ) {
		yield();
		getnstimeofday(&stop);
	}

	count++;
	if ( count == 1000000 ) {
		printk(" byjt....>>> sleep : %llu \n", timespec_delta(&start, &stop) );
		count = 0;
	}

}

static int my_counter;

void work(void) {
	int i;
	for (i=0; i<100000; i++) {
		my_counter++;
	}
}

void work_for_nsecs( unsigned long long yield_time ) {
	struct timespec start, stop;
	static unsigned long count = 0;

	set_current_state(TASK_INTERRUPTIBLE);
	getnstimeofday(&start);
	getnstimeofday(&stop);
	while ( timespec_delta(&start, &stop) < yield_time ) {
		work();
		getnstimeofday(&stop);
	}

	count++;
	if ( count == 1000000 ) {
		printk(" byjt....>>> work : %llu \n", timespec_delta(&start, &stop) );
		count = 0;
	}

}

int
my_thread_fn( void *data ) {

	printk(" byjt....>>> start :  \n");
	while (1) {
		yield_for_nsecs(200);
		work_for_nsecs(800);
		if ( unlikely(kthread_should_stop())) {
			return 0;
		}
	}

}
static int __init my_init(void)
{
	int res=0, major; 

	struct timespec start, stop;
	getnstimeofday(&start);
	getnstimeofday(&stop);
	while ( stop.tv_nsec - start.tv_nsec < 1000 ) {
			getnstimeofday(&stop);
	}
	printk(" byj....>>> successive clock time diff : %lu \n", stop.tv_nsec - start.tv_nsec);

	getnstimeofday(&start);
	sema_init(&sema,1); 
	getnstimeofday(&stop);
	printk(" byj....>>> sema init clock time diff : %lu \n", stop.tv_nsec - start.tv_nsec);

	getnstimeofday(&start);
	spin_lock_init(&lock);
	getnstimeofday(&stop);
	printk(" byj....>>> spinlock init clock time diff : %lu \n", stop.tv_nsec - start.tv_nsec);

	poll_class = class_create(THIS_MODULE, "poll_class");
	res = alloc_chrdev_region(&dev, poll_minor_base, 1, my_devname);
	if (res<0) { 
		return res; 
	}
	getnstimeofday(&start);
	printk(" byj....>>> clock time : %lu %lu \n", start.tv_sec, start.tv_nsec);

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
	getnstimeofday(&start);
	printk(" byj....>>> clock time : %lu %lu \n", start.tv_sec, start.tv_nsec);
	/* initialize use count */
	use_count = 0;
	printk(" %s init - major: %d  \r\n", my_devname, major);

	poll_cdev = device_create(poll_class, NULL, dev, NULL, "poll_dev");
	if (IS_ERR_OR_NULL(poll_cdev)) {
		pr_err("%s:%d error code %lu\n", __func__, __LINE__, PTR_ERR(poll_cdev));
	} else {
		printk("successfully created poll device %p %p \n", poll_cdev, poll_cdev->of_node);
	}
	getnstimeofday(&start);
	printk(" byj....>>> clock time : %lu %lu \n", start.tv_sec, start.tv_nsec);

	my_thread = kthread_create_on_node(my_thread_fn, 
							(void *)NULL, cpu_to_node(0), "myThread");
	printk(" byj...>> thread >> %p \n", my_thread);
	kthread_bind(my_thread, 0);
	wake_up_process(my_thread);
	return res;
}

static void __exit my_exit(void)
{
	struct timespec start;
	getnstimeofday(&start);
	printk(" byj....>>> clock time : %lu %lu \n", start.tv_sec, start.tv_nsec);

	if ( my_thread ) {
		kthread_stop(my_thread);
	}
	device_destroy(poll_class, dev);
	getnstimeofday(&start);
	printk(" byj....>>> clock time : %lu %lu \n", start.tv_sec, start.tv_nsec);
	class_destroy(poll_class);
	getnstimeofday(&start);
	printk(" byj....>>> clock time : %lu %lu \n", start.tv_sec, start.tv_nsec);
	cdev_del(my_cdev);
	getnstimeofday(&start);
	printk(" byj....>>> clock time : %lu %lu \n", start.tv_sec, start.tv_nsec);
	unregister_chrdev_region(dev, 1);
	printk(" %s remove \r\n", my_devname);

	getnstimeofday(&start);
	printk(" byj....>>> clock time : %lu %lu \n", start.tv_sec, start.tv_nsec);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Bhagat Jana");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Description");

