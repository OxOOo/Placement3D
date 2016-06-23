#ifndef PLACEMENT_3D_H
#define PLACEMENT_3D_H

#include "box.h"
#include "solution.h"

#include <cstdlib>
#include <string>
#include <vector>

class Placement3D
{
public:
    static BoxList LoadBoxesFromFile(const std::string& fileName);
    static bool SaveBoxesToFile(const std::string& fileName, const BoxList& boxes);

public:
    Placement3D(const BoxList &boxes);
    ~Placement3D();

    void Solve();

private:
    BoxList boxes;
    Solution sol;
};

#endif // PLACEMENT_3D_H
