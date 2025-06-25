#ifndef POINT3D_H
#define POINT3D_H
#include <cmath>         
#include <sstream>

class Point3D{
private:
    int cluster;
    double x, y, z;
public:
    Point3D(double x_, double y_, double z_);

    double get(int axis) const;

    double getX() const;
    double getY() const;
    double getZ() const;
    int getCluster() const;

    void setCluster(int label);
    double distance(const Point3D& pt) const;
    std::string toHumanString() const;
    std::string toString() const;
};
#endif