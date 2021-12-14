#!/bin/bash
a=36
b=6

expr 3 + 5
expr $a + $b
expr $a - 7

c=`expr $a \* $b`
d=`expr $a + 5`

echo "c = $c"
echo "d = $d"
