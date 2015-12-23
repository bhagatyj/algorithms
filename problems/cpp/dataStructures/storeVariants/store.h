#ifndef __STORE_H__
#define __STORE_H__

#include <iostream>

using std::string;

class Node {
protected:
	int __key;
	string __data;
public:
	Node(int key, string data);
	void update( string data);
};




class Store {
    protected:
        string type;
        int    count;

    public:
        virtual int add ( int key, string data) = 0;
        virtual string get( int key ) = 0;
        virtual int remove( int key ) = 0;
        virtual void print( void ) = 0;
};

#endif
