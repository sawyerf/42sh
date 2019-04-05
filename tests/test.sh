#!/bin/bash
echo testing valid..
cat valid/* | valgrind --tool=memcheck --leak-check=full ./21sh >& valgrind.output && ./21sh < others/clean.sh
echo testing invalid..
cat invalid/* | valgrind --tool=memcheck --leak-check=full ./21sh >> valgrind.output 2>&1
cat valgrind.output | grep 'definitely lost'
