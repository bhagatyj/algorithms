#include <iostream>
#include <string>

#define MAX_BUFFER_SIZE 8192

class LogBuffer {
private:
    char      *_bufPtr;
    unsigned  _size;
    unsigned  _head;
    unsigned  _tail;
    void move_head(unsigned size);
    void move_tail(unsigned size);

public:
    LogBuffer(int size=512);
    ~LogBuffer();
    void put (std::string line);
    void put (const char * line);
    void print( );
};




