#include "sll.h"
#include <string.h>


sllList * createSll(void)
{
	return NULL;
}



/*
 * aPI for SLL Node Creation
 */
//int createSllNode (void *data, unsigned int flags, int size);
int createSllNode(void *data, unsigned int flags)
{
	return 0;
}

/* 
 * API for SLL Node addition to SLL List
 * 
 * addtoSll - Adds node to SLL
 * Returns 0 on success
 */
int addNodeToSll(sllList *list, sllNode *node)
{
	return 0;
}
int addDataToSll(sllList *list, void *data, unsigned int flags, int size)
{
	return 0;
}

/*
 * API for Removal of SLL Node from an SLL List.
 */
int removeNodeFromSll(sllList *list, sllNode *node)
{
	return 0;
}

/* 
 * Search for a particular node in a List using function that operates on data
 */

/* 
 * Get the 'n'-th node in a SLL List
 * Special cases: 
 *  - Get first,
 *  - Get last
 */

/*
 * Delete the SLL Node
 */
void deleteSllNode(sllNode *node)
{
	return;
}
/* 
 * Delete the SLL List
 */
void deleteSllList(sllList *list)
{
	return;
}

/* 
 * Iterate through the SLL List using a function that operates on data.
 */

//#define forEach(var, list)
