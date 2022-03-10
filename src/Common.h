#ifndef COMMON_H
#define COMMON_H

#include <limits>

namespace Consts {

const double Infinity = std::numeric_limits<double>::infinity();
const double Pi = 3.1415926535897932385;

} // namespace Consts

inline double degreesToRadians(double degrees) {
    return degrees * Consts::Pi / 180.0;
}

#endif