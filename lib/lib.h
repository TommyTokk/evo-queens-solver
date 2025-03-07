#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define POPULATION_SIZE 1000
#define STATE 8
#define MAX_GENERATIONS 7000


typedef struct {
    char *individual;
    int fitness;
    double probability;
    int generation;
} Individual;

Individual **generate_population(int population_size, int state);
int fitness(Individual *individual, int state);
char *crossover(Individual *parent1, Individual *parent2, int state);
void set_selection(Individual **population, int population_size);
char *mutate(char *individual, int state);
int get_max_fitness(Individual **population, int population_size);

//Selection algorithms
Individual *roulette_wheel_selection(Individual **population, int population_size);
Individual *tournament_selection(Individual **population, int population_size);


Individual *generate_random_individual(int state);
void print_individual(Individual *individual);
void print_population(Individual **population, int population_size);
int compare_individuals(const void *a, const void *b);

//Genetic algorithms
Individual *genetic_algorithm(int population_size, int state,Individual **population);
Individual *genetic_algorithm_v2(int population_size, int state,Individual **population);