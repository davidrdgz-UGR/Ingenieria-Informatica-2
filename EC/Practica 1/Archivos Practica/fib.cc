#include <iostream>

unsigned fib(unsigned n)
{
    std::cout << "fib(" << n << ")" << std::endl;
    if (n < 2)
        return n;
    else
        return fib(n - 2) + fib(n - 1);
}

int main(int argc, char *argv[])
{
    return fib(argc + 3);
}
