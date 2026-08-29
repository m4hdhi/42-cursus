*This project has been created as part of the 42 curriculum by mamuzamm.*

# Philosophers (philo)

## Description

The **Philosophers** project is a simulation of the classic Dining Philosophers problem, a well-known concurrency exercise used to study synchronization and resource sharing in multi-threaded systems.

In this project, each philosopher is represented by a thread that repeatedly performs three actions: thinking, eating, and sleeping. Forks are shared resources protected by mutexes to prevent race conditions and inconsistent states. A monitoring mechanism ensures that philosophers do not starve and that the simulation stops correctly when a philosopher dies or when all philosophers have eaten the required number of times.

The main goal of this project is to understand and implement:
- Multithreading using POSIX threads (pthread)
- Mutex-based synchronization
- Deadlock and race condition prevention
- Precise time management in concurrent programs
- Clean and norm-compliant C code following the 42 coding standard

---

## Instructions

### Compilation

From the `philo/` directory, compile the program using:

```bash
make
```

To remove object files:

```bash
make clean
```

To remove all generated files:

```bash
make fclean
```

To recompile the project:

```bash
make re
```

---

### Execution

Run the program with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

#### Example:

```bash
./philo 5 800 200 200
```

With an optional argument:

```bash
./philo 5 800 200 200 7
```

---

### Arguments

| Argument | Description |
|---------|------------|
| number_of_philosophers | Number of philosophers and forks |
| time_to_die | Time in milliseconds before a philosopher dies if they do not eat |
| time_to_eat | Time in milliseconds spent eating |
| time_to_sleep | Time in milliseconds spent sleeping |
| number_of_times_each_philosopher_must_eat | Optional: simulation stops when all philosophers have eaten this many times |

---

## Program Behavior

- Each philosopher is executed in a separate thread.
- Forks are represented as mutexes to ensure exclusive access.
- A monitor thread continuously checks:
  - If a philosopher has died due to starvation.
  - If all philosophers have eaten the required number of times (if specified).
- All state changes are logged with timestamps in milliseconds.
- The program avoids data races and deadlocks through controlled locking strategies.

---

## Technical Choices

- **Threads:** Each philosopher runs in its own thread using `pthread_create`.
- **Mutexes:** Forks and shared state variables are protected using mutexes.
- **Deadlock prevention:** Fork acquisition follows a consistent locking order.
- **Timing:** A custom sleep function ensures accurate timing without blocking the monitor thread.
- **Monitoring:** A dedicated monitor thread detects philosopher death and termination conditions.
- **Synchronization:** Shared variables such as `last_meal` and death flags are protected by mutexes.

---

## Example Output

```text
0 1 has taken a fork
1 1 has taken a fork
2 1 is eating
202 1 is sleeping
402 1 is thinking
600 2 died
```

---

## Resources

### References

- POSIX Threads documentation  
  https://man7.org/linux/man-pages/man7/pthreads.7.html

- pthread mutex documentation  
  https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html

- Dining Philosophers Problem  
  https://en.wikipedia.org/wiki/Dining_philosophers_problem

- 42 Philosophers Subject (official project specification)

---

### AI Usage

Artificial Intelligence tools were used as supportive resources during the development of this project for:

- Understanding concurrency concepts and synchronization mechanisms
- Debugging potential race conditions and deadlocks
- Improving code structure and readability
- Drafting and refining documentation

All core implementation logic, architectural decisions, and final code integration were performed manually by the author, who fully understands and takes responsibility for the project.

---

## Notes

This project follows the mandatory requirements of the 42 Philosophers subject:
- No global variables
- No data races
- Proper thread synchronization
- Accurate timing and logging
- Norminette-compliant C code
