1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

The shell uses waitpid() on each child process to ensure all processes finish before continuing. Without waitpid(), leftover processes could keep running and waste resources.

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

Unused pipe ends must be closed to avoid leaks and deadlocks. Open pipes may cause processes to hang indefinitely, waiting for input or output that will never come.

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

The cd command is built-in because it changes the shell’s current directory. If implemented as an external command, it would only change the directory of the child process, leaving the parent shell’s directory unchanged.

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

Replace the fixed-size pipe array with dynamic allocation malloc(). Similarly, dynamically allocate the command list. The trade-offs include increased complexity, increased memory usage, and the need for careful memory management.