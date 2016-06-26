#include "placement3d.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

const int MaxLen = 10;

BoxList getRandomBoxes(int n)
{
    BoxList boxes;
    for (int i = 0; i < n; ++i)
	{
		int a = rand() % MaxLen + 1;
		int b = rand() % MaxLen + 1;
		int c = rand() % MaxLen + 1;
		boxes.push_back(Box(a, b, c));
	}
    return boxes;
}

void test(int index, int n)
{
    int pid = fork();
    if (pid) {
        waitpid(pid, NULL, 0);
        return;
    }

    BoxList boxes = getRandomBoxes(n);
    Placement3D* p3d = new Placement3D(boxes);
    char buffer[1024];

    sprintf(buffer, "statistic/box%d.txt", index);
    Box::SaveBoxesToFile(buffer, boxes);

    int start_clock = clock();
	Solution solution = p3d->GetSolution();
    int end_clock = clock();
    double used_time = (end_clock - start_clock) / double(CLOCKS_PER_SEC);
    sprintf(buffer, "statistic/sol%d.txt", index);
    p3d->SaveSolutionToFile(buffer);

    Box boundingBox = solution.GetBoundingBox();

    sprintf(buffer, "statistic/rst%d.txt", index);
    FILE *fout = fopen(buffer, "w");
    printf("Used Time : %.3lf s\n", used_time);
    printf("Total number of boxes: %d\n", solution.Size());
    printf("Total volume of boxes: %d\n", solution.GetBoxesVolume());
    printf("Volume of bounding box: %d\n", solution.GetBoundingBoxVolume());
    printf("Wasted volume: %d\n", solution.GetWastedVolume());
    printf("Wasted volume ratio: %.3lf%%\n", solution.GetWastedVolumeRatio() * 100);

    fprintf(fout,"Used Time : %.3lf s\n", used_time);
    fprintf(fout,"Total number of boxes: %d\n", solution.Size());
    fprintf(fout,"Total volume of boxes: %d\n", solution.GetBoxesVolume());
    fprintf(fout,"Volume of bounding box: %d\n", solution.GetBoundingBoxVolume());
    fprintf(fout,"Wasted volume: %d\n", solution.GetWastedVolume());
    fprintf(fout,"Wasted volume ratio: %.3lf%%\n", solution.GetWastedVolumeRatio() * 100);

    fclose(fout);

    delete p3d;

    exit(0);
}

int main(int argc, char* argv[])
{
    srand(time(0));

#ifndef Linux
    system("md statistic");
#else
    system("mkdir -p statistic");
#endif

    //test(1, 2);
    //test(2, 5);
    //test(3, 8);
    //test(4, 10);
    //test(5, 15);
    //test(6, 18);
    //test(7, 20);
    //test(8, 25);
    test(9, 28);
    test(10, 30);
    test(11, 33);
    test(12, 37);

    return 0;
}
