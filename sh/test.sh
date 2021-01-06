#!/bin/bash
echo `awk -v x=2.45 -v y=3.123 'BEGIN{printf "%.2f\n",x*y}'`
s=1.5

echo $$

echo $s
echo `awk -v x=2.45 -v y="$s" 'BEGIN{printf "%.2f\n",x*y}'`
