#!/bin/bash
echo testing valid..
cat valid/* | ./42sh >& fsan.output && ./42sh < others/clean.sh
echo testing invalid..
cat invalid/* | ./42sh >> fsan.output 2>&1
