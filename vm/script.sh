#!/bin/bash
./../max_corewar $2 $3 -d $1 > diff1 | ./off_vm $2 $3 -d $1 > diff2 | diff diff1 diff2
