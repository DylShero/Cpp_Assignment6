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

    //Calculate iterator boundaries for splitting the work onto 3 threads
    size_t chunk_size = n / available_threads;
    
    auto it1_start = v1.begin();
    auto it1_mid1  = it1_start + chunk_size;
    auto it1_mid2  = it1_mid1 + chunk_size;
    auto it1_end   = v1.end(); //Covers the rest of the vector

    auto it2_start = v2.begin();
    auto it2_mid1  = it2_start + chunk_size;
    auto it2_mid2  = it2_mid1 + chunk_size;

    /* --------------------------------Serial version-------------------------------------------------------*/

    auto start = std::chrono::steady_clock::now();
    dot_prod = std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 0.0);
    auto end = std::chrono::steady_clock::now();
    std::println("Dot product (serial). Answer = {}", dot_prod.load());
    std::println("Elapsed time : {}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    /* ------------------------------ task based --------------------------------------------------------*/
    start = std::chrono::steady_clock::now();

    auto f1 = std::async(policy, partial_dot, it1_start, it1_mid1, it2_start);
    auto f2 = std::async(policy, partial_dot, it1_mid1, it1_mid2, it2_mid1);
    auto f3 = std::async(policy, partial_dot, it1_mid2, it1_end, it2_mid2);

    //Wait for results
    dot_prod = f1.get() + f2.get() + f3.get();

    end = std::chrono::steady_clock::now();
    std::println("Dot product parallel async: dot_prod = {}", dot_prod.load());
    std::println("Elapsed time : {}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    /* ------------------------------ packaged_tasks --------------------------------------------------------*/


    start = std::chrono::steady_clock::now();

    using Iter = std::vector<double>::iterator;

    //Create three packaged tasks 
    std::packaged_task<double(Iter, Iter, Iter)> pt1(partial_dot);
    std::packaged_task<double(Iter, Iter, Iter)> pt2(partial_dot);
    std::packaged_task<double(Iter, Iter, Iter)> pt3(partial_dot);

    //Get the futures
    auto fut1 = pt1.get_future();
    auto fut2 = pt2.get_future();
    auto fut3 = pt3.get_future();

    //Move the packaged tasks into threads with iterators
    std::thread t1(std::move(pt1), it1_start, it1_mid1, it2_start);
    std::thread t2(std::move(pt2), it1_mid1, it1_mid2, it2_mid1);
    std::thread t3(std::move(pt3), it1_mid2, it1_end, it2_mid2);

    //Wait for results
    double dp = fut1.get() + fut2.get() + fut3.get();

    //Join all threads
    t1.join();
    t2.join();
    t3.join();

    end = std::chrono::steady_clock::now();
    std::println("Dot Product parallel threads & packaged task  = {}", dp);
    std::println("Elapsed time : {}ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    /* --------------------------------------packaged tasks-------------------------------------*/


    return 0;
}
