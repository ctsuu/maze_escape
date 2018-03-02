# maze_escape
Hackerrank

https://www.hackerrank.com/challenges/maze-escape
To make this problem more interest, I want to try use A search to solve the maze. 

###Input strings
```
2
7,7
#######
#--#--#
#--#--#
#--#--#
------#
#-----#
#######
4,0
```
First line is player no.
Second line is maze grid size: 7 cols and 7 rows.
Then, actual grid.
Then, Exit location (5th row, 0 col).

###Basic Build Instructions

    Clone this repo.
    Make a build directory: mkdir build && cd build
    Compile: cmake .. && make
    Run it: ./Escape path/to/input.txt path/to/output.txt. You can find some sample inputs in 'data/'.
        eg. ./Escape ../data/input00.txt output.txt

The robot will find it's way to the exit. 
```
player id:2
maze size:7,7
start position:1,6
exit  position:4,0
#######
#--#--#
#--#--#
#--#--#
------#
#-----#
#######
open cell:(0,1,6)
open cell:(1,1,5)
open cell:(2,1,4)
open cell:(2,2,5)
open cell:(3,2,4)
open cell:(3,3,5)
open cell:(4,3,4)
open cell:(4,4,5)
open cell:(5,4,4)
open cell:(5,5,5)
open cell:(6,4,3)
open cell:(6,5,4)
open cell:(7,4,2)
open cell:(7,5,3)
open cell:(8,3,2)
open cell:(8,4,1)
open cell:(8,5,2)
open cell:(9,2,2)
open cell:(9,3,1)
open cell:(9,4,0)
search success
```
