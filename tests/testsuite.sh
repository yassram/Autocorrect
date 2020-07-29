#! /bin/sh

RED='\033[0;41m'
NC='\033[0m' # No Color
GREEN='\033[0;42m'

echo "[INFO] Compiling words.txt..."
../TextMiningCompiler ../words.txt ../dict.bin

echo "[INFO] REF compiling words.txt..."
../ref/TextMiningCompiler ../words.txt ../ref_dict.bin > /dev/null

for test_file in ../tests/test_files/*
do
	cat $test_file
	cat $test_file | ../TextMiningApp ../dict.bin > .f1
	cat $test_file | ../ref/TextMiningApp ../ref_dict.bin > .ref 2> /dev/null
	diffval=$(diff -q .f1 .ref)
	if [ "$diffval" = "" ] 
	then
		printf ">> [${GREEN}SUCCESS${NC}]\n"
	else
		printf ">> [${RED}FAILURE${NC}]\n"
	fi
done

rm -f .f1 .ref
rm -f ../ref_dict.bin ../dict.bin
