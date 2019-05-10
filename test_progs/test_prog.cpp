#include <iostream>
#include <unistd.h>

#define MICROSECONDS 1000000
int main(void) {
    std::cout << "Printing to stdout" << std::endl;
    usleep(5*MICROSECONDS);
    std::cout << "Printing to stdout after" << std::endl;
    return 0;
}