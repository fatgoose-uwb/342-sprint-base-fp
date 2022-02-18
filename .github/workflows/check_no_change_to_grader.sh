#!/bin/bash

git fetch origin main:main

changes=`git diff --name-only main`

if [[ "$changes" == *".github"* ]]; then
  echo "Grader bot scripts changed in the .github folder. Not permitted!"
  echo "Undo the changes made in the .github folder and try again."
  exit 1
fi
echo "the Grader bot is sane. Nop likes!"
