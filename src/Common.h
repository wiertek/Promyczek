#ifndef COMMON_H
#define COMMON_H

#include <limits>
#include <random>

namespace Consts {

const double Infinity = std::numeric_limits<double>::infinity();
const double Pi = 3.1415926535897932385;

} // namespace Consts

inline double degreesToRadians(double degrees) {
    return degrees * Consts::Pi / 180.0;
}

inline double randomDouble(double min = 0.0, double max = 1.0) {
    double range = max - min;
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    auto result = distribution(generator);
    return result * range + min;
}

#endif