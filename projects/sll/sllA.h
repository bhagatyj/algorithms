#include <stdio.h>

/* Node Structure for Single Link List
 * Flags indicate various operational information
 * For example, did the library create the data or
 * is it holding the data created by someone-else.
 * redZone & magic are for sanity checks.
*/
typedef struct sllNode_ {
	struct sllNode 	*next;
	unsigned int	magic;
	unsigned int	flags;
	void 			*data;
	unsigned int	redZone;
} sllNode;

typedef struct sllList_ {
	struct sllNode 	*next;
} sllList;

sllList * createSll(void);

/*
 * API for SLL Node Creation
 */
//int createSllNode (void *data, int size);
int createSllNode(void *data, unsigned int size);

/* 
 * API for SLL Node addition to SLL List
 * 
 * addtoSll - Adds node to SLL
 * Returns 0 on success
 */
int addNodeToSll(sllList *list, sllNode *node);
int addDataToSll(sllList *list, void *data, unsigned int flags, int size);

/*
 * API for Removal of SLL Node from an SLL List.
 */
int removeNodeFromSll(sllList *list, sllNode *node);

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
void deleteSllNode(sllNode *node);
/* 
 * Delete the SLL List
 */
void deleteSllList(sllList *list);

/* 
 * Iterate through the SLL List using a function that operates on data.
 */

//#define forEach(var, list)