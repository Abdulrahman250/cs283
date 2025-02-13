1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  fgets() safely reads user input, preventing buffer overflow by specifying a maximum length. It handles spaces and reads the entire line, including the newline character, which can be removed later.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  malloc() allows dynamic memory allocation based on user input, ensuring flexibility to handle input of varying lengths and preventing memory waste.

3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  Trimming spaces ensures commands are parsed correctly. Untrimmed spaces could cause issues with command execution and argument parsing.

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  Redirection examples include > output.txt which redirects output to a file, < input.txt which redirects input from a file, and >> output.txt which appends output to a file.

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:  Redirection alters input/output destinations (like files), while piping connects commands so one’s output becomes the next’s input.

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  Keeping them separate allows easier debugging and handling of errors, ensuring clarity in output vs. error messages.

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  Errors should be reported clearly. If merging STDOUT and STDERR, use &>, which sends both streams to the same destination, improving error handling.