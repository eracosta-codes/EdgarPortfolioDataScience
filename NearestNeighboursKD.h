#ifndef NEARESTNEIGHBOURSKD_H
#define NEARESTNEIGHBOURSKD_H

#include "Point3D.h"
#include "KDTree.h"
#include <vector>

class NearestNeighboursKD {
public:
    NearestNeighboursKD(const std::vector<Point3D>& list);
    std::vector<Point3D*> RangeQuery(const Point3D& p, double eps);

protected:
    KDTree KdTree;
    std::vector<Point3D> DB;
    std::vector<Point3D*> DB_pointers;
};

#endif