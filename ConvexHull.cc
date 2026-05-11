#include "ConvexHull.h"

ConvexHull::ConvexHull(std::vector<Point>::iterator beg, std::vector<Point>::iterator end) 
    : points(beg, end) 
{
    //Member initialisation list deals with everything necessary for constructor
}

std::vector<Point> ConvexHull::generate_hull() {
    int n = points.size();
    
    //If there are 3 or fewer points they are the hull
    if (n <= 3) {
        hull = points;
        return hull;
    }

    hull.clear();

    //Find bottom half of the hull
    for (int i = 0; i < n; ++i) {
        // While the hull has at least 2 points and the last two points 
        // plus the current point make a right turn (or are collinear)
        while (hull.size() >= 2 && cross_prod(hull[hull.size() - 2], hull[hull.size() - 1], points[i])) {
            hull.pop_back(); //Remove the interior point
        }
        hull.push_back(points[i]);
    }

    //Find the top half of the hull (reverse of previous)
    size_t lower_hull_size = hull.size(); //Save the size of the lower hull so we don't accidentally pop its points
    
    //Start from the second-to-last point and go backwards
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() > lower_hull_size && cross_prod(hull[hull.size() - 2], hull[hull.size() - 1], points[i])) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    // The last point added in the top half is the same as the first point of the bottom half, so we remove it to avoid duplicates.
    hull.pop_back();

    return hull;
}

void ConvexHull::merge_to_right(ConvexHull &right) {
    //Insert all points from right hull into left.
    points.insert(points.end(), right.points.begin(), right.points.end());
    
    //Clear the right hulls points
    right.points.clear();
    right.hull.clear();
    
    //Generate the hull using the newly merged, sorted points.
    generate_hull();
}