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
#~/globing_script.sh a[a-z][*; echo a[a-z]*; echo a[a\-z]*
#rm -f *
#touch ".bc" "abc" "bbc" "cbc" "-bc" '!bc' "+bc" ",bc" "0bc" "1bc"
#~/globing_script.sh '[ab-]*'
#~/globing_script.sh '[-ab]*'
#~/globing_script.sh '[!-ab]*'
#~/globing_script.sh '[!ab]*'
#~/globing_script.sh '[]ab]*'
#~/globing_script.sh '[+--]*'
#~/globing_script.sh '[--1]*'
#~/globing_script.sh '[z-a]*'
#~/globing_script.sh '[a-a]bc'
#rm -f * .*; ls -A
#touch aa bb cc 11 22 33
~/globing_script.sh '**'
~/globing_script.sh '[!a-z]'
~/globing_script.sh '[4-z][A-b]'
~/globing_script.sh '/*/*'
~/globing_script.sh '/.*/'
~/globing_script.sh '/*/*[a]*'
~/globing_script.sh '/[!A-Z]*/*'
~/globing_script.sh '/??*'
~/globing_script.sh '../../../*/*[A-z]*/'
