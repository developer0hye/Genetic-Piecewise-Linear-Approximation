#include <iostream>

#include <vector>
#include <bitset>
#include <random>

#include <cmath>

std::default_random_engine rng_double;

double getFitness(std::vector<double> individual);
double getMAE(std::vector<double> individual);

double generate_boundary_value(double prev_piece_boundary,
                              double cur_piece_boundary,
                              double next_piece_boundary)
{
    std::uniform_real_distribution<double> dist((cur_piece_boundary + prev_piece_boundary)/2,
                                                (cur_piece_boundary + next_piece_boundary)/2);
    return dist(rng_double);
}

std::vector<double> generate_individual(const unsigned int piece_nums)
{
    std::vector<double> individual;

    individual.push_back(pow(10, -7));

    for(int piece_n = 0; piece_n < piece_nums; piece_n++)
    {
        double boundary_value = generate_boundary_value(individual.back(),
                                                        pow(10, -6 + piece_n),
                                                        pow(10, -5 + piece_n));
        individual.push_back(boundary_value);
    }

    individual.push_back(1.0);

    return individual;
}


std::vector<double> tournament_selection(std::vector<std::vector<double>> individuals)
{
    if(individuals.empty()) return std::vector<double>();

    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> dist_individual_selection(0, individuals.size()-1);
    std::uniform_int_distribution<std::mt19937::result_type> dist_random_prop(0, 100);

    unsigned int idx_individual_a = 0;
    unsigned int idx_individual_b = 0;

    while(idx_individual_a == idx_individual_b)
    {
        idx_individual_a = dist_individual_selection(rng);
        idx_individual_b = dist_individual_selection(rng);
    }

    if(getFitness(individuals[idx_individual_a]) > getFitness(individuals[idx_individual_b])) //less is better
    {
        std::swap(idx_individual_a, idx_individual_b);
    }

    unsigned int t = 55;

    if(t > dist_random_prop(rng))
    {
        return individuals[idx_individual_a];
    }
    else
    {
        return individuals[idx_individual_b];
    }
}



std::vector<double> roulette_wheel_selection(std::vector<std::vector<double>> individuals, double SumOfFitness)
{
    std::uniform_real_distribution<double> dist_point(0, SumOfFitness);

    double point = dist_point(rng_double);
    double sum = 0;

    for(std::vector<double> individual: individuals)
    {
        sum += getFitness(individual);
        if(point < sum)
            return individual;
    }
}



double oetf(double linearLight)
{
    double c1 = 0.8359375;
    double c2 = 18.8515625;
    double c3 = 18.6875;
    double m1 = 0.1593017578125;
    double m2 = 78.84375;

    double tempValue = pow(linearLight, m1);
    return (pow(((c2 *(tempValue) + c1)/(1.0 + c3 *(tempValue))), m2));
}

double getFitness(std::vector<double> individual)
{
    double fitness = 0;

    for(int idx_piece = 0; idx_piece < individual.size() -2; idx_piece++)
    {
        double piece_gap = (individual[idx_piece + 1] - individual[idx_piece])/10000.;

        double y_1 = oetf(individual[idx_piece]);
        double y_2 = oetf(individual[idx_piece + 1]);

        double slope = (y_2 - y_1)/(individual[idx_piece + 1] - individual[idx_piece]);
        double bias = y_1-slope*individual[idx_piece];

        for(double linear_light = individual[idx_piece]; linear_light < individual[idx_piece + 1]; linear_light += piece_gap)
        {
            double label = oetf(linear_light);
            double predicted = slope*linear_light + bias;

            fitness += exp(-fabs(label-predicted));
        }
    }
    return fitness;
}

double getMAE(std::vector<double> individual)
{
    double mae = 0;

    for(int idx_piece = 0; idx_piece < individual.size() -1; idx_piece++)
    {
        double piece_gap = (individual[idx_piece + 1] - individual[idx_piece])/10000.;

        double y_1 = oetf(individual[idx_piece]);
        double y_2 = oetf(individual[idx_piece + 1]);

        double slope = (y_2 - y_1)/(individual[idx_piece + 1] - individual[idx_piece]);
        double bias = y_1-slope*individual[idx_piece];

        for(double linear_light = individual[idx_piece]; linear_light < individual[idx_piece + 1]; linear_light += piece_gap)
        {
            double label = oetf(linear_light);
            double predicted = slope*linear_light + bias;

            mae += fabs(label-predicted);
        }
    }
    return mae;
}


std::vector<double> mutation(std::vector<double> individual)
{
    static std::random_device dev;
    static std::mt19937 rng(dev());

    static std::uniform_int_distribution<std::mt19937::result_type> dist_mutation_accept(0, 100);


    std::vector<double> mutated_individual;

    mutated_individual.push_back(pow(10, -7));

    for(unsigned int piece_idx = 1; piece_idx < individual.size()-1; piece_idx++)
    {
        double prev_piece_boundary = mutated_individual.back();
        double cur_piece_boundary = individual[piece_idx];
        double next_piece_boundary = individual[piece_idx+1];

        std::uniform_real_distribution<double> mutated_boundary(cur_piece_boundary - (cur_piece_boundary - prev_piece_boundary)/100.,
                                                                cur_piece_boundary + (next_piece_boundary - cur_piece_boundary)/100.);

        mutated_individual.push_back(mutated_boundary(rng_double));
    }

    mutated_individual.push_back(1.0);

    return mutated_individual;
}

std::vector<double> cross_over(std::vector<double> parentA, std::vector<double> parentB)
{
    std::vector<double> offspring;

    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);

    for(unsigned int piece_idx = 0; piece_idx < parentA.size(); piece_idx++)
    {
        double piece_parentA = parentA[piece_idx];
        double piece_parentB = parentB[piece_idx];
        double piece_offspring;

        bool b_offspring_piece_over = false;

        if(piece_idx != 0)
        {
            double prev_piece_offspring = offspring.back();

            if(piece_parentA < prev_piece_offspring)
            {
                piece_offspring = piece_parentB;
                b_offspring_piece_over = true;
            }
            else if(piece_parentB < prev_piece_offspring)
            {
                piece_offspring = piece_parentA;
                b_offspring_piece_over = true;
            }
        }

        if(b_offspring_piece_over == false)
        {
            if(dist(rng) == 1)
                piece_offspring = parentA[piece_idx];
            else
                piece_offspring = parentB[piece_idx];
        }

        offspring.push_back(piece_offspring);
    }

    return offspring;
}


int main()
{
    const unsigned int k_NUM_INDIVIDUALS    = 5;
    const unsigned int k_NUM_GENERATION     = 100;

    std::vector<std::vector<double>> individuals;

    for(int idx_individual = 0; idx_individual < k_NUM_INDIVIDUALS; idx_individual++)
        individuals.push_back(generate_individual(6));


    double best_fitness = 0.;
    double best_mae = 9999.;
    std::vector<double> best_individual;

    for(int idx_generation = 0; idx_generation < k_NUM_GENERATION; idx_generation++)
    {
        std::cout<< "gen: "<< idx_generation <<std::endl;
        //evaluate fitness before GA Operation
        double sum_fitness = 0.;
        double sum_mae = 0.;
        for (std::vector<double> individual: individuals)
        {
            double fitness = getFitness(individual);
            double mae = getMAE(individual);

            sum_fitness += fitness;
            sum_mae += mae;
       //     std::cout << fitness <<std::endl;
            if(best_mae > mae)
            {
                best_mae = mae;
                best_individual = individual;

                std::cout<< "***gen: "<< idx_generation << " best fitness of all individuals: "<< fitness << " mae: " << getMAE(individual) << std::endl;
            }
        }
        std::cout<< "gen: "<< idx_generation <<
                    " mean fit =" << sum_fitness / (double)individuals.size() <<
                    " mean mae =" << sum_mae / (double)individuals.size() <<
                    std::endl;


        std::vector<std::vector<double>> new_individuals;
        //cross over
        for (int n_cross_over = 0; n_cross_over < k_NUM_INDIVIDUALS; n_cross_over++)
        {
            std::vector<double> parentA = roulette_wheel_selection(individuals, sum_fitness);
            std::vector<double> parentB = roulette_wheel_selection(individuals, sum_fitness);

            std::vector<double> offspring = cross_over(parentA, parentB);

            offspring = mutation(offspring);
            new_individuals.push_back(offspring);
        }

        individuals = new_individuals;
    }

    for(double boundary_value: best_individual)
    {
        std::cout << boundary_value << std::endl;
    }


    for(int idx_piece = 0; idx_piece < best_individual.size() -1; idx_piece++)
    {
        double y_1 = oetf(best_individual[idx_piece]);
        double y_2 = oetf(best_individual[idx_piece + 1]);

        double slope = (y_2 - y_1)/(best_individual[idx_piece + 1] - best_individual[idx_piece]);
        double bias = y_1-slope*best_individual[idx_piece];

        std::cout << "slope: " << slope << std::endl;
        std::cout << "bias: " << bias << std::endl;
    }


    return 0;
}
