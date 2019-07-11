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

|  keys  |          description        |
|:------:|:---------------------------:|
| K_SUP  | monte dans l'historique     |
| K_SDOW | descant dans l'historique   |
| K_SRGT | avance d'un mot             |
| K_SLFT | recule d'un mot             |
| K_DEL  | supprime une lettre         |
| K_UP   | monte dans l'historique     |
| K_LEFT | va a gauche                 |
| K_RGHT | va a droite                 |
| K_DOWN | descant dans l'historique   | 
| K_END  | va a la fin                 |
| K_HOME | va au debut                 |
| K_TAB  | autocompletion              |
| K_CTRA | va au debut                 |
| K_CTRC | annule la commande en cours |
| K_CTRD | quitte le shell             |
| K_ENTR | confirme la commande        |
| K_CTRR | recherche de commande       |
| K_CTRP | colle la selection          |
| K_CTRV | va en visual mode           |
| K_CTRX | coupe la selection          |
| K_CTRY | copie la selection          |
| K_BSPC | supprime un caractere       |

# PARSER/LEXER
### Mode
|nb|      mode      |description|
|:-:|-|-|
|2 |    MODEFILE    |quand stdin est fermé|
|1 |   INTERACTIVE  |appele readline quand la commande n'est pas complete |
|0 | NONINTERACTIVE |traite la commande tel quelle |
