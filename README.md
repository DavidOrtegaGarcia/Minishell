# Minishell - 42 Project

This project is part of the 42 curriculum. The main objective is to create a **simple shell**, a mini Bash clone. The goal is to learn about **processes**, **file descriptors**, **signals**, and system calls by rebuilding a command-line interpreter from scratch in C.

## 🏗 Architecture
The shell works through a continuous loop (Read-Eval-Print Loop) structured into four main phases:

* **Tokenizer:** Scans the raw input string and breaks it down into tokens (words, pipes, redirections).
* **Parser:** Analyzes the tokens to build an Abstract Syntax Tree (AST) or a command table, handling grammar, quotes, and environment variables.
* **Expander:** Processes the parsed commands before execution, expanding environment variables (e.g., `$USER`, `$??`), handling exit statuses, and stripping quotes.
* **Executor:** Executes the commands by managing forks, duplicating file descriptors, and tracking process IDs.
* **Builtins:** Internal shell commands executed directly within the parent process to modify the shell state.

## 🚀 Prerequisites
To compile and run this project, you must have the following installed:
* [GCC](https://gcc.gnu.org/)
* [Make](https://www.gnu.org/software/make/)
* [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)

## 🏗 Project Structure
The project is organized with the automation setup (`Makefile`) at the root level, custom libraries, and the source code inside the `src` directory:

```text
.
├── Makefile            # Automation setup and compiler manager
├── .gitignore          # Git exclusion file
├── libft/              # 42 standard library extension
├── libs/               # Header files directory
│   └── minishell.h     # Main project configuration header
└── src/                # Source code files (.c)
```

## ⚙️ Configuration & Features
Minishell replicates a subset of Bash features. Before running it, ensure you understand the supported mechanics:

* **Built-in Commands:** The shell handles the following builtins internally without invoking external binaries:
```text
  echo    -> with option -n
  cd      -> with only a relative or absolute path
  pwd     -> with no options
  export  -> with no options
  unset   -> with no options
  env     -> with no options or arguments
  exit    -> with no options
```

* **Redirections & Pipes:** Commands can be chained and their inputs/outputs redirected using standard operators:
```bash
  |   -> Pipes the output of one command into the input of the next
  <   -> Redirects standard input from a file
  >   -> Redirects standard output to a file (truncates)
  >>  -> Redirects standard output to a file (appends)
  <<  -> Heredoc (reads input until a specific delimiter is met)
```

## 📊 Environment & Signal Management
To ensure the shell behaves like a real terminal, it replicates environment tracking and standard terminal interruptions:

* **Environment Variables:** Transmitted from the parent shell, they expand dynamically when using `$` (e.g., `$USER` or the exit status via `$?`).
* **Signal Handling:** Intercepts system interrupts to match Bash behavior (`Ctrl-C`, `Ctrl-D`, and `Ctrl-\`).

> ⚠️ **Warning:** If a command contains unclosed quotes (`'` or `"`), Minishell will automatically interpret them as closed at the end of that specific token. Additionally, unhandled metacharacters (like `;`, `\`, `&&`, or `||`) will trigger a syntax error, as they are explicitly excluded by the 42 project subject guidelines.
>
> ## 🛠 Usage
We have included a `Makefile` to simplify binary management. You can use the following commands in your terminal:

* `make` or `make all`: Compiles the source files and generates the `minishell` executable.
* `make clean`: Removes all object files (`.o`) generated during compilation.
* `make fclean`: Performs a full reset. It purges all object files and completely deletes the compiled `minishell` binary.
* `make re`: Runs `fclean` followed by `make`.

To launch the shell after compilation, simply run:
```bash
./minishell
```

## 🛡 Security & Memory Considerations
* **Memory Management:** Every allocated block of memory is tracked and freed upon command completion or shell exit to ensure **zero leaks**.
* **Process Isolation:** Child processes are safely isolated via `fork()`, ensuring that a crashing command does not crash the main Minishell prompt.
* **Error Handling:** System calls are continuously monitored; if a command fails, Minishell updates the global exit status (`$?`) accordingly.

## 👥 Collaboration
This project was developed in collaboration between:

* **[DavidOrtegaGarcia](https://github.com/DavidOrtegaGarcia):** Developed the core infrastructure, including:
  * **Expander:** Environment variable expansion (`$USER`, `$??`) and quote removal.
  * **Executor:** Process creation via `fork()`, pipeline manipulation (`|`), and complex redirections (`<`, `>`, `>>`, `<<`).
  * **Signals & Memory:** Signal intercepting (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) and leak prevention management.
  * **Builtins:** Implemented `echo`, `cd`, `pwd`, `export`, and `exit`.

* **[@richix64](https://github.com/richix64):** Developed the initial processing layers and environment features:
  * **Lexer & Tokenizer:** Scanning and breaking down the raw input into structured tokens.
  * **Parser:** Transforming tokens into the command table and validating grammar syntax.
  * **Builtins:** Implemented `env` and `unset`.
---
*Project developed as part of the 42 curriculum.*
