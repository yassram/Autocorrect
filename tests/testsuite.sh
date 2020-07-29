#! /bin/sh

RED='\033[0;41m'
NC='\033[0m' # No Color
GREEN='\033[0;42m'

echo "Please choose your os: [osx / linux64]"
read choosen_os

if [ $choosen_os = "osx" ]
then
	path_to_ref="ref/osx"
elif [ $choosen_os = "linux64" ]
then
	path_to_ref="ref/linux64"
else
	echo "Unavailable choice!"
	exit 1
fi

echo "[INFO] Compiling words.txt..."
"../TextMiningCompiler" ../words.txt ../dict.bin

echo "[INFO] REF compiling words.txt..."
"../${path_to_ref}/refTextMiningCompiler" ../words.txt ../ref_dict.bin > /dev/null

for test_file in ../tests/test_files/*
do
	cat $test_file
	cat $test_file | "../TextMiningApp" ../dict.bin > .f1
	cat $test_file | "../${path_to_ref}/refTextMiningApp" ../ref_dict.bin > .ref 2> /dev/null
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
