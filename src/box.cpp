#include "box.h"

#include <cstdio>

using namespace std;

BoxList Box::LoadBoxesFromFile(const string& fileName)
{
    FILE* fin  = fopen(fileName.c_str(), "r");
    BoxList boxes;
    int n;

    if (!fin)
    {
        printf("ERROR: NO such file '%s'\n", fileName.c_str());
        return boxes;
    }

    fscanf(fin, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        int l, w, h;
        fscanf(fin, "%d%d%d", &l, &w, &h);
        boxes.push_back(Box(l, w, h));
    }
    fclose(fin);

    return boxes;
}

void Box::SaveBoxesToFile(const string& fileName, const BoxList& boxes)
{
    FILE* fout  = fopen(fileName.c_str(), "w");

    int n = boxes.size();
    fprintf(fout, "%d\n", n);
    for (int i = 0; i < n; i++)
        fprintf(fout, "%d %d %d\n", boxes[i].l, boxes[i].w, boxes[i].h);
    fclose(fout);
}
