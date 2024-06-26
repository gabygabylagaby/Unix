#!/bin/bash

echo "Running script args [$f1] [$f2]"

function f1(){
    echo "hi from f1 function "  
}

f1

function f2(){
    echo "param [$f1] [$f2]"
}

f2 2 "Mike"

g_sum = 0
function sumtwo(){
    g_sum = $(($1 + $2))
    #return $1 + $2
}

sumtwo 2 4
result = $((sumtwo 2 3))
echo "result is $result"
echo "g_sum is $g_sum"


gl=5

function f4(){
    gl= 2
    echo "gl is $gl"

}

f4

function f5(){
    echo "function f5"

} -> f5.out

f5

function f6(){
    while read input
    do
        echo "line is $input"
    done
} < script1.sh


f6


