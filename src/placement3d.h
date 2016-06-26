#ifndef PLACEMENT_3D_H
#define PLACEMENT_3D_H

#include "box.h"
#include "solution.h"

class Placement3D
{
public:
    Placement3D(const BoxList& boxes);
    ~Placement3D();

    /// Get a placement solution
    Solution GetSolution()
    {
        solve();
        return sol;
    }

private:
    const int n;
    BoxList boxes;
    Solution sol;

    /// Solve the 3D Placement Problem use Simulated Annealing + T-tree
    void solve();
};

#endif // PLACEMENT_3D_H
