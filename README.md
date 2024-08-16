# Simple shell
See authors in the AUTHORS file

## 1. Execution
```
./simple_shell
```

## 2. Usage
The simple shell works akin to a true shell with some differences:
* The shell creates a child process (fork());
* It waits for an input (stdin);
* One shall enter a command (for example "/usr/bin/ls" or "usr/bin/ls -la /root") The command name must indeed be the full path to the corresponding binary;
* The simple shell recognizes the command
* It loops back to the first step

It has to be noted that simple shell 0.1 didn't work with arguments, and simple shell 0.2 implemented that functionality.

## 2. Environments
### 2.1. Environment used (simple shell ver. 0.2)
The simple shell uses the same environments used in the initial process it is called in, by duplicating it through global variables. However, the environment variables of the simple shell's process can be changed (it will not change the parent process' environment).

### 2.2. Check environment (simple shell ver. 1.0)
You might want to check the environment variables and their content. To do so, simply input the following command :
```
env
```

## 3. Close simple shell (simple shell ver. 0.4)
To close the simple shell, simply type the exit command as-is.

```
exit
```
