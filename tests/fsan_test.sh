#!/bin/bash
echo testing valid..
cat valid/* | ./21sh >& fsan.output && ./21sh < others/clean.sh
echo testing invalid..
cat invalid/* | ./21sh >> fsan.output 2>&1
