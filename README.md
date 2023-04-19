# Tape Simulator

It is simple tape simulator. It can sort your tape (kinda merge sort is used).

## How to use

```
$ git clone git@github.com:matmuher/tape_simulator.git

$ cd tape_simulator && mkdir -p build && cd build && cmake .. && make

$ cd ../bin

$ echo "0 0 0" > config.txt

$ echo "1 2 3 -1 -2 -3" > input_tape.txt

$ ./TapeSorter input_tape.txt output_tape.txt

$ cat output_tape.txt
```

You should get:

```
-3 -2 -1 1 2 3 
```


## How to configure

To configure simulator create 'config.txt' file in the folder with executable.

You should put there 3 numbers:

1. Read time delay
2. Write time delay
3. Move time delay

All times are in seconds.

For example:

*config.txt*:

```
1
1
5
```

## Very basic tests

To run tests it's enough to make all steps from [How to use](#how-to-use) section. In the same /bin directory you should do:

```
$ ./test_sort
```