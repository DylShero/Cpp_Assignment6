#include "point.h"
#include <iostream>


bool Point::operator==(const Point& rhs) {
    return (this->x == rhs.x) && (this->y == rhs.y);
}


bool cross_prod(Point p1, Point p2, Point p3) {
    double v1_x = p2.x - p1.x;
    double v1_y = p2.y - p1.y;
    double v2_x = p3.x - p1.x;
    double v2_y = p3.y - p1.y;

    double cp = (v1_x * v2_y) - (v1_y * v2_x);
    return cp <= 0;
}


void write_to_file(std::string fn, std::vector<Point> pts) {
    std::ofstream outFile(fn);
    
    if (!outFile.is_open()) {
        std::cerr << "Could not open file " << fn << "\n";
        return;
    }

    for (const auto& pt : pts) {
        outFile << pt << "\n"; 
    }
    
    outFile.close();
}

void sort_points(std::vector<Point>& points) {
    //Lambda expression to compare two points
    auto comparePoints = [](const Point& a, const Point& b) {
        //If the x-coordinates are  the same, sort by the y
        if (a.x == b.x) {
            return a.y < b.y;
        }
        //Otherwise sort by the x-coordinate
        return a.x < b.x;
    };

    //Sort with lambda expression
    std::sort(points.begin(), points.end(), comparePoints);

}