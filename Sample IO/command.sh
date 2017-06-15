#!/bin/bash
while read line

do

echo $line | ./the1 >> outputs.txt

done < ./'Inputs.txt'
