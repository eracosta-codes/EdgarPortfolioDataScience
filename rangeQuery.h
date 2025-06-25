#ifndef RANGEQUERY_H
#define RANGEQUERY_H
#include "Point3D.h"
#include <vector>

class KDTree;
class RangeQuery{
    public:
        std::vector<Point3D> DB;
        RangeQuery(const std::vector<Point3D>& list);
        std::vector<Point3D*> RangeQueryMethod(const Point3D& p, double eps) const;
        ~RangeQuery();
    private:
        KDTree* KdTree;
};

#endif