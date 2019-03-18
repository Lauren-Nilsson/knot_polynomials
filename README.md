INPUT FILE NAME: user_input.in

INPUT DESCRIPTION: 
You will need to enter the number of crossings (n) the knot has, followed by the PD notation (with numbers separted by at least one space). Only spaces or tabs may be used as the delimiter. The last crossing entered MUST be the crossing between the first and last segment (0 and n). Only analysis for real knots is supported at this time (no virtual knots or arcs). 

An example of what your input file should look like is below (in-between the "/" marks). Notice that this knot has 6 crossings and 12 segments that have been labelled 0-11. 

OUTPUT FILE NAMES: comment_stream.out, data.out
OUTPUT DESCRIPTION: data.out contains the necessary information to compute Jones polynomials. The summation of the terms in this file is the Jones polynomial. The data can be exported to Mathematica for this purpose.
comment_stream.out is a verbose file containing additional information about the knot. The initial configuration is repeated back to the user (in order to confirm that the user_input.in file was inputted correctly) along with analysis information. Loop structures for every smoothing are explicitely listed.

RUNNING THE PROGRAM:
1) Make sure all the necessary files are stored in the same location. The following files are necessary to run this program:
crossing.h
knot.h
loop.h
main.cpp
Makefile
pair.h
segment.h
user_input.in

2) In order to generate the executable (simulate_topology), you must first make the file. Makefile is a script that will do this for you--you need only to type "make" into the terminal. This will make a main.o object file and display the following output:
g++	-c -o main.o main.cpp
g++ -g -Wall -o simulate_topology main.o   -lgsl -lgslcblas

3) You may clean up the directory (remove all .o files) with the "make clean" command.

4) Run the executable. In linux, you need only type "./simulate_topology" into the terminal. The program will display a message upon completion. 

** After changing any of the c++ files you must regenerate the executable. This is not necessary if all you have changed is the user_input.in file.

** The most common runtime error is a Segmentation Fault error. This is likely caused by invalid input (an arc or virtual knot). You can check if this is the case by looking into the comment_stream.out file and making sure the printed information is correct.

** The program has not been set up to take input for intertwined but unconnected knots. For example, the following knot would not work--
1 1* 0 0* | 1* 1 0* 0

PROGAMMER'S OTHER NOTES:
This program was written as a topology final project. There is much room for it to grow. I have purposely left it open so that other students (either graduate / undergraduate researchers) may make modifications. Below are some edits I think would be useful, organized from simplest to most difficult to implement.
1) Add a function to determine which knot is between the first and last segments and put a flag on it. This would not restrict the user to identifying this crossing in advance.
2) Allow multiple, intertwined, unconnected loops. (This has not been tested, but may work with current implementation)
3) Add virtual knot analysis (check to see if the PD notation is valid, output Error message instead of allowing compiler to crash)
4) Add arc analysis. Determine how to generate Jones Polynomial for this case
5) Link this program to Mathematica with a script / mexing function to automatically generate the Jones Polynomial summation.


/////////////////////////////////////////////////////
> Number of crossings: 6

0 	8 	1 	7
4	2	5	1
2	9	3	10
8	3	9	4
10	6	11	5
6	0	7	11
////////////////////////////////////////////////////

////////////////////////////////////////////////////
Number of crossings: 9

0	13	1	14
12	7	13	8
11	9	12	8
10	6	11	5
4	15	5	16
16	3	17	4
14	1	15	2
6	9	7	10
17	3	0	2
////////////////////////////////////////////////////

Number of crossings: 19

33	36	34	37
29	35	30	34
35	29	36	28
27	14	28	15
4	16	5	15
5	16	6	17
26	18	27	17
18	13	19	14
25	13	26	12
19	25	20	24
23	30	24	31
2	31	3	32
1	23	2	22
32	21	33	22
3	20	4	21
8	11	9	12
7	11	8	10
9	7	10	6
37	1	0	0


	

