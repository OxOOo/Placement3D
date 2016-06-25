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
    for (auto box : boxes)
        total_vol += box.Volume();
    return total_vol;
}

bool Solution::Check()
{
	// FIXME if more efficient method exists
	for (auto box1 = boxes.begin(); box1 != boxes.end(); ++box1)
		for (auto box2 = boxes.begin(); box2 != boxes.end(); ++box2)
		{
			if (box1 == box2) continue;
			if (pointInBox(box1->x, box1->y, box1->z, box2)) return 0;
			if (pointInBox(box1->x, box1->y, box1->z + box1->h, box2)) return 0;
			if (pointInBox(box1->x, box1->y + box1->w, box1->z, box2)) return 0;
			if (pointInBox(box1->x, box1->y + box1->w, box1->z + box1->h, box2)) return 0;
			if (pointInBox(box1->x + box1->l, box1->y, box1->z, box2)) return 0;
			if (pointInBox(box1->x + box1->l, box1->y, box1->z + box1->h, box2)) return 0;
			if (pointInBox(box1->x + box1->l, box1->y + box1->w, box1->z, box2)) return 0;
			if (pointInBox(box1->x + box1->l, box1->y + box1->w, box1->z + box1->h, box2)) return 0;
		}
	return 1;
}

bool Solution::pointInBox(int x, int y, int z, PlacedBoxList::iterator box)
{
	if (x > box->x && x < box->x + box->l && y > box->y && y < box->y + box->w && z > box->z && z < box->z + box->h)
		return 1;
	return 0;
}
