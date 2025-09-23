#!/bin/bash
cd ..
source setenv.sh
cd DDSFuzz
export ASAN_OPTIONS=use_sigaltstack=false:abort_on_error=1:symbolize=0:detect_leaks=0
i=1
while true
do
  random_number=$(( ( RANDOM % 1000000 ) + 1 ))
  python3 diff.py $random_number > /dev/null 2>&1
  echo "Iteration $i: Executed diffy.py with random number $random_number"
  i=$((i + 1)) 
done