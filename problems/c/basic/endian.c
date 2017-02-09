#include <stdio.h>

unsigned ChangeEndianness(unsigned value)
{   
    unsigned result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

int main() {
    printf("%x\n", ChangeEndianness(0x12345678));
}

