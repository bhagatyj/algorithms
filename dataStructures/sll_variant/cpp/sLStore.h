#ifndef __SLSTORE_H__
#define __SLSTORE_H__

#include "store.h"

using std::string;

class SLNode : public Node {
private:
	SLNode  *__next;

public:
	SLNode( int key, string data, SLNode *next );
	friend class SLStore;
};



class SLStore : public Store {
protected:
	SLNode *head;

public:
    SLStore();
    int add ( int key, string data);
    string get( int key );
    int remove( int key );
    void print( void );
    SLNode * find ( int key);
};

#endif