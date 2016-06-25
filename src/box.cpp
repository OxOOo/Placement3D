#include "box.h"

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
    for (auto box : boxes)
        total_vol += box.l * box.w * box.h;
    return total_vol;
}
