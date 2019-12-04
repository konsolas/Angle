#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#include "angle.h"

int main() {
    using namespace ang::literals;
    using ang::angle;

    // Creating variables
    angle a = 10.0_deg;
    angle b = a - 20.0_deg;
    angle c = 20.0_deg - a;
    angle d = 1.0_rad + 57.2958_deg;

    std::cout << "a = " << a.degrees() << " deg" << std::endl; // a = 10 deg
    std::cout << "b = " << b.degrees() << " deg" << std::endl; // b = -10 deg
    std::cout << "c = " << c.degrees() << " deg" << std::endl; // c = 10 deg
    std::cout << "d = " << d.radians() << " rad" << std::endl; // d = 2 rad

    // Subtraction
    std::cout << "50.0 deg - 350.0 deg = " << (50.0_deg - 350.0_deg).degrees() << " deg" << std::endl; // 60 deg
    std::cout << "50.0 deg - 10.0 deg = " << (50.0_deg - 10.0_deg).degrees() << " deg" << std::endl; // 40 deg
    std::cout << "359.0 deg - 1.0 deg = " << (359.0_deg - 1.0_deg).degrees() << " deg" << std::endl; // -2 deg

    // Comparisons
    std::cout << "50.0 deg > 30.0 deg = " << (50.0_deg > 30.0_deg) << std::endl; // 1 (true)
    std::cout << "57.0 deg <= 1.0 rad = " << (57.0_deg <= 1.0_rad) << std::endl; // 1 (true)

    // Standard algorithms
    std::cout << "std::max(60.0 deg, 1 rad) = "
              << std::max(60.0_deg, 1.0_rad).radians() << " rad" << std::endl; // 1.01229 rad

    // Containers
    std::vector<angle> angles = {38.0_deg, 12.0_rad, 3.2_deg, 176.0_deg, -2.3_rad, -180.0_deg};
    std::transform(angles.begin(), angles.end(), angles.begin(), [](auto angle) { return angle + 1.0_deg; });

    std::cout << "angles:";
    for (auto val : angles) std::cout << ' ' << val.degrees() << " deg";
    std::cout << std::endl;

    // Sorting
    std::sort(angles.begin(), angles.end());

    std::cout << "sorted angles:";
    for (auto val : angles) std::cout << ' ' << val.radians() << " rad";
    std::cout << std::endl;

    // Midpoint of two angles
    angle e = 359.0_deg;
    angle f = 1.0_deg;
    std::cout << "(e + f) / 2 = " << ((e + f) / 2.0).degrees() << " deg" << std::endl; // 0 deg

    return 0;
}
