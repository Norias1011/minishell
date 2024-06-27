# MiniShell Project

Welcome to the MiniShell project! This repository contains the source code for a simple UNIX-like shell, designed as a learning project to understand the basics of shell programming and operating system concepts.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)

## Introduction

The MiniShell is a minimalist shell implementation that provides basic command execution features. It serves as an educational tool to help developers understand how shells work, including command parsing, execution, and simple I/O redirection.

## Features

- Basic command execution (e.g., `ls`, `echo`, `cat`)
- Input and output redirection (e.g., `>` and `<`)
- Piping between commands (e.g., `ls | grep mini`)
- Environment variable handling (e.g., `export VAR=value`)
- Simple built-in commands (e.g., `cd`, `exit`)

## Installation

To install and run MiniShell, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/minishell.git
    ```
2. Navigate to the project directory:
    ```sh
    cd minishell
    ```
3. Compile the source code:
    ```sh
    make
    ```

## Usage

To start using MiniShell, run the compiled executable:

```sh
./minishell
```

You can then start typing commands just like you would in any other shell. For example:

```sh
minishell> ls -l
minishell> echo "Hello, world!"
minishell> cat < input.txt > output.txt
minishell> ls | grep mini
```

## Built-in Commands

MiniShell supports several built-in commands, including:

- `cd [directory]`: Change the current directory.
- `export VAR=value`: Set an environment variable.
- `unset VAR`: Unset an environment variable.
- `exit [status]`: Exit the shell with an optional status code.

---

Thank you for using MiniShell! If you have any questions or issues, feel free to open an issue on GitHub. Happy coding!
