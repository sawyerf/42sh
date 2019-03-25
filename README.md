# 21sh

## TODO

- leak in builtin forks
- ${} readline
- ls >& 2>file.txt should be valid
- empty cmdname with redir should apply redir
- subtle difference between '$notexistant;' and '"";' needs to be fixed ft_wordexp
- export builtin, set && unset missing stuff.
- del la hashtable quand on modifie le PATH
- readline return values from char\* to int
- move full path bin checking out of fork

------------------------------------
### 42sh

- sig handling && job control.
- moar testing on redirections.
- cd set_shell_env needs malloc checks.
- replace printf/write(2, etc.. by sprintf or zprintf.

## READLINE
### Return
| info | status | str |
|:----:|:------:|:---:|
|malloc| MEMERR |  ?  |
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
