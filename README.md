# Simple shell
**Simple shell** is, akin to a shell, an UNIX command line interpreter, used to interact with the operating system with commands, system calls and environment variables.

## 0. Setup
### 0.0. Requirements
* An Ubuntu 20 or later operating system
* GCC (GNU Compiler Collection)
* Git

### 0.1. Installation
* To clone the project repository, input:
```
git clone https://github.com/Ashe2A/holbertonschool-simple_shell.git
```

* To compile the program into the ```simple_shell``` executable, input:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell
```

## 1. Execution
To start the simple shell, type either of the following :
* **Interactive mode:** ```./simple_shell```
    * Executes the ```simple_shell``` executable, which loops
* **Non interactive mode:** ```echo "ls -la /root" | ./simple_shell```
    * Inputs a command output to the ```simple_shell``` executable, hence not looping

## 2. Usage
### 2.0. Interactive mode

### 2.1. Non interactive mode

```mermaid
flowchart
    start(["Start<br>(main())"]) --> interact{"Interactive?"}
    interact -- true --> prompt("Print prompt<br>(current/path/$ )")
    prompt --> getline("Read user input<br>(getline())")
    interact -- false --> getline
    getline -- EOF (Ctrl + D) --> EOF(["Exit<br>(exit())"])
    getline --> tokenize("Tokenize input<br>(tokenize())")
    tokenize --> builtin_check{"Built-in?<br>(env, exit)"}
    builtin_check -- false --> full_path_check{"Full path?"}
    builtin_check -- true --> builtin_run("Run built-in")
    builtin_run --> reset_ressources
    full_path_check -- true --> fork("Create child process<br>(fork())")
    fork --> fork_check{"Child?<br>if (getpid() == 0)"}
    fork_check -- true --> execve("Execute environment variable<br>(execve())")
    fork_check -- false --> wait("Wait for child(ren) process(es) to end<br>wait(&status)")
    full_path_check -- false --> build_path("Search for PATH")
    build_path --> fork
    wait --> reset_ressources("Reset ressources<br>(free())")
    reset_ressources --> interact

    style start stroke:#FC0,fill:#FFD,color:#A80
    style EOF stroke:#FC0,fill:#FFD,color:#A80

    style interact stroke:#C0F,fill:#ECF,color:#80A
    style builtin_check stroke:#C0F,fill:#ECF,color:#80A
    style full_path_check stroke:#C0F,fill:#ECF,color:#80A
    style fork_check stroke:#C0F,fill:#ECF,color:#80A

    style prompt stroke:#0CF,fill:#CEF,color:#08A
    style getline stroke:#0CF,fill:#CEF,color:#08A
    style tokenize stroke:#0CF,fill:#CEF,color:#08A
    style builtin_run stroke:#0CF,fill:#CEF,color:#08A
    style fork stroke:#0CF,fill:#CEF,color:#08A
    style build_path stroke:#0CF,fill:#CEF,color:#08A
    style execve stroke:#0CF,fill:#CEF,color:#08A
    style reset_ressources stroke:#0CF,fill:#CEF,color:#08A
    style wait stroke:#0CF,fill:#CEF,color:#08A
```

<small>(See the project authors in the ```AUTHORS``` file)</small>