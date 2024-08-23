# Simple shell

**Simple shell** is a basic UNIX command-line interpreter that emulates the functionalities of a shell. It allows users to interact with the operating system by executing commands, invoking system calls, and managing environment variables. The project is implemented in C and designed for educational purposes, demonstrating the principles of shell programming and system-level programming in UNIX-like environments.

## 0. Setup

### 0.0. Requirements

To successfully build and run the Simple Shell, you need the following:

* Operating System: Ubuntu 20.04 LTS or later
* Compiler: GCC (GNU Compiler Collection)
* Version Control: Git

### 0.1. Installation

To set up the Simple Shell on your local machine, follow these steps:

1. Clone the Project Repository:

    * Clone the repository using Git to obtain the source code:

```
git clone https://github.com/Ashe2A/holbertonschool-simple_shell.git
```

2. Navigate to the Project Directory:

    * Change your current directory to the project folder:

```
cd holbertonschool-simple_shell
```

3. Compile the Program:

    * To compile the program into the ```simple_shell``` executable, input:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell
```

Flags Explained:
- Wall: Enables all compiler's warning messages.
- Werror: Treats all warnings as errors.
- Wextra: Enables additional warning messages.
- pedantic: Enforces strict ISO C compliance.
- std=gnu89: Specifies the standard to which the code should conform (GNU89).

## 1. Execution

You can run the Simple Shell in two modes: Interactive and Non-Interactive.

1. **Interactive mode:** ```./simple_shell```
    * In this mode, the shell prompts the user for input, processes the inputted commands, and displays the results. This mode continues running until the user exits (e.g., by typing exit or pressing Ctrl+D).

2. **Non interactive mode:** ```echo "ls -la /root" | ./simple_shell```
    * In this mode, the shell processes the command provided and then exits immediately after execution, without entering a loop.

## 2. Usage

### 2.0. Interactive Mode

In Interactive Mode, the Simple Shell continuously waits for user input. You can execute various commands as you would in a typical shell, such as:

- Basic Commands:

```
ls
pwd
```

- Exiting the shell

```
exit
```

### 2.1. Non interactive mode

In Non-Interactive Mode, you can input a command or a series of commands directly into the shell via a pipe or redirection:

- Single Command

```
echo "ls -l" | ./simple_shell
```

- Multiple Commands

```
echo -e "pwd\nls -l" | ./simple_shell
```

This mode is useful for scripting or automating tasks where a persistent shell session is not required.

## 3. Features

- Built-in Commands: Support for basic shell commands like exit, env, etc.
- Error Handling: The shell handles common errors gracefully, providing appropriate feedback.
- Command Execution: Supports execution of binary files and built-in shell commands.
- Path Resolution: Automatically resolves commands using the PATH environment variable.

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
