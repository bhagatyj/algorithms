#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

using namespace std;


class Tree {
	vector<int>  __store;
	int __size;
	int __numLevels;

	public:
	Tree( int level);
	void print( void );
	void set_bits( int offset, int length);
	void clear_bits( int offset, int length);
};

Tree::Tree( int level ) {
	__numLevels = level;
	__size = std::pow(2, level) - 1;
	__store.resize(__size);
	
	for (auto i=0; i<__size; i++) {
		__store[i] = 0;
	}
}

void 
Tree::print( void ) {

	unsigned i, level, nodesOnLevel;

	level = 0; nodesOnLevel = 0;
	for (i=0; i< __size; i++) {
		cout << __store[i];
		nodesOnLevel++;
		if ( nodesOnLevel == pow(2, level) ) {
			cout << endl;
			level++;
			nodesOnLevel = 0;
		}
	}
	cout << endl;
}

void
Tree::set_bits( int offset, int length) {
	unsigned end = offset + length;
	assert( offset + length - 1  < __size );
	while ( offset < end ) {
		__store[offset] = 1;
		if ( 2*offset + 1 < __size ) {
			set_bits( 2*offset+1, 1);
		} 
		if ( 2*offset + 2 < __size ) {
			set_bits( 2*offset+2, 1);
		}
		offset++;
	}
}

void
Tree::clear_bits( int offset, int length ) {

	assert( offset + length - 1 < __size );
	cout << "offset: "<< offset << " length: " << length << endl;

	// Start from the end. This implies that we can 
	// stop if we hit a zero.
	unsigned end = offset;
	offset += length - 1;
	while ( offset >= end ) {
		__store[offset] = 0;
		if ( offset == 0 ) {
			return;
		} else {
			clear_bits( (offset - 1 ) / 2, 1 );
			offset--;
		}
	}
}

int main() {

	Tree t(4);

	t.set_bits(0, 1);
	t.print();
	t.clear_bits(14, 1);
	t.print();
	t.clear_bits(10, 1);
	t.print();
	t.set_bits(2, 1);
	t.print();

}
