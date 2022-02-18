#!/bin/bash

cfg_path=`find ~ -name "cfg_location.sh"`
source $cfg_path

# read coverage bar from config
while IFS= read -r line
do
  if [[ "$line" == *"assignment: "* ]]; then
    url=`echo $line | sed 's/assignment: \(.*\)/\1/'`
  fi
done < "$cfg"
filename=md.coverage
wget $url -O $filename 

while IFS= read -r line
do
  if [[ "$line" == *"- Line coverage bar: "* ]]; then
    line_coverage_bar=`echo $line | sed 's/- Line coverage bar: \(.*\)/\1/'`
  fi
  if [[ "$line" == *"- Function coverage bar: "* ]]; then
    function_coverage_bar=`echo $line | sed 's/- Function coverage bar: \(.*\)/\1/'`
  fi
done < "$filename"

if [ -z "$line_coverage_bar" ]
then
  echo "Failed to extra coverage bar. Please contact instructor."
  exit 1
fi
if [ -z "$function_coverage_bar" ]
then
  echo "Failed to extra coverage bar. Please contact instructor."
  exit 1
fi


# verify coverage against bars
validator_path=`find ~ -name "validate_coverage.py"`
coverage_out=/tmp/342_coverage_check.out
if [ "$#" -ne 1 ]; then
    echo "No log specified. Using /tmp/342_coverage_check.out"
else
    coverage_out=$1
    echo "Using /tmp/342_coverage_check.out as specified"
fi

coverage_log=`cat $coverage_out`
summary=`grep -A 2 "Overall coverage rate:" <<< ${coverage_log}`

$validator_path "$summary" $line_coverage_bar $function_coverage_bar
ret=$?
if [ $ret -ne 0 ]; then
     exit 1 
fi

