#!/bin/bash
echo testing valid..
cat valid/* | valgrind --tool=memcheck --leak-check=full ./42sh >& valgrind.output && ./42sh < others/clean.sh
echo testing invalid..
cat invalid/* | valgrind --tool=memcheck --leak-check=full ./42sh >> valgrind.output 2>&1
cat valgrind.output | grep 'definitely lost'
mkdir -p lol/lel; cd lol/lel; rm -rf ../../lol
cd ..
cd -
cd lel
cd ..

