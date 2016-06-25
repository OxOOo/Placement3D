#ifndef BOX_H
#define BOX_H

#include <vector>

class Box
{
public:
    Box() : l(0), w(0), h(0) {}
    Box(int l, int w, int h) : l(l), w(w), h(h) {}

    /// 长，宽，高
    int l, w, h;

    int Volume() { return l * w * h; }
};
typedef std::vector<Box> BoxList;


class PlacedBox: public Box
{
public:
    PlacedBox() : Box(), x(0), y(0), z(0), x2(0), y2(0), z2(0) {}
    PlacedBox(int x, int y, int z, int l, int w, int h)
        : Box(l, w, h), x(x), y(y), z(z), x2(x + l), y2(y + w), z2(z + h) {}
    PlacedBox(int x, int y, int z, Box box)
        : Box(box.l, box.w, box.h), x(x), y(y), z(z), x2(x + box.l), y2(y + box.w), z2(z + box.h) {}

    /// 左前下角坐标
    int x, y, z;

    /// 右后上角坐标
    int x2, y2, z2;

    void SetBox(Box box) {
        l = box.l;
        w = box.w;
        h = box.h;
    }
    void SetXYZ(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void Solve2() {
        x2 = x + l;
        y2 = y + w;
        z2 = z + h;
    }
};
typedef std::vector<PlacedBox> PlacedBoxList;


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

    /// length(X), width(Y) and height(Z)

    PlacedBoxList::iterator BoxesBegin() { return boxes.begin(); }
    PlacedBoxList::iterator BoxesEnd() { return boxes.end(); }

private:
    PlacedBoxList boxes;
    int vol, total_vol;
    Box bounding_box;
};

#endif // BOX_H
