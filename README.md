# 21sh

## TODO

- leak in builtin forks
- ${} readline
- ls >& 2>file.txt should be valid
- empty cmdname with redir should apply redir
- subtle difference between '$notexistant;' and '"";' needs to be fixed ft_wordexp
- export builtin, set && unset missing stuff.
- del la hashtable quand on modifie le PATH
- readline return values from char* to int
- move full path bin checking out of fork

------------------------------------
### 42sh

- sig handling && job control.
- moar testing on redirections.
- cd set_shell_env needs malloc checks.
- replace printf/write(2, etc.. by sprintf or zprintf.
