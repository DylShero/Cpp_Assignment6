/**
 * @file assignment6c.cc
 * @brief Skeleton code for Q3 of 5614 Assignment 6
 *          You will use the below code to price a fixed strike arithmetic asian option
 *          There is a bit of information in this question on how to implement generation
 *          of random numbers for parallel processes. See the Assignment document for a 
 *          very brief introduction. The main purpose of this is to use some of Boost.MPI
 *          and Boost.Serialization libraries
 *          Note that I have made the simplification that delta_t=1 so that it drops out 
 *          of any equations. The average is taken over the values at the end of each timestep.
 *          This would correspond to taking the average of the end-of-year values.
 *          Note also that this is somewhat of a "toy" example.
 *
 *          Most of the code is done for you. Look for the three "TODO"s
 *
 * @author R. Morrin
 * @version 1.0
 * @date 2026-04-06
 */
#include <boost/mpi.hpp>
#include <boost/random.hpp>
#include <boost/serialization/valarray.hpp>
#include <random>
#include <print>
#include <valarray>

struct Stats {
    double mean;
    double variance;
    double in_the_money;
    unsigned processor_rank;

    /// TODO: Add serialize function
};

// Struct to hold simulation parameters. You won't have to change this
struct Parameters
{
    double S0 {100};                    //!< Initial Value/price
    unsigned T  {10};                   //!< Maturity.  End time. 
    double sigma {0.3};                 //!< Volatility
    double mu {0.00};                   //!< Drift term
    double strike {105};                //!< Strike
	unsigned paths_per_proc {10'000'000};  //!< Number of paths per process
};

int main()
{
	Parameters params;

    // Set up your MPI
	boost::mpi::environment env;
	boost::mpi::communicator world;

	// Populate seeds from random device
	std::valarray<std::uint32_t> seeds(10);
	if(world.rank()==0){
		std::random_device rd;
		for(auto& i : seeds){
			i = rd(); 
		}
	}
	// Broadcast seeds from proc 0 to other processes
	boost::mpi::broadcast(world, seeds, 0);

	// ranlux48_base better for skipping ahead. 
	std::ranlux48_base gen;
	// Seed the generator
	std::seed_seq seed_sequence{std::begin(seeds), std::end(seeds)};
	gen.seed(seed_sequence);
	// Use boosts normal_distribution as it uses Ziggurat algorithm so we know how many RNs will be consumed from the engine ..... at least for this assignment we will assume it does
	boost::random::normal_distribution dist {0.0,1.0};
	unsigned block_size {params.paths_per_proc * params.T}; // params.T is the same as number of timesteps given we have decided delta_t = 1 year.
	gen.discard(world.rank()*block_size); 					// Skip ahead on other ranks
	auto rng {std::bind(dist, std::ref(gen))};
	Stats proc_stats;       // Holds statistics for each process

	{ // Dummy braces to reduce scope of valarrays so that they are cleaned up when not needed
		std::valarray<double> vals(100.0, params.paths_per_proc);   // S0 = 100
		std::valarray<double> payoff(0.0, params.paths_per_proc);
		std::valarray<double> random_numbers(0.0, params.paths_per_proc);

        /// TODO: Write code to do the simulation for this process.
        ///     Note that it should only take about 15-20 lines
	}

	// TODO: Gather values back from other processes to process 0 and print to screen
	if(world.rank()==0){
	}
	else{
	}

	return 0;
}
