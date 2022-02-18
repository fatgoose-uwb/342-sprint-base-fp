#!/bin/bash

morning_dance() {
  echo
  echo '♪┏(・o･)┛♪┗ ( ･o･) ┓♪'
  echo
  echo '  ᕕ(⌐■_■)ᕗ ♪♬'
  echo
  echo '    ᕕ(⌐■_■)ᕗ ♪♬'
}

afternoon_dance() {
  echo '   _O/                   '
  echo '     \                  /           \O_'
  echo '     /\_              \_\         /\/'
  echo '     \                   \         /'
  echo '             O/ /       /O\        \'
  echo '             /\|/\                 '
}

evening_dance() {
  echo '    ♪┏(・o･)┛♪┗ ( ･o･) ┓♪'
  echo
  echo '  ᕕ(⌐■_■)ᕗ ♪♬'
  echo
  echo '♪┏(・o･)┛♪┗ ( ･o･) ┓♪'
  echo
}

midnight_dance() {
  sleep_art_path=`find ~ -name "sleep.art"`
  cat $sleep_art_path
}

# https://stackoverflow.com/questions/14346342/greet-a-user-differently-on-the-time-of-day-bash-script
h=`TZ=US/Pacific date +%H`
if [ $h -le 12 ] && [ $h -gt 5 ] ; then
  afternoon_dance
elif [ $h -le 18 ] && [ $h -gt 12 ]; then
  afternoon_dance
elif [ $h -lt 23 ] && [ $h -gt 18 ]; then
  afternoon_dance
else
  midnight_dance
fi
echo
echo Proud of you on finishing this 342! It\'s been a great run!
echo
echo Best luck in your future endeavors!
echo
echo Grader bot peace out...