#include "sllA.h"
#include <string.h>


sllAList * createSll(void)
{
	sllAList *list = malloc(sizeof(sllAList));
	return list;
}

/*
 * API for SLL Node Creation
 */
int createSllANode(void *data)
{
	sllA
	return 0;
}

/* 
 * API for SLL Node addition to SLL List
 * 
 * addtoSll - Adds node to SLL
 * Returns 0 on success
 */
int addNodeToSllA(sllAList *list, sllANode *node)
{
	return 0;
}
int addDataToSllA(sllAList *list, void *data, unsigned int flags, int size)
{
	return 0;
}

/*
 * API for Removal of SLL Node from an SLL List.
 */
int removeNodeFromSllA(sllAList *list, sllANode *node)
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
void deleteSllANode(sllANode *node)
{
	return;
}
/* 
 * Delete the SLL List
 */
void deleteSllAList(sllAList *list)
{
	return;
}

/* 
 * Iterate through the SLL List using a function that operates on data.
 */

//#define forEach(var, list)
