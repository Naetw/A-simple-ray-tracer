#include "Utility.h"

#include <ctime>
#include <random>

double clamp(double x, double min, double max) {
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

double getRandomDouble01() {
    static std::default_random_engine generator(time(NULL));
    static std::uniform_real_distribution<double> uniform(0.0, 1.0);
    return uniform(generator);
}

double getRandomDoubleInRange(double min, double max) {
    return min + (max - min) * getRandomDouble01();
}
