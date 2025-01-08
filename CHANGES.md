# Signal Handling and Terminal Control Changes

## Overview
These changes improve signal handling, terminal control, and process group management in the shell implementation.

## Modified Files

### signals.c
- Simplified signal handling
- Added terminal control attributes
- Removed problematic terminal settings
- Added handling for SIGTTIN and SIGTTOU
- Disabled ECHOCTL to prevent ^C from showing

### main.c
- Added proper terminal control initialization
- Implemented job control setup
- Added signal handling for terminal control signals
- Ensured shell gains control of terminal at startup
- Properly initialized process group

### executioner.c
- Improved child process signal handling
- Added proper process group management
- Fixed terminal control transfer between processes
- Added waitpid with WUNTRACED for proper child process handling
- Improved parent process terminal control management

## Key Changes

### Signal Handling
```c
// New signal setup
signal(SIGTTIN, SIG_IGN);
signal(SIGTTOU, SIG_IGN);
signal(SIGTSTP, SIG_IGN);
```

### Terminal Control
```c
// Terminal control initialization
while (tcgetpgrp(STDIN_FILENO) != getpgrp())
    kill(getpid(), SIGTTIN);
setpgid(0, 0);
tcsetpgrp(STDIN_FILENO, getpgrp());
```

### Process Management
```c
// Child process setup
setpgid(0, 0);
if (!is_pipe)
    tcsetpgrp(STDIN_FILENO, getpid());

// Parent process management
setpgid(pid, pid);
if (!is_pipe) {
    tcsetpgrp(STDIN_FILENO, pid);
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());
}
```

## Testing
1. Verify Ctrl+C works properly in both shell and child processes
2. Check that Ctrl+Z (SIGTSTP) is properly ignored
3. Ensure background processes don't take control of terminal
4. Verify shell doesn't get suspended unexpectedly

## Known Issues
- Terminal control might need adjustment dfor certain edge cases
- Signal handling in pipelines might need further testing
- Some terminal attributes might need fine-tuning based on specific use cases
