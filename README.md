# Pipex Project

## Overview
The Pipex project is part of the 42 Network curriculum, aiming to deepen the understanding of Unix processes, inter-process communication, and file descriptor manipulation. This project mimics the behavior of the Unix pipe operator `|`, allowing the output of one command to be used as the input for another.

## Features

### Mandatory Part
- **Single Pipe with Two Commands**: Implements the functionality of a single pipe that connects the output of one command to the input of another.
  - Example: `./pipex file1 cmd1 cmd2 file2` should behave like `cat file1 | cmd1 | cmd2 > file2`.

### Bonus Part
- **Multiple Pipes**: Extends the functionality to handle multiple pipes, allowing for more complex command sequences.
  - Example: `./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2` should behave like `cat file1 | cmd1 | cmd2 | cmd3 | ... | cmdN > file2`.
- **Here-Document (heredoc)**: Adds support for the heredoc feature, allowing input to be provided directly in the command line.
  - Example: `./pipex here_doc LIMITER cmd1 cmd2 file2` should take input until `LIMITER` is found and then execute the commands.

## Usage

### Compilation
Compile the project using the provided `Makefile`:
```sh
make
for mandatory:
./pipex file1 cmd1 cmd2 file2
for bonus:
./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2
./pipex here_doc LIMITER cmd1 cmd2 file2
Mandatory Example
./pipex infile "ls -l" "wc -l" outfile
This will read the content of infile, execute ls -l, then pipe its output to wc -l, and finally write the result to outfile.

Bonus Examples
Multiple Pipes
./pipex infile "grep '42'" "sort" "uniq" outfile
This will execute grep '42' on infile, pipe its output to sort, then pipe the result to uniq, and write the final output to outfile.

Here-Document
./pipex here_doc EOF "cat" "grep 42" outfile
