#include "logBuffer.h"

LogBuffer::LogBuffer( int size ) {
   _bufPtr =  new char [ size ];
   _size = size;
   _head = 0;
   _tail = 0;
}

LogBuffer::~LogBuffer() {
    delete _bufPtr;
}

void
LogBuffer::move_head( unsigned size ) {
    _head = ( _head + size ) % _size;
}

void
LogBuffer::move_tail( unsigned size ) {
    _tail = ( _tail + size ) % _size;
}

unsigned
LogBuffer::space_left( void ) {
    if ( _tail > _head ) {
        return ( _tail - _head );
    } else {
        return ( _size - _head + _tail );
    }
}
/*
 * Put is an interesting method. When the buffer has space for the 
 * new item, it needs to move only the head. But when the buffer 
 * does n't have enough space for the new item or it is already 
 * full, then the tail also needs to move.
 * 
 * If the buffer is already full, tail has to move the same distance
 * as head.
 *
 * If the buffer will become full, tail has to move less distance -
 * based on the space left.
 */
void
LogBuffer::put( std::string line )
{
    put( line.c_str() );
}

void
LogBuffer::put( const char *line ) {

    unsigned lineLen = strlen(line);
    unsigned copyLen, oldHead, remainLen;
    const char *startPos;

    // Copy till end and keep doing until line is done.
    oldHead = _head;
    remainLen = lineLen;
    copyLen  = std::min( _size - _head, remainLen );
    startPos = line;
    while (copyLen > 0 ) {
        memcpy( (_bufPtr+_head), startPos, copyLen );
        move_head( copyLen );
        remainLen -= copyLen;
        startPos += copyLen;
        copyLen = std::min( _size - _head, remainLen );
    }

    // If head moved over tail, 
    // move tail to head+1
    if ( ( _tail < oldHead ) && 
         ( _tail >= _head ) ) {
        _tail = ( _head + 1 ) % _size;
    }
    if ( lineLen > _size ) {
        _tail = ( _head + 1 ) % _size;
    }
}

using namespace std;
void
LogBuffer::print( ) {

    cout << "Head : " << _head << endl;
    cout << "Tail : " << _tail << endl;
    cout << "Size : " << _size << endl;

    if ( _tail == _head ) {
        cout << "Buffer is empty" << endl;
        cout << endl;
        return;
    } 
    char data[_size+1];
    unsigned len;

    memset(data, 0, _size);
    if ( _head > _tail ) {
        len = _head - _tail;
        strncpy(data, _bufPtr+_tail, len);
    } else {
        // First copy from tail to end
        len = _size - _tail;
        strncpy( data, _bufPtr + _tail, len );
        // Copy from start to head
        strncpy( data+len, _bufPtr, _head );
        len += _head;
    }
    cout << "Len : " << len << endl;
    cout << data << endl << endl;

    // Move the tail as we just printed out buffer contents
    _tail = _head;
}
