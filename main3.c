#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void child_process() {
    // Seed the random number generator
    srand(time(NULL) ^ (getpid()<<16));

    int num_iterations = rand() % 31; // Random number of iterations, max 30
    for (int i = 0; i < num_iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        
        // Sleep for a random amount of time, max 10 seconds
        int sleep_time = rand() % 11; // random sleep time between 0-10
        sleep(sleep_time);
        
        printf("Child Pid: %d is awake!\n", getpid());
        printf("Where is my Parent: %d?\n", getppid());
    }

    // Exit the child process
    exit(0);
}

int main() {
    pid_t pid1, pid2;

    // Fork the first child
    if ((pid1 = fork()) == 0) {
        child_process();  // Run the child process code
    } else if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }

    // Fork the second child
    if ((pid2 = fork()) == 0) {
        child_process();  // Run the child process code
    } else if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    }

    // Parent process waits for both children to complete
    int status;
    pid_t completed_pid;
    for (int i = 0; i < 2; i++) {
        completed_pid = wait(&status);
        printf("Child Pid: %d has completed\n", completed_pid);
    }

    return 0;
}