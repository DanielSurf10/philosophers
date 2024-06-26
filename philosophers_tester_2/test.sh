#!/bin/bash

## PATH VARS
BIN_PATH=philo/philo
MAKEFILE_PATH="philo"
## UNCOMMENT BONUS TESTS IF NEEDED
# BONUS_BIN_PATH=philo_bonus/philo_bonus
# BONUS_MAKEFILE_PATH=philo_bonus

## TEST PARAMETERS - CHANGE AS NEEDED
NB_OF_TESTS=25
RESULTS_FOLDER='test_results'

## TEST FUNCTION DEFINITION
run_test_case() {
	CASE_NO=$1
	CASE=$2
	CASE_FILE="$(echo $2 | tr ' ' _)"
	EXPECTED_OUTCOME=$3
	FONT_COLOUR_BG=''
	FONT_COLOUR=''

	i=1
	time=0.1

	if [[ $EXPECTED_OUTCOME == "should-die" ]]
	then
		COLOUR_BG="\e[1;31mTest:"
		FONT_COLOUR_BG="\e[41;30m"
	else
		COLOUR_BG="\e[1;32mTest:"
		FONT_COLOUR_BG="\e[42;30m"
	fi

	mkdir -p "$RESULTS_FOLDER/$CASE_NO"
	echo -e "$FONT_COLOUR_BG $CASE_NO: $CASE $EXPECTED_OUTCOME \e[0m"
	while [ $i -le $NB_OF_TESTS ]
	do
		echo -e "$COLOUR_BG $i\e[0m"
		echo "$CASE" > "$RESULTS_FOLDER/$CASE_NO/test$i-$EXPECTED_OUTCOME-$CASE_FILE"
		# valgrind -q --tool=helgrind $BIN_PATH $CASE >> "$RESULTS_FOLDER/$CASE_NO/test$i-$EXPECTED_OUTCOME-$CASE_FILE"
		$BIN_PATH $CASE >> "$RESULTS_FOLDER/$CASE_NO/test$i-$EXPECTED_OUTCOME-$CASE_FILE" &
		# echo "$CASE_NO - test$i" >> tests_log
		# cat "$RESULTS_FOLDER/$CASE_NO/test$i-$EXPECTED_OUTCOME-$CASE_FILE" | grep 'die'
		sleep $time
		i=$(( $i + 1 ))
	done
	sleep 3

	if [[ $EXPECTED_OUTCOME == "should-die" ]]
	then
		echo -n '[N° tests] [N° dies]: '
		cat $(find test_results -name "test*-$EXPECTED_OUTCOME-$CASE_FILE")'' | grep died | wc -l | tr '\n' ' ' && find test_results -name "test*-$EXPECTED_OUTCOME-$CASE_FILE" | wc -l
	else
		echo -n 'test number: '
		find test_results -name "test*-$EXPECTED_OUTCOME-$CASE_FILE" | wc -l
		echo -n 'died: '
		cat $(find test_results -name "test*-$EXPECTED_OUTCOME-$CASE_FILE")'' | grep died | wc -l
	fi

	echo
}

## RUN SCRIPT
make -C $MAKEFILE_PATH && clear
mkdir -p $RESULTS_FOLDER
rm -rf $RESULTS_FOLDER/*
# run_test_case "case_01" "1 400 100 100 7" "should-die"
# run_test_case "case_02" "1 800 200 200 7" "should-die"
# run_test_case "case_03" "2 100 200 200" "should-die"
# run_test_case "case_04" "2 150 200 100" "should-die"
# run_test_case "case_05" "2 150 360 100" "should-die"
# run_test_case "case_06" "3 200 100 100 7" "should-die"
# run_test_case "case_07" "4 310 200 100 7" "should-die"
# run_test_case "case_08" "4 399 200 200 7" "should-die"
# run_test_case "case_09" "5 200 100 100 7" "should-die"
# sleep 5
echo -n '[N° tests] [N° dies]: '
cat $(find test_results -name "*should*") | grep died | wc -l | tr '\n' ' ' && find test_results -name "*should*" | wc -l

run_test_case "case_10" "3 400 100 100 7" "not-die"
run_test_case "case_11" "4 210 100 100 7" "not-die"
run_test_case "case_12" "4 410 200 200 7" "not-die"
run_test_case "case_13" "5 400 100 100 7" "not-die"
run_test_case "case_14" "5 800 200 200 7" "not-die"
# sleep 5
echo -n 'test number: '
find test_results -name "*not*" | wc -l
echo -n 'died: '
cat $(find test_results -name "*not*")'' | grep died | wc -l

make -C $MAKEFILE_PATH fclean

# # UNCOMMENT BONUS TESTS IF NEEDED
# make -C $MAKEFILE_PATH && clear
# mkdir -p "bonus_$RESULTS_FOLDER"
# run_test_case "bonus_case_01" "1 400 100 100 7" "should-die"
# run_test_case "bonus_case_02" "1 800 200 200 7" "should-die"
# run_test_case "bonus_case_03" "2 100 200 200" "should-die"
# run_test_case "bonus_case_04" "2 150 200 100" "should-die"
# run_test_case "bonus_case_05" "2 150 360 100" "should-die"
# run_test_case "bonus_case_06" "3 200 100 100 7" "should-die"
# run_test_case "bonus_case_07" "4 310 200 100 7" "should-die"
# run_test_case "bonus_case_08" "4 399 200 200 7" "should-die"
# run_test_case "bonus_case_09" "5 200 100 100 7" "should-die"

# run_test_case "bonus_case_10" "3 400 100 100 7" "not-die"
# run_test_case "bonus_case_11" "4 210 100 100 7" "not-die"
# run_test_case "bonus_case_12" "4 410 200 200 7" "not-die"
# run_test_case "bonus_case_13" "5 400 100 100 7" "not-die"
# run_test_case "bonus_case_14" "5 800 200 200 7" "not-die"
# make -C $MAKEFILE_PATH fclean
