/**
 * @file assignment5a.cc
 * @brief Skeleton code for 5614 assignment 6 Part 1.
 * @author R. Morrin
 * @version 7.0
 * @date 2026-04-06
 */

#include <vector>
#include <print>
#include <chrono>
#include <functional>
#include <random>
#include <algorithm>
#include <thread>
#include <future>


// You can use this global to make it easy to switch
const auto policy = std::launch::async;  
//const auto policy = std::launch::deferred;   


int main(void)
{
    const int n {50'000'000};
    std::atomic<double> dot_prod {0};  // I used atomic to prevent reordering of code around the timings
    std::random_device rd {};
    std::default_random_engine eng{rd()};
    // Note using std::ref to wrap engine in a referece_wrapper. See Assignment doc
    auto ui = std::bind(std::normal_distribution<>{}, std::ref(eng));

    std::vector<double> v1(n);
    std::vector<double> v2(n);
    std::generate(std::begin(v1), std::end(v1), ui);
    std::generate(std::begin(v2), std::end(v2), ui);


    auto hardware_threads = std::thread::hardware_concurrency();
    std::println("Num hardware threads = {}", hardware_threads);
    unsigned available_threads = 3;

    auto partial_dot = [](auto it, auto it2, auto it3){return std::inner_product(it, it2, it3, 0.0);};

    /* --------------------------------Serial version-------------------------------------------------------*/

    auto start = std::chrono::steady_clock::now();
    dot_prod = std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 0.0);
    auto end = std::chrono::steady_clock::now();
    std::println("Dot product (serial). Answer = {}", dot_prod);
    std::println("Elapsed time : {}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    /* ------------------------------ task based --------------------------------------------------------*/
    start = std::chrono::steady_clock::now();

    /* Add code to do spawn three async tasks here. You can use the lambda expression partial_dot from above */

    end = std::chrono::steady_clock::now();
    std::println("Dot product parallel async: dot_prod = {}", dot_prod);
    std::println("Elapsed time : {}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    /* ------------------------------ packaged_tasks --------------------------------------------------------*/


    start = std::chrono::steady_clock::now();

    /*
     * Add code to do spawn three threads to run three packaged tasks here. You can use the lamda expression partial_dot from above 
     * You will need to create the packaged tasks and then move each one into a thread 
     */

    end = std::chrono::steady_clock::now();
    std::println("Dot Product parallel threads & packaged task  = {}", dp);
    std::println("Elapsed time : {}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    /* --------------------------------------packaged tasks-------------------------------------*/


    return 0;
}
