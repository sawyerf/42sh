#!/bin/bash
ARG="$1"
> matching.txt
echo "echo $ARG" > cmd.sh
diff <(echo $ARG |  tr ' ' '\n' | sort ) <(/Users/tduval/Documents/42sh/42sh < cmd.sh | tr ' ' "\n" | sort) > /dev/null
if (($?))
then
	printf "\033[0;31m[KO] $ARG\033[0;00m\n"
	echo "test: $ARG: " >> matching.txt
	echo "Diff: " >> matching.txt
	echo "===============================" >> matching.txt
	diff <(echo $ARG |  tr ' ' '\n' | sort ) <(/Users/tduval/Documents/42sh/42sh < cmd.sh | tr ' ' "\n" | sort) >> matching.txt
	echo "matching BASH: " >> matching.txt
	echo "===============================" >> matching.txt
	echo $ARG |  tr ' ' '\n' | sort >> matching.txt
	echo "matching 42sh: " >> matching.txt
	echo "===============================" >> matching.txt
	/Users/tduval/Documents/42sh/42sh < cmd.sh | tr ' ' "\n" | sort >> matching.txt
else
	printf "\033[0;33m[OK]\033[0;00m\n"
fi
