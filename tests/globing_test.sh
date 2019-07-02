mkdir empty && cd empty
touch a? b* [c]; ls -1
echo a > aa && echo b > ab && cat -e a?
rm -f *
mkdir -p one/two
echo 'four' > one/two/three
echo 'six' > one/five
cat ./*/*/* ./*/*
ls /??r
rm -rf ./*
mkdir '[x' && touch '[x/foo'
echo [*; echo *[x; echo [x/*
rm -rf *
touch 'a[a-z][x' 'ab[x'
echo a[a-z][*; echo a[a-z]*; echo a[a\-z]*
rm -f *
touch ".bc" "abc" "bbc" "cbc" "-bc" '!bc' "+bc" ",bc" "0bc" "1bc"
echo [ab-]*
echo [-ab]*
echo [!-ab]*
echo [!ab]*
echo []ab]*
echo [+--]*
echo [--1]*
echo [z-a]*
echo [a-a]bc
rm -f * .*; ls -A
touch aa bb cc 11 22 33
echo **
echo [!a-z]
echo [4-z][A-b]
