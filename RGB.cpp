#include "RGB.h"
#include <random>
#include <sstream>

RGB::RGB() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.2, 0.8);
    r = dis(gen);
    g = dis(gen);
    b = dis(gen);
}

std::string RGB::toString() const {
    std::ostringstream oss;
    oss << r << "," << g << "," << b;
    return oss.str();
}