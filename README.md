# 42sh

*Contributors: ![Kais](https://github.com/kaistlili), ![Alaë](https://github.com/sawyerf), ![Julien](https://github.com/juhallyn), ![Theo](https://github.com/theduv)*

## Description
42sh, is the compilation of projects minishell, 21sh and 42sh. It consists of reproducing the behaviour of bash in C during 5 months with 4 team members. This project gave us the opportunity to learn all the moving parts of a shell (lexer, parser, execution, job control, readline, variables, etc) and perfect our knowledge in the bash scripting language. Along with the main part we made some ![features and bonus](#Features-and-Bonus).


## Features and Bonus
- History
  - fc builtins
  - ! expansions
  - History File
  - Ctrl+R
- Autocompletions
  - Contextual and dynamic
- Inhibiteurs
  - `"`, `'`, `\`
- Tilde and additional parameter
  - ${var:para}
- Globing
  - `*`, `!`, `[]`, `?`
- Alias
- Customization of the prompt

## Builtins
- set/unset
- export
- exit
- fc 
- type
- alias
- fg/bg

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
| <kbd>^</kbd><br>
  <kbd>^</kbd>                         | Browse the history |
| <kbd>Shift</kbd>+<kbd><</kbd><br> 
  <kbd>Shift</kbd>+<kbd>></kbd><br>    | Move one word      |
| <kbd>end</kbd>/
  <kbd>ctrl</kbd>+<kbd>e</kbd>         | line Forward       |
| <kbd>end</kbd>/
  <kbd>ctrl</kbd>+<kbd>a</kbd>         | line backward      |
| <kbd>tab</kbd>                       | autocompletion     |
| <kbd>ctrl</kbd>+<kbd>y</kbd>         | Clear the terminal |
| <kbd>ctrl</kbd>+<kbd>d</kbd>         | exit the shell     |
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
