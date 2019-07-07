alias hello='echo "hello, world"'
hello | cat -e
alias hello
alias hello=
hello
alias hello
alias sub='(echo abc|'
sub cat -e)
alias rd='ls DOESTNOEXIST 2>>err'
rd; rd; rd
cat err
alias aa='echo hello' bb='echo world'
aa; bb
alias mk='mkdir -v' abc='def'
mk abc
alias mk='mkdir -v ' abc='def'
mk abc
alias
alias a=alias
a aa='echo "alias builtin redefined"'
aa
alias b=c
alias c=d
alias d='echo It should works'
b
alias e='g'
alias f='e'
alias g='echo "infinite loop"; e'
g
alias hello='echo "hello, world!"'
unalias hello
hello
alias hello='echo "hello, world!"'
unalias -a
alias
