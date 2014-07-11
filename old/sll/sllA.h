#include <stdio.h>

/* Node Structure for Single Link List
 * Flags indicate various operational information
 * For example, did the library create the data or
 * is it holding the data created by someone-else.
 * redZone & magic are for sanity checks.
*/
typedef struct sllANode_ {
	struct sllANode 	*next;
	unsigned int		magic;
	unsigned int		flags;
	void 				*data;
	unsigned int		redZone;
} sllANode;

typedef struct sllAList_ {
	struct sllANode 	*next;
} sllAList;

sllAList * createSllA(void);

/*
 * API for SLL Node Creation
 */
int createSllANode(void *data);

/* 
 * API for SLL Node addition to SLL List
 * 
 * addtoSll - Adds node to SLL
 * Returns 0 on success
 */
int addNodeToSllA(sllAList *list, sllANode *node);
int addDataToSllA(sllAList *list, void *data, unsigned int flags, int size);

/*
 * API for Removal of SLL Node from an SLL List.
 */
int removeNodeFromSllA(sllAList *list, sllANode *node);

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
void deleteSllANode(sllANode *node);
/* 
 * Delete the SLL List
 */
void deleteSllAList(sllAList *list);

/* 
 * Iterate through the SLL List using a function that operates on data.
 */

//#define forEach(var, list)