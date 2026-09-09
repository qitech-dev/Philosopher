*This project has been created as part of the 42 curriculum by qijin.*

# Philosophers

## Description

**Philosophers** is a simulation of the Dining Philosophers problem, a classic concurrency exercise. A group of philosophers sit around a table and repeatedly eat, sleep, and think. There is one fork between each pair of philosophers, and each philosopher needs both adjacent forks to eat.

The goal is to coordinate the philosophers without data races or deadlocks while detecting starvation quickly and keeping the program's output synchronized.

This implementation covers the mandatory part of the project:

- each philosopher is represented by a POSIX thread;
- each fork is protected by its own mutex;
- shared simulation state and console output are protected by mutexes;
- a monitor checks for death and for completion of the optional meal target;
- all allocated memory and initialized mutexes are released on exit.

## How It Works

The main thread creates one thread per philosopher, initializes their last-meal times, and releases them through a shared start flag so that they begin from the same reference time.

Each philosopher then repeats the following cycle:

1. take the two adjacent forks;
2. eat and update the protected meal data;
3. release both forks;
4. sleep;
5. think.

To prevent circular waiting, odd-numbered philosophers take their left fork first while even-numbered philosophers take their right fork first. Even-numbered philosophers also begin with a short delay, which reduces initial contention.
For an odd number of philosophers, an additional thinking delay helps distribute access to the forks more evenly.

The main thread monitors every philosopher's `last_meal_time`. The simulation ends when a philosopher dies, or when every philosopher has reached the optional meal count. A dedicated write mutex prevents log messages from overlapping and ensures that only one death is printed.

The single-philosopher case is handled separately: the philosopher can take the only available fork but cannot eat, so the simulation ends when they starve.

## Instructions

### Requirements

- a C compiler such as `cc` or `clang`;
- GNU Make;
- POSIX threads support.

### Compilation

```sh
make
```

This creates the `philo` executable. Other available rules are:

```sh
make clean    # remove object files
make fclean   # remove object files and the executable
make re       # rebuild the project from scratch
```

### Execution

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
    [number_of_times_each_philosopher_must_eat]
```

All times are expressed in milliseconds. Every argument must be a positive integer.

| Argument | Meaning |
| --- | --- |
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Maximum time since the start of the last meal before death |
| `time_to_eat` | Time spent eating while holding two forks |
| `time_to_sleep` | Time spent sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional meal target for every philosopher |

### Examples

```sh
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 1 800 200 200
```

The second command stops when every philosopher has completed at least seven meals, unless a philosopher dies first.

Output follows the format required by the subject:

```text
timestamp_in_ms philosopher_id has taken a fork
timestamp_in_ms philosopher_id is eating
timestamp_in_ms philosopher_id is sleeping
timestamp_in_ms philosopher_id is thinking
timestamp_in_ms philosopher_id died
```

## Project Structure

| File | Responsibility |
| --- | --- |
| `main.c` | Argument parsing, initialization, simulation launch, and cleanup |
| `check_functions.c` | Numeric validation and argument parsing |
| `init_functions.c` | Allocation and mutex/philosopher initialization |
| `simulation.c` | Thread creation, synchronized start, monitoring, and joining |
| `threads.c` | Philosopher routine and special handling for one philosopher |
| `forks.c` | Fork selection, locking, and release |
| `actions.c` | Eating, sleeping, and thinking actions |
| `monitor.c` | Starvation and meal-target checks |
| `state.c` | Thread-safe access to shared start and stop flags |
| `print_functions.c` | Synchronized status and death messages |
| `tools.c` | Time measurement and interruptible sleep helpers |
| `cleanup.c` | Mutex destruction and memory cleanup |
| `philo.h` | Structures, includes, and function prototypes |

## Technical Choices

- **One mutex per fork:** prevents two neighboring philosophers from holding the
  same fork simultaneously.
- **Per-philosopher meal mutex:** protects `last_meal_time` and `meals_eaten`
  from concurrent access by the philosopher and the monitor.
- **Shared state mutex:** protects the start and stop flags.
- **Write mutex:** serializes output and suppresses status messages after the
  simulation has stopped.
- **Absolute eating deadlines:** eating sleeps until `meal_start + time_to_eat`
  to limit timing drift.
- **Short polling intervals:** sleep helpers and the monitor check the stop state
  regularly so threads can terminate promptly.

## Resources

- [The Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX threads overview - Linux man-pages](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [`pthread_create(3)` - Linux man-pages](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [`pthread_mutex_lock(3p)` - POSIX manual](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [`gettimeofday(2)` - Linux man-pages](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

### Use of AI

AI was used as a learning and review aid during the project: to clarify threading and mutex concepts, suggest debugging and test cases, review possible race and resource-cleanup issues, and help organize this README. Suggestions were checked against the subject and the actual source code before being kept. The final code and its behavior remain the author's responsibility.
