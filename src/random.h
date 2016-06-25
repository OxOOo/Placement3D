#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>

class Random
{
public:
    static int rand()
    {
#ifdef WIN32
    return (rand() << 16) + rand();
#else
    return rand();
#endif
    }

    static int nextInt(int n) { return rand() % n; }

    static double nextDouble() { return 1.0 * rand() / (~0U); }
};

#endif // RANDOM_H
