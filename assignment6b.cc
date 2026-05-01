/**
 * @file assignment5b.cc
 * @brief Main function for 5614 Assignment 6 Part 2.
 * @author R. Morrin
 * @version 7.0
 * @date 2026-04-06
 */
#include <println>
#include <vector>
#include <random>
#include <functional>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <future>

#include "point.h"
#include "ConvexHull.h"

// Use below two lines to seed from random device
std::random_device rd;
std::default_random_engine rng {rd()};
// Use the below with some seed for a fixed seed
// std::default_random_engine rng {1234};

const auto policy = std::launch::async;
// const auto policy = std::launch::deferred;

int main(void)
{
    // You can change number of points if you want for timing purposes
    const int n {10'000'000};
    std::vector<Point> points(n);
    auto gaussian_rv = std::bind(std::normal_distribution<> {0,1}, std::ref(rng));
    //auto gaussian_rv = std::bind(std::uniform_real_distribution<> {0,1}, std::ref(rng)); // If you want a different distribution

    // Assign random coordinates to each point.
    for (auto &p : points) {
        p.x = gaussian_rv(); 
        p.y = gaussian_rv(); 
    }

    // sort Points in order of increasing x-coordinate. You wrote this function in points.cc
    sort_points(points);

    // Construct a convex hull from these points. You wrote this constructor
    ConvexHull CH {std::begin(points), std::end(points)};

    auto start = std::chrono::steady_clock::now();
    CH.generate_hull(); 	// Generate hull. You wrote this function
    auto end = std::chrono::steady_clock::now();

    std::println("Serial time: {}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    write_to_file( std::string("points.txt"), CH.get_points()); 	// Write all points to file
    write_to_file( std::string("serial.txt"), CH.get_hull()); 		// Write hull points to file

    // ----------------------------------------------------------------------------------
    /*
     * You don't need to change above this line
     */


    /*
     * Create three ConvexHull objects below here. 
     * ConvexHull CH_left from the leftmost one-third of points from CH above
     * ConvexHull CH_mid from the middle one-third of points from CH above
     * ConvexHull CH_right from the rightmost one-third of points from CH above
     */

    start = std::chrono::steady_clock::now();
    {
        /*
         * launch the std::async tasks inside these braces. Do not forget to store
         * the returned future in a local variable
         * or else the main thread will sleep for each launched task.
         * i.e. you will need to to auto fut1 = std::async(policy, ...)
         *
         */

        /*
         * If you run deferred policy then you the task would not start executing
         * normally until you called "get" or wait on the future. Call wait on them
         * below here
         */

    } // Leave these braces here. the ~futures will block here so if we had
      // had asynchonous policy we wouldn't even need to do the waits above
      // You don't need the braces here though. I just include them to mark
      // where you can call the function.

    /*
     * You don't need to change below this line
     */
    // ----------------------------------------------------------------------------------

    // If you want to be more accurate, comment out the write_to_file functions when timing the code.
    write_to_file( std::string("left_hull.txt"), CH_left.get_hull());
    write_to_file( std::string("mid_hull.txt"), CH_mid.get_hull());
    write_to_file( std::string("right_hull.txt"), CH_right.get_hull());

    CH_left.merge_to_right(CH_mid); 	// Merge first two hulls into CH_left. See Fig. 4 on assignmnet document
    write_to_file( std::string("after_first_merge.txt"), CH_left.get_hull());

    CH_left.merge_to_right(CH_right);   // Merge other hull into CH_right

    write_to_file( std::string("after_second_merge.txt"), CH_left.get_hull());

    end = std::chrono::steady_clock::now();
    std::println("Parallelised time {}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 0;
}
