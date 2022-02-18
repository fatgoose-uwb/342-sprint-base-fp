#!/bin/bash

event="/home/runner/work/_temp/_github_workflow/event.json"

if ! [ -f "$event" ]; then
  echo "$event does not exists. Please contact instructor."
  exit 1
fi

baseRepoOwner=`cat $event|jq '.pull_request.base.label'| sed 's/"\(.*\):\(.*\)"/\1/'`
baseRepoBranch=`cat $event|jq '.pull_request.base.label'| sed 's/"\(.*\):\(.*\)"/\2/'`
headRepoOwner=`cat $event|jq '.pull_request.head.label'| sed 's/"\(.*\):\(.*\)"/\1/'`
headRepoBranch=`cat $event|jq '.pull_request.head.label'| sed 's/"\(.*\):\(.*\)"/\2/'`
PRSender=`cat $event|jq '.sender.login'| sed 's/"\(.*\)"/\1/'`
prO=`cat $event|jq '.pull_request.head.label'| sed 's/"\(.*\):\(.*\)/\1/'`

if [[ -z "$baseRepoOwner" || -z $headRepoOwner || -z $PRSender || -z $headRepoBranch ]]
then
  echo "Failed to extra PR info. Please contact instructor."
  exit 1
fi

if [[ $baseRepoOwner == $headRepoOwner && $baseRepoOwner == $PRSender && $baseRepoBranch == "main" && $headRepoBranch != "main" ]]; then
  echo "PR is targeting the right repo and branch. Awesome!"
else
  echo "PR is against the wrong target branch (it should be from your \"work\" branch towards YOUR OWN main branch). Failed."
  echo "base repo owner: $baseRepoOwner"
  echo "head repo owner: $headRepoOwner"
  echo "base repo branch: $baseRepoBranch"
  echo "head repo branch: $headRepoBranch"
  echo "pr sender: $PRSender"
  echo "A very popular reasons for this error is that your PR is create from your \"work\" branch to the instructor's branch."
  echo "Please close and discard this PR, and try again. PR from Your work branch to your main branch."
  exit 1
fi
