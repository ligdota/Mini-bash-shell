# Mini-bash-shell

`Mini-bash-shell` is a small Unix-style shell written in C. The project focuses on process creation, command parsing, pipelines, redirection, and basic job handling without relying on standard external libraries.

## Features

- executes commands found through `PATH`
- supports direct executable paths
- supports pipelines using `|`
- supports input and output redirection with `<` and `>`
- runs foreground and background jobs
- includes built-in `cd` and `exit` commands
- keeps track of process group IDs for launched jobs

## Build

```bash
make
```

This produces an executable named `mysh`.

## Run

```bash
./mysh
```

The shell prints the current working directory as part of its prompt and then waits for user commands.

## Repository Layout

- `myshell.c`: main REPL loop and terminal/job control setup
- `command.c`: built-in handling and external command execution
- `pipeline.c`: pipe setup plus redirection wiring
- `job.c`: parsing of background execution and redirection options
- `cmdPath.c`: command lookup through `PATH`
- `pgidTracker.c`: tracking process groups for running jobs
- `myString.c` and `myMem.c`: custom string and allocation helpers

## Limitations

The code includes placeholders for `fg`, `bg`, and `kill`, i.e job-control is only partially implemented.
