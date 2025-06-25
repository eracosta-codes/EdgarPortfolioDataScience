#include "rangeQuery.h"
#include "KDTree.h"
#include "Point3D.h"
#include <vector>

RangeQuery::RangeQuery(const std::vector<Point3D>& list) {
    KdTree = new KDTree();
    
    DB = list;
    for (auto& p : DB) {
        KdTree->add(&p);
    }
}

std::vector<Point3D*> RangeQuery::RangeQueryMethod(const Point3D& p, double eps) const {
    std::vector<Point3D*> neighbours;    // <-- use pointers here!
    KdTree->RangeQuery(p, eps, neighbours, KdTree->root());
    return neighbours;
}

RangeQuery::~RangeQuery() {
    delete KdTree;
}