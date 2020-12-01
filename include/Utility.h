#ifndef RAYTRACER_UTILITY_H
#define RAYTRACER_UTILITY_H

#include <limits>

// ============================
// > Constants
// ============================
const double kInfinity = std::numeric_limits<double>::infinity();

// ============================
// > Helper functions
// ============================
/// Return a random real in [0,1).
double getRandomDouble01();

/// Clamp value x into range [min, max]
double clamp(double x, double min, double max);

#endif
