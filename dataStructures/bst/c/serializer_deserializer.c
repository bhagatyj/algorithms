#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


struct TreeNode {
 	int 	val;
 	struct TreeNode *left;
 	struct TreeNode *right;
};

typedef struct memo_t_ {
	struct memo_t_ *next;
	struct memo_t_ *prev;
	struct TreeNode *val;
} memo_t;

typedef struct memo_queue_t_ {
	memo_t *head;
	memo_t *tail;
} memo_queue_t;


struct TreeNode *makeNewNode( int value ) {
	struct TreeNode *t = (struct TreeNode *) malloc(sizeof(struct TreeNode));
	assert(t != NULL);
	t->val = value;
	t->left = NULL;
	t->right = NULL;
	return t;
}

memo_t *makeMemo( struct TreeNode *value ) {
	memo_t *m = (memo_t *)malloc(sizeof(memo_t));
	assert(m);
	m->val = value;
	m->next = NULL;
	return m;
}

void printNode(struct TreeNode *n) {
    printf("Value:%4d ", n->val);
    if (n->left) {
        printf("Left: %4d ", n->left->val);
    } else {
        printf("Left: Null ");
    }
    if (n->right) {
        printf("Right: %4d ", n->right->val);
    } else {
        printf("Right: Null ");
    }
    printf("\n");
}

void inOrder(struct TreeNode *root) {
    if(root != NULL) {
        inOrder(root->left);
        printNode(root);
        inOrder(root->right);
    }
}

void enqueue_memo_tail(memo_queue_t *q, memo_t *m) {
	m->prev = q->tail;
	m->next = NULL;
	if (q->head == NULL) {
		q->head = m;
		q->tail = m;
	} else {
		q->tail->next = m;
		q->tail = m;
	}
}

memo_t *dequeue_memo(memo_queue_t *q) {
	memo_t *tmp;
	if (q->head == NULL) {
		return NULL;
	}
	if (q->head == q->tail) {
		tmp = q->head;
		q->head = NULL;
		q->tail = NULL;
		return tmp;
	}
	tmp = q->head;
	q->head = q->head->next;
	return tmp;
}

bool empty_memo_queue(memo_queue_t *q) {
	if (q->head == NULL) {
		return true;
	} else {
		return false;
	}
}

void
print_memo_queue(memo_queue_t *q) {
	memo_t *tmp = q->head;

	printf("The Queue is \n");
	while (tmp) {
		printf(" memo %p \n", tmp);
		tmp = tmp->next;
	}
	
}
void queue_tester() {
	memo_queue_t *memo_queue;
	memo_queue = (memo_queue_t *)malloc(sizeof(memo_queue_t));
	memset(memo_queue, 0, sizeof(memo_queue_t));

	struct TreeNode *n = makeNewNode(5);
	memo_t *m1 = makeMemo(n);
	memo_t *m2 = makeMemo(n);
	memo_t *m3 = makeMemo(n);

	enqueue_memo_tail(memo_queue, m1);
	enqueue_memo_tail(memo_queue, m2);
	enqueue_memo_tail(memo_queue, m3);
	print_memo_queue(memo_queue);
	memo_t *mx = dequeue_memo(memo_queue);
	printf("Dequeued %p\n", mx);

	print_memo_queue(memo_queue);
}

struct TreeNode *
deserialize( char *src ) {

	char *word, *data;
	int value;
	struct TreeNode *root;
	memo_queue_t *memo_queue;

	data = strdup(src);
	memo_queue = (memo_queue_t *)malloc(sizeof(memo_queue_t));
	memset(memo_queue, 0, sizeof(memo_queue_t));
	word = strtok(data, ",");
	if ( sscanf(word, "%d", &value) ) {
		printf("Processing %s\n", word);
		root = makeNewNode(value);
		memo_t *m = makeMemo(root);
		enqueue_memo_tail(memo_queue, m);
	}

	while ( !empty_memo_queue(memo_queue) ) {
		memo_t *parent_memo = dequeue_memo(memo_queue);
		struct TreeNode *parent = parent_memo->val;
		word = strtok(NULL, ",");
		printf("Processing %s\n", word);
		if ( sscanf(word, "%d", &value) ) {	
			struct TreeNode *n = makeNewNode(value);
			memo_t *m = makeMemo(n);
			enqueue_memo_tail(memo_queue, m);
			parent->left = n;
		} else {
			parent->left = NULL;
		}

		word = strtok(NULL, ",");
		printf("Processing %s\n", word);
		if ( sscanf(word, "%d", &value) ) {	
			struct TreeNode *n = makeNewNode(value);
			memo_t *m = makeMemo(n);
			enqueue_memo_tail(memo_queue, m);
			parent->right = n;
		} else {
			parent->right = NULL;
		}
	}
	free(data);
	return root;
}

char *
serialize( struct TreeNode *root) {

	char *data, *start;
	struct TreeNode *n;
	memo_queue_t *memo_queue;

	start = data = (char *) malloc(256);
	memset(data, 0, 256);
	memo_queue = (memo_queue_t *)malloc(sizeof(memo_queue_t));
	memset(memo_queue, 0, sizeof(memo_queue_t));

	memo_t *m = makeMemo(root);
	enqueue_memo_tail(memo_queue, m);

	while ( !empty_memo_queue(memo_queue) ) {
		memo_t *parent_memo = dequeue_memo(memo_queue);
		struct TreeNode *parent = parent_memo->val;
		if ( parent ) {
			data += sprintf(data, "%d,", parent->val);
			memo_t *m = makeMemo(parent->left);
			enqueue_memo_tail(memo_queue, m);
			m = makeMemo(parent->right);
			enqueue_memo_tail(memo_queue, m);
		} else {
			data += sprintf(data, "N,");
		}
	}
	return start;
}

int
main() {

	char data[] = "1,2,3,N,N,4,5,N,N,6,7,N,N,N,N,";
	char *rslt;
	struct TreeNode *root;

	root = deserialize(data);
	printf("\nIn order traversal ...\n");
	inOrder(root);

	rslt = serialize(root);
	printf("Old: %s \n", data);
	printf("New: %s \n", rslt);
	printf("Comparison: %d\n", strcmp(data, rslt));
}
