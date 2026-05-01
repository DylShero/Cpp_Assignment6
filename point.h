/**
 * @file point.h
 * @brief Class definition for Point class needed for 5614 Assignment 6.
 * 		Write the necessary function definitions in point.cc
 * @author R. Morrin
 * @version 6.0
 * @date 2026-04-06
 */
#ifndef POINT_H_OMJSZLDH
#define POINT_H_OMJSZLDH
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>
#include <format>
#include <sstream>
#include <iomanip>


/**
 * @brief Simple structure to store coordinates of a point on the grid
 */
struct Point {
    double x;                                      //!< x-coordinate 
    double y;                                      //!< y-coordinate 

    Point() = default;
    Point(double inx, double iny) : x{inx}, y{iny}{};  //!< Constructor

    // Write the definition of this in point.cc
    bool operator==(const Point & rhs);   	
};

/**
 * @brief Overloading output stream operator for a Point.
 * The operator should simply print the x and y coordinates of Point "in"
 * If you need to output a point, just use std::cout rather than specialising
 * your own formatter. 
 *
 * @param os    Reference to output stream
 * @param in    Reference to Point which we want to print.
 *
 * @return      Reference to output stream
 */
inline std::ostream & operator<<(std::ostream & os,const Point & in){
    os << std::fixed << std::setw(9) << in.x << ", " << std::setw(9) << in.y;
    return os; 
}

/**
* @brief Specialising std::formatter for the Point class
*/
template <>
struct std::formatter<Point> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const Point& p, FormatContext& ctx) const {
        std::ostringstream os;
        os << std::fixed
           << std::setw(9) << p.x
           << ", "
           << std::setw(9) << p.y;

        return std::format_to(ctx.out(), "{}", os.str());
    }
};


// Write the definition of the 3 below functions in point.cc
void write_to_file(std::string fn, std::vector<Point> pts);
bool cross_prod(Point p1, Point p2, Point p3);
void sort_points(std::vector<Point>& points);

#endif /* end of include guard: POINT_H_OMJSZLDH */
