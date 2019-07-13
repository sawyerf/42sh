# 42sh

*Contributors: [Kais](https://github.com/kaistlili), [Alaë](https://github.com/sawyerf), [Julien](https://github.com/juhallyn), [Theo](https://github.com/theduv)*

## Description
42sh, is the compilation of projects minishell, 21sh and 42sh. It consists of reproducing the behaviour of bash in C during 5 months with 4 team members. This project gave us the opportunity to learn all the moving parts of a shell \(lexer, parser, execution, job control, readline, variables, etc\) and perfect our knowledge in the bash scripting language. Along with the main part we made some [features and bonus\.](#features-and-bonus)

## How it works ?
The execution pipeline of the shell starts with the readline module wich handles line editing, all terminal interactions and signal handling while the user is entering input, it then passes the user input to the lexer that scans the command line yielding a list of tokens that are then passed to the parser for syntatic analysis. After input validation by the parser, an abstract syntax tree is generated and passed to the interpretation module that evaluates the newly created tree, when a tree node is not bypassed by a logical operator ('&&' or '||'), the corresponding command pipeline is passed to the expansion module for variable substitution, parameters expansion, filename expansion and pattern matching. The execution submodule then sets the appropriate environment variables, redirections, pipes and job control (if required) before launching each command in the pipeline. The shell optionally waits for the executed pipeline to be finished before navigating further in the tree.

## Features and Bonus
- History
  - fc builtins
  - ! expansions
  - History File
  - Ctrl+R
- Autocompletions
  - Contextual and dynamic
- Quoting
  - `"`, `'`, `\`
- Tilde and additional parameter
  - ${var:para}
- Globbing
  - `*`, `!`, `[]`, `?`
- Alias
- Customization of the prompt
- Hash table for retrieving binaries in $PATH
- Builtins are POSIX compliant

## Builtins
- set/unset
- export
- exit
- fc 
- type
- alias
- fg/bg
- hash
- cd

## READLINE
### Return
| info | status | str |
|:----:|:------:|:---:|
|malloc| MEMERR |  ?  |
|error |   -2   |  ?  |
|error |   -1   |  ?  |
|  OK  |    0   | cmd |
|Ctrl+D|    1   | NULL|
|Ctrl+C|    2   | NULL|

### Keys

|  keys                                | description        |
|:------------------------------------:|--------------------|
| <kbd>^</kbd><br><kbd>v</kbd>                         | Browse the history |
| <kbd>Shift</kbd>+<kbd><</kbd><br><kbd>Shift</kbd>+<kbd>></kbd><br>    | Move one word      |
| <kbd>end</kbd>/<kbd>ctrl</kbd>+<kbd>e</kbd>         | Line forward       |
| <kbd>end</kbd>/<kbd>ctrl</kbd>+<kbd>a</kbd>         | Line backward      |
| <kbd>tab</kbd>                       | Autocompletion     |
| <kbd>ctrl</kbd>+<kbd>l</kbd>         | Clear the terminal |
| <kbd>ctrl</kbd>+<kbd>d</kbd>         | Exit the shell     |
| <kbd>ctrl</kbd>+<kbd>r</kbd>         | Search a command   |
| <kbd>ctrl</kbd>+<kbd>v</kbd>         | Visual mode        |
| <kbd>ctrl</kbd>+<kbd>p</kbd>         | Paste              |
| <kbd>ctrl</kbd>+<kbd>x</kbd>         | Cut                |
| <kbd>ctrl</kbd>+<kbd>y</kbd>         | Copy               |

# PARSER/LEXER
### Mode
|nb|      mode      |description|
|:-:|-|-|
|2 |    MODEFILE    |quand stdin est fermé|
|1 |   INTERACTIVE  |appele readline quand la commande n'est pas complete |
|0 | NONINTERACTIVE |traite la commande tel quelle |
