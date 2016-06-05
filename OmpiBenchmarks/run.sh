#!/bin/bash

iterations=50
dim=3
points=$2

ppn=$1
bindto=core
nodes=48

$BUILD/bin/mpirun --report-bindings --hostfile nodes.txt -np $(($ppn*$nodes)) --map-by ppr:$ppn:node:SPAN --bind-to $bindto ./a.out $points $dim $iterations


