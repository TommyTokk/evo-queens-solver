#include "lib/lib.h"
#include <stdint.h>

int main (int argc, char **argv){
    srand(time(NULL));
    int population_size = POPULATION_SIZE;
    int state = STATE;
    Individual **population = generate_population(population_size, state);
    Individual *returned_individual = genetic_algorithm(population_size, state, population);
    //Individual *returned_individual = genetic_algorithm_v2(population_size, state, population);
    printf("Attended value: %d\n", (state) * (state - 1) / 2);
    printf("Returned value: %d\n", returned_individual->fitness);
    printf("=======================\n");
    print_individual(returned_individual);

    return 0;
}