# 42-minishell 🐚
* [Introduction](#Introduction 💻)
* [Usage](#Usage ❓)
* [Features](#Features 📃)

# Introduction 💻

The objective of this project is to create a simple shell.

# Usage ❓

1. Clone the repo `git clone git@github.com:zcanales/42-minishell.git`
2. Install Readline library `sh install_readline.sh`
3. Compile Minishell `make`
4. Run `./minishell`

# Features 📃
### Basics:
- Working History.
- Search and launch the right executable (based on the PATH variable or by using a relative or an absolute path).
- Environment variables ($ followed by a sequence of characters) expand to their values.
- ```’``` (single quotes: inhibit all interpretation of a sequence of characters).
- ```"``` (double quotes: inhibit all interpretation of a sequence of characters except for $.)
- ```$?``` expand to the exit status of the most recently executed foreground pipeline.
- ```|```  Pipes: The output of each command in the pipeline is connected via a pipe to the input of the next command.
- ctrl-C, ctrl-D and ctrl-\ work like in bash.

### Redirections: 
- ```< file```: Redirect Input.
- ```> file```: Redirect Output.
- ```<< file```: Read Input from the current source until a line containing only the delimiter is seen.
- ```>> file```: Redirect Output with append mode.

### Builtins
- ```echo``` with option -n.
- ```cd``` with only a relative or absolute path.
- ```pwd``` without options.
- ```export``` without options.
- ```unset``` without options.
- ```env``` without options.
- ```exit``` without options
