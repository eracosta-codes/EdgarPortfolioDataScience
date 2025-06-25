#include "KDTree.h"
#include <cmath>
#include <algorithm>

// -------- KDNode Implementation --------
KDTree::KDNode::KDNode(Point3D* pt, int axis)
    : point(pt), axis(axis), value(pt->get(axis)), left(nullptr), right(nullptr) {}


// -------- KDTree Constructor --------
KDTree::KDTree() : rootNode(nullptr) {}


// -------- KDTree Destructor --------
KDTree::~KDTree() {
    freeNode(rootNode);
}


// -------- Recursive Memory Cleanup --------
void KDTree::freeNode(KDNode* node) {
    if (!node) return;
    freeNode(node->left);
    freeNode(node->right);
    delete node;
}


KDTree::KDNode* KDTree::insert(const Point3D* p, KDTree::KDNode* node, int axis) {
    if (!node) {
        return new KDNode(const_cast<Point3D*>(p), axis);  // or modify KDNode to accept const* cleanly
    }

    if (p->get(axis) <= node->value) {
        node->left = insert(p, node->left, (axis + 1) % 3);
    } else {
        node->right = insert(p, node->right, (axis + 1) % 3);
    }
    return node;
}

// -------- Add a Point to the KDTree --------
void KDTree::add(Point3D* p) {
    rootNode = insert(p, rootNode, 0); // start with axis 0 (x)
}

void KDTree::build(std::vector<Point3D*>& points) {
    rootNode = buildBalanced(points, 0);
}

KDTree::KDNode* KDTree::buildBalanced(std::vector<Point3D*>& points, int depth) {
    if (points.empty()) return nullptr;

    int axis = depth % 3;

    std::sort(points.begin(), points.end(), [axis](Point3D* a, Point3D* b) {
    return a->get(axis) < b->get(axis);
    });

    size_t medianIndex = points.size() / 2;
    KDNode* node = new KDNode(points[medianIndex], axis);

    std::vector<Point3D*> left(points.begin(), points.begin() + medianIndex);
    std::vector<Point3D*> right(points.begin() + medianIndex + 1, points.end());

    node->left = buildBalanced(left, depth + 1);
    node->right = buildBalanced(right, depth + 1);

    return node;
}



// -------- Range Query --------
void KDTree::RangeQuery(const Point3D& p, double eps, std::vector<Point3D*>& neighbours, KDNode* node) const {
    if (!node) return;

    double dist = p.distance(*node->point);  // dereference pointer to call distance

    if (dist > 0 && dist < eps) {
        neighbours.push_back(node->point);  // push pointer (correct)
    }

    if (p.get(node->axis) - eps <= node->value) {
        RangeQuery(p, eps, neighbours, node->left);
    }
    if (p.get(node->axis) + eps > node->value) {
        RangeQuery(p, eps, neighbours, node->right);
    }
}


// -------- Return Root Node --------
KDTree::KDNode* KDTree::root() const {
    return rootNode;
}
