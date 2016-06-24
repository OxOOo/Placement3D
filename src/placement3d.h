#ifndef PLACEMENT_3D_H
#define PLACEMENT_3D_H

#include "box.h"

#include <string>
#include <vector>
#include <cstdlib>

class Placement3D
{
public:
    static BoxList LoadBoxesFromFile(const std::string& fileName);
    static Solution LoadSolutionFromFile(const std::string& fileName);
    static bool SaveBoxesToFile(const std::string& fileName, const BoxList& boxes);
    static bool SaveSolutionToFile(const std::string& fileName, const Solution& sol);

    Placement3D(const BoxList& boxes);
    ~Placement3D();

    /// Solve the 3D Placement Problem use Simulated Annealing + T-tree
    void Solve();

    /// Get a placement solution
    Solution GetSolution()
    {
        Solve();
        return sol;
    }

private:
    BoxList boxes;
    Solution sol;
};

#endif // PLACEMENT_3D_H
