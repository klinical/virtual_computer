#! /bin/bash
# TODO utilize CMDLINE arguments for I/O files
program=virtual_computer

clear

echo "Executing make clean..."
make clean

sleep 0.5

echo "Executing make..."
make

if [ $? -eq 0 ]
then
	echo "Make build succeeded."
	./$program prog1

  sleep 0.5

  make clean
else
	echo "Make failed. start.sh will now stop."
fi
