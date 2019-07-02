#mkdir empty ; cd empty
#pwd
#touch a? b* [c]; ls -1
#echo a > aa && echo b > ab && cat -e a?
#rm -f *
#mkdir -p one/two
#echo 'four' > one/two/three
#echo 'six' > one/five
#cat ./*/*/* ./*/*
#ls /??r
#echo rm -rf ./*
#mkdir '[x' && touch '[x/foo'
#echo [*; echo *[x; echo [x/*
#rm -rf *
#touch 'a[a-z][x' 'ab[x'
#~/scriptest.sh a[a-z][*; echo a[a-z]*; echo a[a\-z]*
#rm -f *
#touch ".bc" "abc" "bbc" "cbc" "-bc" '!bc' "+bc" ",bc" "0bc" "1bc"
#~/scriptest.sh '[ab-]*'
#~/scriptest.sh '[-ab]*'
#~/scriptest.sh '[!-ab]*'
#~/scriptest.sh '[!ab]*'
#~/scriptest.sh '[]ab]*'
#~/scriptest.sh '[+--]*'
#~/scriptest.sh '[--1]*'
#~/scriptest.sh '[z-a]*'
#~/scriptest.sh '[a-a]bc'
#rm -f * .*; ls -A
#touch aa bb cc 11 22 33
~/scriptest.sh '**'
~/scriptest.sh '[!a-z]'
~/scriptest.sh '[4-z][A-b]'
~/scriptest.sh '/*/*'
~/scriptest.sh '/.*/'
~/scriptest.sh '/*/*[a]*'
~/scriptest.sh '/[!A-Z]*/*'
~/scriptest.sh '/??*'
~/scriptest.sh '../../../*/*[A-z]*/'
