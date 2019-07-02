ARG="$1"
> vardiff.txt
echo echo "$ARG" > .cmd.sh
diff <(bash .cmd.sh) <(./42sh < .cmd.sh) > /dev/null
if (($?))
then
	echo "[KO] $ARG"
	echo "test: $ARG: " >> vardiff.txt
	echo "Diff: " >> vardiff.txt
	echo "===============================" >> vardiff.txt
	diff <(bash .cmd.sh) <(./42sh < .cmd.sh) >> vardiff.txt
	echo "var BASH: " >> vardiff.txt
	echo "===============================" >> vardiff.txt
	bash .cmd.sh >> vardiff.txt
	echo "var 42sh: " >> vardiff.txt
	echo "===============================" >> vardiff.txt
	./42sh < .cmd.sh >> vardiff.txt
else
	echo "[OK]"
fi
