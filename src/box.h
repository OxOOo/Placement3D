#ifndef BOX_H
#define BOX_H

#include <vector>

class Box
{
public:
    /// 长，宽，高
    int l, w, h;
};
typedef std::vector<Box> BoxList;


class PlacedBox: public Box
{
public:
    /// 空间坐标
    int x, y, z;
};
typedef std::vector<PlacedBox> PlacedBoxList;


class Solution
{
public:

private:
    PlacedBoxList boxes;
};

#endif // BOX_H
