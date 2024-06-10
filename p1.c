/*
CPSC 457 Assignment 2 part 2 submitted by Aishan Irfan (30157743)
*/
//including all the header files for the libraries used
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//defining the constants
#define NUM_ASTRONOMERS 10
#define NUM_ASYMMETRIC 3
#define AVG_EAT_TIME 1
#define MAX_WAIT_TIME 2

//ordering array used for representing the astronomers on the table
int ordering[NUM_ASTRONOMERS];

//defining the mutex arary for chopstics and thread astronomers
pthread_mutex_t chopsticks[NUM_ASTRONOMERS];
pthread_t philosophers[NUM_ASTRONOMERS];

//struct for defining each astronomer
typedef struct {
    int id; //astronomer id
    int is_asymmetric; //flag for checking if the astronomer is asymmetric or symmetric
    int left_chopstick; //holds the index for the chopstick to the left of the astronomer
    int right_chopstick; //holds the index for the chopstick to the right of the astronomer
} Astronomer;

//eating method for asymmetric astronomers
void eat_asym(int id) {
    printf("Asymmetric astronomer %d is eating\n", id);
    sleep(rand() % AVG_EAT_TIME + 1);
}

//eating method for symmetric astronomers
void eat_sym(int id) {
    printf("Symmetric astronomer %d is eating\n", id);
    sleep(rand() % AVG_EAT_TIME + 1);
}

//thinking method for asymmetric astronomers
void think_asym(int id) {
    printf("Asymmetric astronomer %d is thinking\n", id);
    sleep(rand() % MAX_WAIT_TIME + 1);
}

//thinking method for asymmetric astronomers
void think_sym(int id){
    printf("Symmetric astronomer %d is thinking\n", id);
    sleep(rand() % MAX_WAIT_TIME + 1);
}

//method for releasing the chopsticks
void release_chopsticks(Astronomer *astronomer) {
    pthread_mutex_unlock(&chopsticks[astronomer->left_chopstick]);
    pthread_mutex_unlock(&chopsticks[astronomer->right_chopstick]);
    if(astronomer->is_asymmetric){
        think_asym(astronomer->id);
    }

    else{
    think_sym(astronomer->id);
    }
}

//thread function for each astronomer
void *philosopher(void *arg) {
    Astronomer *astronomer = (Astronomer *)arg;
    while(1){

    //checking if the astronomer is asymmetric    
    if(astronomer->is_asymmetric){
        //acquire the right chopstick
        if(pthread_mutex_trylock(&chopsticks[astronomer->right_chopstick])==0){
            printf("Asymmetric astronomer %d picked up the right chopstick\n",astronomer->id);
            //sleep for 1 second
            sleep(1);
            //acquire the left chopstick
            if(pthread_mutex_trylock(&chopsticks[astronomer->left_chopstick])==0){
                printf("Asymmetric astronomer %d picked up the left chopstick\n",astronomer->id);
                //eating for a fixed amount of time
                eat_asym(astronomer->id);
                //release both the chopsticks
                release_chopsticks(astronomer);
                printf("Asymmetric astronomer %d released both of his chopsticks\n",astronomer->id);
            }
            else{
                //release the right chopstick
                pthread_mutex_unlock(&chopsticks[astronomer->right_chopstick]);
                printf("Asymmetric astronomer %d released his right chopstick\n",astronomer->id);
                //going back to thinking
                think_asym(astronomer->id);
            }
        }
        else{
            //going back to thinking
            think_asym(astronomer->id);
        }
        
    }

    else {
        //sleep for 2 seconds
        sleep(2);
        //try acquring both the chopsticks
        if(pthread_mutex_trylock(&chopsticks[astronomer->left_chopstick])==0){   
            printf("Symmetric astronomer %d picked up the left chopstick\n",astronomer->id);
            if(pthread_mutex_trylock(&chopsticks[astronomer->right_chopstick])==0){
                printf("Symmetric astronomer %d picked up the right chopstick\n",astronomer->id);
                //eat for a fixed amount of time
                eat_sym(astronomer->id);
                //release both the chopsticks
                release_chopsticks(astronomer);
                printf("Symmetric astronomer %d released both of his chopsticks\n",astronomer->id);
            }
            else{
                //release the left chopstick
                pthread_mutex_unlock(&chopsticks[astronomer->left_chopstick]);
                printf("Symmetric astronomer %d released his left chopstick\n",astronomer->id);
                //going back to thinking
                think_sym(astronomer->id);
            }

        }
        else{
            //going back to thinking
            think_sym(astronomer->id);

        }
        
    }

    }

    
}

// Function to place astronomers as specified in the problem statement
void place_astronomers(int *ordering) {
    for (int i = 0; i < NUM_ASYMMETRIC; i++) {
        ordering[i] = 1;
    }
    for (int i = NUM_ASYMMETRIC; i < NUM_ASTRONOMERS; i++) {
        ordering[i] = 0;
    }
    for (int i = 0; i < NUM_ASTRONOMERS; i++) {
        int j = rand() % NUM_ASTRONOMERS;
        int temp = ordering[i];
        ordering[i] = ordering[j];
        ordering[j] = temp;
    }
}

//main method
int main() {
    //generating the seed for the random function
    srand(time(NULL));
    //placing the astronomers randomly across the table
    place_astronomers(ordering);

    //initializing the chopstick mutexes
    for (int i = 0; i < NUM_ASTRONOMERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    //initializing the astronomer structs
    Astronomer astronomers[NUM_ASTRONOMERS];
    for (int i = 0; i < NUM_ASTRONOMERS; i++) {
        astronomers[i].id = i;
        astronomers[i].is_asymmetric = ordering[i];
        astronomers[i].left_chopstick = i;
        astronomers[i].right_chopstick = (i + 1) % NUM_ASTRONOMERS;
    }

    //creating the astronomer threads
    for (int i = 0; i < NUM_ASTRONOMERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &astronomers[i]);
    }

    //joining all the astronomer threads
    for (int i = 0; i < NUM_ASTRONOMERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}