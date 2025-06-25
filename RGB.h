#ifndef RGB_H
#define RGB_H
#include <string>

class RGB {
public:
    double r, g, b;
    RGB();
    std::string toString() const;
};

#endif