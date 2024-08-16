# Simple shell
<small>(See authors in the ```AUTHORS``` file)</small>

## 1. Execution
To start the simple shell, type ```./simple_shell```

## 2. Usage
The simple shell works akin to a true shell with some differences:

1. The shell creates a child process (with ```fork()```);

2. It waits for an input (```stdin```);

3. One shall enter a command (for example : ```/usr/bin/ls``` or ```usr/bin/ls -la /root```). The command name must indeed be the full path to the corresponding binary;

4. The simple shell recognizes the command and executes it using the newly forked process' environment (see the Managing environments tab below);

5. It loops back to the first step (```while (1)```).

It has to be noted that **simple shell 0.1** didn't work with arguments, and **simple shell 0.2** implemented that functionality.

## 2. Managing environments
### 2.1. Environment used <small>(simple shell ver. 0.2)</small>
The simple shell uses the same environments used in the initial process it is called in, by duplicating it through global variables. However, the environment variables of the simple shell's process can be changed by writing the binaries or the ```PATH``` file (it will not change the parent process' environment).

### 2.2. Check environment (simple shell ver. 1.0)
You might want to check the environment variables and their content. To do so, simply input ```env```

## 3. Close simple shell (simple shell ver. 0.4)
To close the simple shell, simply type the ```exit``` command as-is.
