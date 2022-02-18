#!/bin/bash

cov_path=`find ~ -name "coverage_check"|grep -v workflows`

pushd $cov_path

echo
echo "visit coverage page at http://[public ip]"
echo

sudo python3 -m http.server 80 # yes it's that simple

trap "popd" INT # may not be necessary
