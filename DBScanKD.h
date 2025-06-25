#ifndef DBSCANKD_H
#define DBSCANKD_H
#include <cmath>         // for math functions
#include <vector>        // for dynamic arrays
#include <functional>    // for std::function and comparators
#include <unordered_map> // for hash maps
#include <map>           // for sorted maps
#include <set>           // for sets
#include <stack>         // for stacks
#include <random>        // for random number generation
#include <sstream>
#include "KDTree.h"
#include "NearestNeighboursKD.h"
#include "rangeQuery.h"
#include "Point3D.h"
#include "RGB.h"

class DBScanKD : public NearestNeighboursKD{
public:
    int c;
    double eps;
    double minPts;
    std::stack<Point3D*> s;
    std::unordered_map<int, int> clusterCounter;
    std::unordered_map<int, RGB> clusterColor;
    int noiseCounter;
    DBScanKD(const std::vector<Point3D>& list);
    double setEps(const double eps);
    double setMinPts(const double minPts);
    void findClusters();
    int getNumberOfClusters();
    std::vector<Point3D> getPoints();
    static std::vector<Point3D> read(const std::string& filename);
    int getSize();
    void printStats();
    void generateStats();
    void save(const std::string& filename);
private:
    void addToCluster(int cluster);
};

#endif