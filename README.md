# philosophers

**A project of School 21.**

In this project I had to make a simulation of a "dining philosophers" problem. It was solved by using threads and mutexes.

Philosophers are sitting at the round table with a large bowl of endless spaghetti in the center.

There are forks between every 2 philosophers (number of forks = number of philosophers).

Philosophers can eat only if they take both nearby forks.

After eating, they fall asleep.

After sleeping, they want to eat at once. While philosophers can't take their forks, they eat.

If a philosopher can't eat for certain time, he dies, and the simulation stops.

Installation:

```
$ git clone https://github.com/vadsamokh/philosophers && cd philosophers && make
```

Launch:

```
$ ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```
$ ./philo 4 600 200 200
```
