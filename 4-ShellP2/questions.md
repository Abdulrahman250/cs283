1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**:  Fork creates a child process so that execvp can replace the child's image without terminating the shell. This separation lets the shell remain active to accept new commands while the child executes the external command.

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  If fork() fails, it returns -1. In our implementation, we check the return value; upon failure, we print an error message (using perror) and return an error code to prevent further execution.

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  execvp() searches for the command in the directories listed in the PATH environment variable, looking for an executable file that matches the given command name.

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  wait() makes the parent process block until the child process terminates, ensuring proper cleanup. Without it, terminated children become zombie processes, and the parent wouldn’t reliably know when the command has finished.

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**:  WEXITSTATUS() extracts the exit status from the child's termination status. This is important to determine if the command executed successfully (exit status 0) or if an error occurred.

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**:  The build_cmd_buff() function handles quoted arguments by using an in_quotes flag to ignore spaces inside quotes and treat quoted content as a single token. This is necessary to correctly parse arguments with spaces, like file paths or phrases, as single units.

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  The updated code enhances the command loop by handling built-in commands, parsing input with proper whitespace management, and ensuring correct tokenization of arguments. The only challenge were managing memory efficiently and handling edge cases with quoted arguments.

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**:  Signals in Linux are used for inter-process communication (IPC), enabling processes to send notifications to each other. They differ from other IPC methods like pipes and message queues, as they are asynchronous and can interrupt a process to handle specific events, such as errors or user requests.

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:  SIGKILL terminates a process immediately and cannot be caught or ignored. SIGTERM can be caught or ignored and is used for graceful termination. SIGINT interrupts a process (via Ctrl+C) and can be caught to allow custom handling.

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**:  When a process receives SIGSTOP, it is paused and cannot be caught or ignored. This is a special signal designed to stop the process unconditionally, unlike SIGINT which can be caught.