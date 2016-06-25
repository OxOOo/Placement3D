#ifndef SOLUTION_H
#define SOLUTION_H

#include "box.h"

class Solution
{
public:
    Solution() : vol(0), total_vol(0), bounding_box() {}

    int Size() { return boxes.size(); }

    void Add(PlacedBox& box) { boxes.push_back(box); }
    void Add(int x, int y, int z, int l, int w, int h) { boxes.push_back(PlacedBox(x, y, z, l, w, h)); }

    /// Get the bounding box after placement
    Box GetBoundingBox();

    /// Get total volume of boxes
    int GetBoxesVolume();

    /// Get volume of the bounding box
    int GetBoundingBoxVolume() { return vol ? vol : vol = GetBoundingBox().Volume(); }

    /// Get the wasted volume, = GetBoundingBoxVolume() – GetBoxesVolume()
    int GetWastedVolume() { return GetBoundingBoxVolume() - GetBoxesVolume(); }

    /// Get wasted volume ratio, = getWastedVolume() / GetBoundingBoxVolume()
    double GetWastedVolumeRatio()
    {
        GetBoundingBoxVolume();
        return vol ? 1.0 * GetWastedVolume() / vol : 0;
    }

    /// Check if valid
    bool Check();

    /// Iterators of boxes
    PlacedBoxList::iterator BoxesBegin() { return boxes.begin(); }
    PlacedBoxList::iterator BoxesEnd() { return boxes.end(); }

private:
    PlacedBoxList boxes;
    int vol, total_vol;
    Box bounding_box;
};

#endif // SOLUTION_H
