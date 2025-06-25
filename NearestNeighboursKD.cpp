#include "NearestNeighboursKD.h"
#include "KDTree.h"
#include "rangeQuery.h"

NearestNeighboursKD::NearestNeighboursKD(const std::vector<Point3D>& list) : DB(list) {
    for (auto& p : DB) {
        DB_pointers.push_back(&p);  // pointer to object inside DB
    }
    for (auto* p : DB_pointers) {
        KdTree.add(p);
    }
}

std::vector<Point3D*> NearestNeighboursKD::RangeQuery(const Point3D& p, double eps) {
    std::vector<Point3D*> neighbors;
    this->KdTree.RangeQuery(p, eps, neighbors, this->KdTree.root());
    return neighbors;
}