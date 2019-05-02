# 42sh

## TODO
- export builtin, set && unset missing stuff.
- autocomplete after >& is wrong
- ~~IFS in ft_wordexp is broken on IFS != ` \n\t` and quote removal~~
- ~~backslash and single quotes bugged: `var='\'\'\'\''' ; echo $var`~~
- ~~field splitting has to be handled in handle_exp_param/build_param~~
- ~~empty cmdname with redir should apply redir~~
- ~~subtle difference between '$notexistant;' and '"";' needs to be fixed ft_wordexp~~
- ~~del la hashtable quand on modifie le PATH~~
- ~~move full path bin checking out of fork~~
- ~~Parameter expansions has invalid read/write on multiline command with ' or "~~
------------------------------------
### 42sh

- finir la feature historique
- sig handling && job control.
- moar testing on redirections.
- cd set_shell_env needs malloc checks. <= this
- replace printf/write(2, etc.. by sprintf or zprintf.

## Bug
|check|     `command`     |                result               | info complementaire |
|:---:|:-----------------:|:-----------------------------------:|:-------------------:|
|     | `"\t"`            | le token doit contnir \t et non un tab |||
|     | `ls \ <tab>`      | ca ne comprends le ' '              |||
|     | `ls "file <tab>`  | ne considere pas le debut des quote |||
|  ✓  | `ls "<tab>`       | ne referme pas les quotes           |||
|  ✓  | `ls '<tab><ctrl+c/d`| segfault |la fonction est surement readline appele dans light_parser||
|  ✓  | ` `               | 21sh: syntax error near : '' + exit ||
|  ✓  | `env - i ./21sh ` | double free						    ||
|  ✓  | `ls \\n` + Ctrl+c | 21sh: premature EOF + exit          ||
|  ✓  | `ls "\n` + Ctrl+c | 21sh: premature EOF + exit          ||
|  ✓  | `fc -s` apres celle d'avant | boucle infini | UPDATE: added MODE_FC in sh_core.h and in request_new_line--le terminale est en NONINTERACTIVE quand la commande est lancer 2. s'arrete avec Ctrl+d |

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
