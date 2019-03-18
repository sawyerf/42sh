# 21sh

## TODO

HERE_DOC
- leak in builtin forks
- ${} readline
- fix new line seeking in non interactive here_doc
- fix error propagation in refactored parser
- add missing_quote in readline
------------------------------------
- ls >& 2>file.txt should be valid
- empty cmdname with redir should apply redir
- subtle difference between '$notexistant;' and '"";' needs to be fixed ft_wordexp
- export builtin, set && unset missing stuff.
- sig handling && job control.
- moar testing on redirections.
- cd set_shell_env needs malloc checks.
- replace printf/write(2, etc.. by sprintf or zprintf.
- del la hashtable quand on modifie le PATH
