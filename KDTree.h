#ifndef KDTREE_H
#define KDTREE_H
#include "Point3D.h"
#include "rangeQuery.h"
#include <vector>
class KDTree{
public:
    class KDNode{
    public:
        Point3D* point;
        int axis;
        double value;
        KDNode* right;
        KDNode* left;
        KDNode(Point3D* pt, int axis);
    };

    KDTree();
    ~KDTree();
    void add(Point3D* p);
    KDNode* root() const;
    void RangeQuery(const Point3D& p, double eps, std::vector<Point3D*>& neighbors, KDNode* node) const;
    KDNode* buildBalanced(std::vector<Point3D*>& points, int depth);
    void build(std::vector<Point3D*>& points);

private:
    KDNode* rootNode;
    KDNode* insert(const Point3D* p, KDNode* node, int axis);
    void freeNode(KDNode* node);
};
#endif