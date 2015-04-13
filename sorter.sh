#!/bin/bash

for COUNT in {80..1045}
do
  echo $COUNT
  if [ $COUNT -lt 10 ]
  then
      FILE="/afs/tlabs.ac.za/user/p/padsley/data/PR227/run0000"$COUNT".mid.gz"
  elif [ $COUNT -lt 100 ]
  then
      FILE="/afs/tlabs.ac.za/user/p/padsley/data/PR227/run000"$COUNT".mid.gz"
  elif [ $COUNT -lt 1000 ]
  then
      FILE="/afs/tlabs.ac.za/user/p/padsley/data/PR227/run00"$COUNT".mid.gz"
  elif [ $COUNT -lt 10000 ]
  then
      FILE="/afs/tlabs.ac.za/user/p/padsley/data/PR227/run0"$COUNT".mid.gz"
  else
      echo "This might not work"
  fi
  echo $FILE
  if [ $COUNT -lt 10 ]
  then
      FILE2="/afs/tlabs.ac.za/user/p/padsley/data/PR227/sorted0000"$COUNT".root"
  elif [ $COUNT -lt 100 ]
  then
      FILE2="/afs/tlabs.ac.za/user/p/padsley/data/PR227/sorted000"$COUNT".root"
  elif [ $COUNT -lt 1000 ]
  then
      FILE2="/afs/tlabs.ac.za/user/p/padsley/data/PR227/sorted00"$COUNT".root"
  elif [ $COUNT -lt 10000 ]
  then
      FILE2="/afs/tlabs.ac.za/user/p/padsley/data/PR227/sorted0"$COUNT".root"
  else
      echo "This might not work"
  fi
  echo $FILE2
  if [ -e $FILE ]
  then
      if [ ! -e $FILE2 ]
      then
      echo $FILE
#       ./analyzer -i /afs/tlabs.ac.za/user/p/padsley/data/PR227/run000"$COUNT".mid.gz
      ./analyzer -i $FILE
#       mv output.root /afs/tlabs.ac.za/user/p/padsley/data/PR227/sorted000$COUNT.root
      mv output.root $FILE2
      fi
  fi
done


