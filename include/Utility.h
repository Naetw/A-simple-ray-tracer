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

/// Return a random real in [min, max)
double getRandomDoubleInRange(double min, double max);

/// Clamp value x into range [min, max]
double clamp(double x, double min, double max);

/// Convert degrees into radians
double convertDegreeIntoRadian(double degrees);

#endif
