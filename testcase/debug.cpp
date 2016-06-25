#include "placement3d.h"
#include "bttree.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
    BoxList temp;
    BTTree T(temp);
    T.Debug();

    return 0;
}
