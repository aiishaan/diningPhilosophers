# Dining Astronomers

This project simulates the classic "Dining Philosophers" problem with a twist, where astronomers (philosophers) can be either symmetric or asymmetric in their approach to acquiring chopsticks. The program uses POSIX threads and mutexes to manage concurrent execution and synchronization of astronomers.

## Author

- **Aishan Irfan**

## Overview

The program creates 10 astronomers who are either symmetric or asymmetric in their behavior:

- **Symmetric Astronomers:** These astronomers attempt to pick up their left chopstick first and then their right chopstick
- **Asymmetric Astronomers:** These astronomers attempt to pick up their right chopstick first and then their left chopstick

The astronomers alternate between thinking and eating, with their actions being printed to the console.

## Constants

- `NUM_ASTRONOMERS`: Number of astronomers (10)
- `NUM_ASYMMETRIC`: Number of asymmetric astronomers (3)
- `AVG_EAT_TIME`: Average time spent eating (1 second)
- `MAX_WAIT_TIME`: Maximum time spent thinking (2 seconds)

## Program Flow

1. **Initialization:**
   - Initialize the mutexes for chopsticks.
   - Randomly place astronomers around the table, ensuring the specified number of asymmetric astronomers.

2. **Thread Creation:**
   - Each astronomer is represented by a thread that executes the `philosopher` function.

3. **Philosopher Function:**
   - Continuously attempts to pick up chopsticks based on whether they are symmetric or asymmetric.
   - Eats if both chopsticks are successfully acquired.
   - Thinks if unable to acquire chopsticks.

## Compilation and Execution

To compile and run the program:

1. Ensure you have a C compiler (e.g., `gcc`) installed on your system.
2. Save the source code to a file, say `dining_astronomers.c`.
3. Open a terminal and navigate to the directory containing `dining_astronomers.c`.
4. Compile the code:

    ```sh
    gcc -pthread -o dining_astronomers dining_astronomers.c
    ```

5. Run the compiled program:

    ```sh
    ./dining_astronomers
    ```

## Example Output
 - Asymmetric astronomer 1 picked up the right chopstick
 - Asymmetric astronomer 1 picked up the left chopstick
 - Asymmetric astronomer 1 is eating
 - Asymmetric astronomer 2 picked up the right chopstick
 - Asymmetric astronomer 2 picked up the left chopstick
 - Asymmetric astronomer 2 is eating
 - Symmetric astronomer 3 picked up the left chopstick
 - Symmetric astronomer 3 picked up the right chopstick
 - Symmetric astronomer 3 is eating

## Notes

- The output will vary on each run due to the random placement of astronomers and the stochastic nature of their actions.
- The program runs indefinitely. You can stop it by pressing `Ctrl+C`.





