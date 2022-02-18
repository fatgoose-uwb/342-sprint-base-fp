#!/bin/bash

source ./.github/workflows/cfg_location.sh

while IFS= read -r line
do
  if [[ "$line" == *"upstream: "* ]]; then
    upstream=`echo $line | sed 's/upstream: \(.*\)/\1/'`
  fi
done < "$cfg"

if [ -z "$upstream" ]
then
  echo "Failed to extra upstream url. Please contact instructor."
  exit 1
fi

# get file count in submission repo
file_count_in_submission=`find . -type f ! -path '*/.git/*' | wc -l`

# get file count in upstream repo
pushd /tmp
git clone $upstream upstream_repo
cd upstream_repo
file_count_in_upstream=`find . -type f ! -path '*/.git/*' | wc -l`
popd

if [[ $file_count_in_submission == $file_count_in_upstream ]]; then
    echo "No new files added. Bravo!"
else
    echo "New file(s) added to the repo. Not allowed. Please remove them."
    exit 1
fi
