#include "Point3D.h"
#include <cmath>
#include <sstream>

Point3D::Point3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

double Point3D::get(int axis) const {
    if (axis == 0) return x;
    else if (axis == 1) return y;
    else return z;
}

double Point3D::getX() const{ return x;}
double Point3D::getY() const{ return y;}
double Point3D::getZ() const{ return z;}
int Point3D::getCluster() const{ return cluster;}

void Point3D::setCluster(int label){
    cluster = label;
}

double Point3D::distance(const Point3D& pt) const{
        double dx = x - pt.x;
        double dy = y - pt.y;
        double dz = z - pt.z;
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }

std::string Point3D::toHumanString() const{
    std::ostringstream oss;
    oss << "x: " << x << "y: " << y << "z: " << z;
    return oss.str();
}
std::string Point3D::toString() const{
    std::ostringstream oss;
    oss << x << "," << y << "," << z;
    return oss.str();
}