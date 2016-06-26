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

    /// Set if debug
    void SetDebug() { is_debug = true; }

    /// Set Status Factor
    void SetStatusFactor(double k) { status_factor = k; }

    /// Set volume factor
    void SetVolumeFactor(double k) { volume_factor = k; }

    /// Set lowest temperature
    void SetLowestTemperature(double k) { lowest_temperature = k; }

    /// Set temperature down factor
    void SetTemperatureDownFactor(double k) { temperature_down_factor = k; }

private:
    const int n;
    BoxList boxes;
    Solution sol;

    bool is_debug;
    double status_factor;
    double volume_factor;
    double lowest_temperature;
    double temperature_down_factor;

    /// Solve the 3D Placement Problem use Simulated Annealing + T-tree
    void solve();
};

#endif // PLACEMENT_3D_H
