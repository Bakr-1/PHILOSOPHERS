# 💡PHILOSOPHERS

The dining philosophers problem is invented by E. W. Dijkstra.

Imagine that five philosophers who spend their lives just eating, thinking and sleeping. 

In the middle of the dining room is a circular table with five chairs.

The table has a big plate of spaghetti. However, there are only five forks available.

Each philosopher thinks. When he gets hungry, he sits down and picks up the two forks that are closest to him.

If a philosopher can pick up both forks, he eats for a while. After a philosopher finishes eating, he puts down the forks and starts to sleep and think.

# ℹ️Overview
  • One or more philosophers sit at a round table.
  
  There is a large bowl of spaghetti in the middle of the table.
  
  • The philosophers alternatively eat, think, or sleep.
  
  While they are eating, they are not thinking nor sleeping;
  
  while thinking, they are not eating nor sleeping;
  
  and, of course, while sleeping, they are not eating nor thinking.
  
  • There are also forks on the table. There are as many forks as philosophers.
  
  • Because serving and eating spaghetti with only one fork is very inconvenient, a
  
  philosopher takes their right and their left forks to eat, one in each hand.
  
  • When a philosopher has finished eating, they put their forks back on the table and
  
  start sleeping. Once awake, they start thinking again. The simulation stops when
  
  a philosopher dies of starvation.
  
  • Every philosopher needs to eat and should never starve.
  
  • Philosophers don’t speak with each other.
  
  • Philosophers don’t know if another philosopher is about to die.
  
  • No need to say that philosophers should avoid dying!

# ❗️REQUIREMENT 

• Your(s) program(s) should take the following arguments:

number_of_philosophers time_to_die time_to_eat time_to_sleep

[number_of_times_each_philosopher_must_eat]

  ◦ number_of_philosophers: The number of philosophers and also the number
  of forks.
  
  ◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
  milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
  
  ◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
  During that time, they will need to hold two forks.
  
  ◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
  
  ◦ number_of_times_each_philosopher_must_eat (optional argument): If all
  
  philosophers have eaten at least number_of_times_each_philosopher_must_eat
  
  times, the simulation stops. If not specified, the simulation stops when a
  philosopher dies.
  
• Each philosopher has a number ranging from 1 to number_of_philosophers.

• Philosopher number 1 sits next to philosopher number number_of_philosophers.

Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

About the logs of the program:

  • Any state change of a philosopher must be formatted as follows:
  
    ◦ timestamp_in_ms X has taken a fork
    
    ◦ timestamp_in_ms X is eating
    
    ◦ timestamp_in_ms X is sleeping
    
    ◦ timestamp_in_ms X is thinking
    
    ◦ timestamp_in_ms X died

Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
  • A displayed state message should not be mixed up with another message.
  
  • A message announcing a philosopher died should be displayed no more than 10 ms
  
  after the actual death of the philosopher.
  
  • Again, philosophers should avoid dying
  
  ⚠️ Your program must not have any data races. ⚠️
  
  • Each philosopher should be a thread.
 
 • There is one fork between each pair of philosophers. Therefore, if there are several
 
   philosophers, each philosopher has a fork on their left side and a fork on their right

   side. If there is only one philosopher, there should be only one fork on the table.
 
 • To prevent philosophers from duplicating forks, you should protect the forks state
  with a mutex for each of them.
  
# 👨‍💻Usage

The function is written in C language and thus needs the gcc compiler and some standard C libraries to run.

Compiling the project

To compile, clone the repository and run the following inside the folder:
```bash
$>make
```

The program will be executed as follows:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
with the number of times each philosopher must eat is optional.

as an additional step you can have multiple test cases in the Makefile from t1-t6 and can be executed as follows:
```bash
$>make t1
philo will die after 800
./philo 1 800 200 200
802 Philo 1 died 😵
```
and so on
