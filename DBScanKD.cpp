#include "DBScanKD.h"
#include "NearestNeighboursKD.h"
#include <set>
#include <utility>
#include <fstream>
#include <iostream>
#include <cmath>         // for math functions
#include <vector>        // for dynamic arrays
#include <functional>    // for std::function and comparators
#include <unordered_map> // for hash maps
#include <map>           // for sorted maps
#include <set>           // for sets
#include <stack>         // for stacks
#include <random>        // for random number generation
#include <sstream>

DBScanKD::DBScanKD(const std::vector<Point3D>& list) : NearestNeighboursKD(list){
    s = std::stack<Point3D*>();
    clusterCounter = std::unordered_map<int, int>();
    clusterColor = std::unordered_map<int, RGB>();
}

double DBScanKD::setEps(const double eps){
    this->eps = eps;
    return eps;
}
double DBScanKD::setMinPts(const double minPts){
    this->minPts = minPts;
    return minPts;
}

void DBScanKD::findClusters(){
    this->c = 0;
    std::vector<Point3D> N;
    for(Point3D& q: this-> DB){
        if(q.getCluster() != 0){
            continue;
        }
        std::vector<Point3D*> N = RangeQuery(q, this-> eps);
        if(N.size() < this-> minPts){
            q.setCluster(-1);
            continue;
        }
        this->c++;
        q.setCluster(this-> c);
        for (const auto& point : N) {
            s.push(&const_cast<Point3D&>(*point));  // Add each point to the stack
        }
        while(!this->s.empty()){
            Point3D* p = s.top();  // get the top element
            s.pop();     
            if(p->getCluster() == -1){
                p->setCluster(this->c);
            }  else if(p->getCluster() != 0){
                continue;
            }
            p->setCluster(this-> c);
            N = RangeQuery(*p, this->eps);
            if(N.size() >= this->minPts){
                for (const auto& point : N) {
                s.push(&const_cast<Point3D&>(*point));  // Add each point to the stack
                }
            }
        }
    }
    std::cout << "Neighbors found for point: " << N.size() << std::endl;
}

int DBScanKD::getNumberOfClusters(){
    return this->c;
}

std::vector<Point3D> DBScanKD::getPoints(){
    return this-> DB;
}
void DBScanKD::addToCluster(int cluster){
    int key = cluster;
    if(this->clusterCounter.find(key) == this->clusterCounter.end()){
        this->clusterCounter[key] = 1;
    }else{
        int value = clusterCounter[key] + 1;
        this->clusterCounter[key] = value;
    }
}

std::vector<Point3D> DBScanKD::read(const std::string& filename){
    std::vector<Point3D> points;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return points;  // Return empty vector or handle error differently
    }

    std::string line;

    // Read header line (and discard)
    std::getline(file, line);

    // Read each remaining line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        // Split line by commas
        while (std::getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() >= 3) {
            // Convert tokens to doubles and create Point3D
            double x = std::stod(tokens[0]);
            double y = std::stod(tokens[1]);
            double z = std::stod(tokens[2]);

            points.emplace_back(x, y, z);
        }
        else {
            std::cerr << "Malformed line (expected 3 values): " << line << std::endl;
        }
    }

    file.close();
    return points;
}

void DBScanKD::printStats(){
    std::cout << this->clusterCounter.size() << std::endl;
    struct CompareByValueDesc {
    bool operator()(const std::pair<int,int>& a, const std::pair<int,int>& b) const {
        if (a.second != b.second) {
            return a.second > b.second; // Descending order by value
        }
        return a.first < b.first;       // Tie-break by key ascending
    }
    };

    // Usage:
    std::set<std::pair<int,int>, CompareByValueDesc> sortedCount;

    // Example insertions (assuming clusterCounter is std::unordered_map<int,int>)
    for (const auto& entry : clusterCounter) {
        sortedCount.insert(entry);
    }
    std::cout << "cluster => size:\n";
    for (const auto& entry : sortedCount) {
        std::cout << "Cluster " << entry.first << " => " << entry.second << " points\n";
    }
    std::cout << "Noise points: " << this->noiseCounter << std::endl;
}

void DBScanKD::generateStats(){
    this->noiseCounter = 0;
    for(Point3D p: this->DB){
        int label = p.getCluster();
        if(label == -1){
            this->noiseCounter++;
        }else{
            this->addToCluster(label);
        }
    }
    for (const auto& pair : clusterCounter) {
    int label = pair.first;
    clusterColor[label] = RGB();
}
}

void DBScanKD::save(const std::string& filename) {
    std::ofstream file(filename + "_clusters.csv");
    if (!file.is_open()) {
        std::cerr << "Could not open file for writing: " << filename << std::endl;
        return;
    }

    file << "x,y,z,cluster\n";
    for (const Point3D& point : this->DB) {
        file << point.getX() << "," 
             << point.getY() << "," 
             << point.getZ() << "," 
             << point.getCluster() << "\n";
    }

    file.close();
}

int main(int argc, char* argv[]){
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input.csv> <eps> <minPts>\n";
        return 1;
    }
    std::string filename = argv[1];
    double eps = std::stod(argv[2]);
    double minPts = std::stod(argv[3]);
    std::vector<Point3D> points = DBScanKD::read(filename);
    std::cout << "Points loaded: " << points.size() << std::endl;
    DBScanKD scanner(points);
    scanner.setEps(eps);
    scanner.setMinPts(minPts);
    scanner.findClusters();
    scanner.generateStats();
    scanner.save(filename);
    scanner.printStats();
}
