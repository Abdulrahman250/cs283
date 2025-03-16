1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

The remote client detects the end of a command's output by checking for a EOF character (0x04). It handles partial reads with multiple recv() calls until the EOF character is received.

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

A network shell protocol can use delimiters to define message boundaries. Without this, commands may be split, merged, or misinterpreted.

3. Describe the general differences between stateful and stateless protocols.

Stateful protocols maintain session information, while stateless protocols do not. Stateful protocols track the state across requests, whereas stateless protocols treat each request independently.

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

We would use it for for applications that prioritize speed over reliability.

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

The operating system provides a socket API to enable applications to send and receive network data.