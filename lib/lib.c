#include "lib.h"

Individual *generate_random_individual(int state){
    //srand(time(NULL));
    Individual *ind = (Individual *)malloc(sizeof(Individual));
    if(!ind){
        printf("Memory allocation failed\n");
        exit(1);
    }

    ind->individual = (char *)malloc((state + 1) * sizeof(char));
    if(!ind->individual){
        printf("Memory allocation failed\n");
        exit(1);
    }

    for(int i = 0; i < state; i++){
        ind->individual[i] = (rand() % STATE) + '0';
    }
    ind->individual[state] = '\0';
    ind->fitness = fitness(ind, state);

    ind -> probability = 0;
    ind -> generation = 0;

    return ind;
}

int compare(const void *a, const void *b){
    Individual *ind1 = *(Individual **)a;
    Individual *ind2 = *(Individual **)b;
    if(ind1 -> fitness < ind2 -> fitness){
        return 1;
    }
    else if(ind1 -> fitness > ind2 -> fitness){
        return -1;
    }
    else{
        if(ind1 -> probability < ind2 -> probability){
            return 1;
        }
        else if(ind1 -> probability > ind2 -> probability){
            return -1;
        }
        else{
            return 0;
        }
    }
}

void print_individual(Individual *individual){
    printf("Name: %s\n", individual -> individual);
    printf("Probability: %f%%\n", (individual -> probability) * 100);
    printf("Generation: %d\n", individual -> generation);
    printf("Fitness: %d\n", individual -> fitness);
    printf("-----------------\n");
}

void print_population(Individual **population, int population_size){
    for(int i = 0; i < population_size; i++){
        print_individual(population[i]);
    }
}

Individual **generate_population(int population_size, int state){
    Individual **population = (Individual **)malloc(population_size * sizeof(Individual *));
    if(!population){
        printf("Memory allocation failed\n");
        exit(1);
    }

    for(int i = 0; i < population_size; i++){
        population[i] = generate_random_individual(state);
    }
    return population;
}

int fitness (Individual *individual, int state){
    int fitness = 0;
    for(int i = 0; i < state; i++){
        for(int j = i + 1; j < state; j++){
            if(!(abs(individual->individual[i] - individual->individual[j]) == abs(i - j) || individual->individual[i] == individual->individual[j])){
                fitness++;
            }
        }
    }
    return fitness;
}

int get_max_fitness(Individual **population, int population_size){
    int max = population[0] -> fitness;
    for(int i = 1; i < population_size; i++){
        if(population[i] -> fitness > max){
            max = population[i] -> fitness;
        }
    }
    return max;
}

void set_selection(Individual **population, int population_size){
    int sum = 0;
    for(int i = 0; i < population_size; i++){
        sum += population[i] -> fitness;
    }
    for(int i = 0; i < population_size; i++){
        population[i] -> probability = (double)population[i] -> fitness / sum;
    }
}

Individual *roulette_wheel_selection(Individual **population, int population_size){
    srand(time(NULL));
    double r = (double)rand() / RAND_MAX;
    double total_prob = 0;
    for(int i = 0; i < population_size; i++){
        total_prob += population[i] -> probability;
        if(total_prob >= r){
            return population[i];
        }
    }
    return population[population_size - 1];
}

Individual *tournament_selection(Individual **population, int population_size){
    //srand(time(NULL));
    int tournament_size = 5;
    Individual *tournament[tournament_size];
    for(int i = 0; i < tournament_size; i++){
        tournament[i] = population[rand() % population_size];
    }
    qsort(tournament, tournament_size, sizeof(Individual *), compare);
    return tournament[0];
}

char *crossover(Individual *parent1, Individual *parent2, int state){
    //srand(time(NULL));
    int crossover_point = rand() % state;
    char *child = (char *)malloc((state + 1) * sizeof(char));
    if(!child){
        printf("Memory allocation failed\n");
        exit(1);
    }
    for(int i = 0; i < crossover_point; i++){
        child[i] = parent1 -> individual[i];
    }
    for(int i = crossover_point; i < state; i++){
        child[i] = parent2 -> individual[i];
    }
    child[state] = '\0';
    return child;
}

char *mutate(char *individual, int state){
    //srand(time(NULL));
    float  MUTATION_RATE = ((float)rand()/(float)(RAND_MAX));
    //printf("Mutation rate: %f\n", MUTATION_RATE);
    for(int i = 0; i < state; i++){
        if((float)rand() / RAND_MAX > MUTATION_RATE){
            individual[i] = (rand() % STATE) + '0';
        }
    }
    return individual;
}

Individual *genetic_algorithm(int population_size, int state, Individual **population){
    int max_fitness = get_max_fitness(population, population_size);
    Individual **new_population = (Individual **)malloc(population_size * sizeof(Individual *));
    Individual *best_individual = population[0];

    if(!new_population){
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for(int i = 0; i < MAX_GENERATIONS; i++){

        set_selection(population, population_size);

        for(int j = 0; j < population_size; j++){
            Individual *parent1 = tournament_selection(population, population_size);
            Individual *parent2 = tournament_selection(population, population_size);
            while(parent1 -> individual == parent2 -> individual){
                parent2 = tournament_selection(population, population_size);
            }
            char *child = crossover(parent1, parent2, state);
            child = mutate(child, state);
            new_population[j] = (Individual *)malloc(sizeof(Individual));
            if(!new_population[j]){
                printf("Memory allocation failed\n");
                exit(1);
            }
            new_population[j] -> individual = child;
            new_population[j] -> fitness = fitness(new_population[j], state);
            new_population[j] -> probability = 0;
            new_population[j] -> generation = i+1;
        }
        population = new_population;
        qsort(population, population_size, sizeof(Individual *), compare);
        if(population[0] -> fitness > best_individual -> fitness){
            best_individual = population[0];
        }
        if(get_max_fitness(population, population_size) > max_fitness){
            max_fitness = get_max_fitness(population, population_size);
        }
    }
    return best_individual;
}

// Individual *genetic_algorithm_v2(int population_size, int state, Individual **population){
//     int max_fitness = get_max_fitness(population, population_size);
//     Individual **new_population = (Individual **)malloc(population_size * sizeof(Individual *));
//     if(!new_population){
//         printf("Memory allocation failed\n");
//         exit(1);
//     }
//     Individual *best_individual = population[0];
//     qsort(population, population_size, sizeof(Individual *), compare);

//     for(int i = 0; i < MAX_GENERATIONS; i++){
//         for (int j = 1; j < population_size; j++){
            
//         }
//     }
// }


