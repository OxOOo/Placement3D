#include "solution.h"

#include <algorithm>

using namespace std;

Box Solution::GetBoundingBox()
{
    if (bounding_box.Volume()) return bounding_box;
    if (!Size()) return Box();
    int l = 1e9, f = 1e9, d = 1e9;
    int r = -1e9, b = -1e9,u = -1e9;
    for (auto box : boxes)
    {
        l = min(l, box.x), f = min(f, box.y), d = min(d, box.z);
        r = max(r, box.x2), b = max(b, box.y2), u = max(u, box.z2);
    }
    return bounding_box = Box(r - l, b - f, u - d);
}

int Solution::GetBoxesVolume()
{
    if (total_vol) return total_vol;
    for (auto box : boxes) total_vol += box.Volume();
    return total_vol;
}

bool Solution::Check()
{
    // FIXME TODO this function is wrong when boxes are contained
    // FIXME if more efficient method exists
    for (auto box1 = boxes.begin(); box1 != boxes.end(); ++box1)
        for (auto box2 = boxes.begin(); box2 != boxes.end(); ++box2)
        {
            if (box1 == box2) continue;
            if (pointInBox(box1->x,  box1->y,  box1->z,  box2)) return 0;
            if (pointInBox(box1->x,  box1->y,  box1->z2, box2)) return 0;
            if (pointInBox(box1->x,  box1->y2, box1->z,  box2)) return 0;
            if (pointInBox(box1->x,  box1->y2, box1->z2, box2)) return 0;
            if (pointInBox(box1->x2, box1->y,  box1->z,  box2)) return 0;
            if (pointInBox(box1->x2, box1->y,  box1->z2, box2)) return 0;
            if (pointInBox(box1->x2, box1->y2, box1->z,  box2)) return 0;
            if (pointInBox(box1->x2, box1->y2, box1->z2, box2)) return 0;
        }
    return 1;
}

bool Solution::pointInBox(int x, int y, int z, const PlacedBoxList::iterator& box)
{
    return x > box->x && x < box->x2 &&
           y > box->y && y < box->y2 &&
           z > box->z && z < box->z2;
}

Solution Solution::LoadSolutionFromFile(const string& fileName)
{
    FILE* fin  = fopen(fileName.c_str(), "r");
    Solution sol;
    int n;

    if (!fin)
    {
        printf("ERROR: NO such file '%s'\n", fileName.c_str());
        return sol;
    }

    fscanf(fin, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x, y, z, l, w, h;
        fscanf(fin, "%d%d%d", &x, &y, &z);
        fscanf(fin, "%d%d%d", &l, &w, &h);
        sol.Add(x, y, z, l, w, h);
    }
    fclose(fin);

    return sol;
}

void Solution::SaveToFile(const string& fileName) const
{
    FILE* fout;
    if (!fileName.length())
        fout = stdout;
    else
        fout = fopen(fileName.c_str(), "w");

    fprintf(fout, "%d\n", Size());
    for (auto it = BoxesBegin(); it != BoxesEnd(); ++it)
    {
        fprintf(fout, "%d %d %d  ", it->x, it->y, it->z);
        fprintf(fout, "%d %d %d\n", it->l, it->w, it->h);
    }
    if (fout != stdout) fclose(fout);
}
