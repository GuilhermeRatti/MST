#include <stdio.h>

void printBits(unsigned int num) {
    for (int bit = 0; bit < (sizeof(unsigned int) * 8); ++bit) {
        printf("%u ", num & 0x01); // Print the last bit and shift right.
        num >>= 1;
    }
}

int main(int argc, char const *argv[])
{
    printBits(32<<16);
    return 0;
}
