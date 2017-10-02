# Assignment 1
## Alex Abrahamson - 10/2/17

This is the programming assignment 1 written by Alex Abrahamson

### Invocation
To invoke the **circular** executable, simply perform the following:
```
$ ./circular input.txt
```
Where input.txt is a properly formatted (for **circular**) .txt file. The contents of **input.txt** are the table from the assignment description.

### Compiling (not really necessary)
If the provided **circular** executable does not work/run, then compile **circular.c** with 
```
$ gcc -Wall circular.c -o circular
```

### Creating input
The **circular** executable requires a .txt file as input. I have provided the default one from the assignment 1 description, but if you want to make one yourself there are three requirements.

  1. Each line should correspond to the job's number
  2. The contents of each line should be the jobs arrival time and processing time
  3. The arrival time and processing time must be separated by a space

