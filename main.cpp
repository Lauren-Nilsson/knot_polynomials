#include <iostream>
#include <vector>

#include "segment.h"
#include "crossing.h"
#include "knot.h"
#include "loop.h"
#include "pair.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"  //used for progress bar
#define PBWIDTH 60

using namespace std;

void ProgressBar(double fraction_completed)
{
    int val = (int) (fraction_completed * 100);
    int lpad = (int) (fraction_completed * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf ("\r%3d%% |%.*s%*s|", val, lpad, PBSTR, rpad, "");
    fflush (stdout);
}

int main() {
	
															//Opening the inputfile
	ifstream data_in;
	data_in.open("user_input.in");
	if (!data_in) {											//check to make sure file is there and can be opened
		cerr << "Error! File could not be opened. Check directory and/or filename. Input file should be named 'user_input.in' see EXAMPLES.out for help.";
		exit(1);
	}	
	string dummy;											//dummy vector
	int count, thing;										//used to hold the number of crossings
	data_in >> dummy >> dummy >> dummy >> count;			//read in input data
	
															//setup output files
	ofstream verbose("comment_stream.out", ios::out);
	ofstream data("data.out", ios::out);
	
		
	
	verbose << "The knot has " << count << " crossings." << endl;
	vector<vector<int> > userinput(count, vector<int>(4));	//printing info to comment stream
	userinput.reserve(count);
	verbose << "You have entered the following PD notation:" << endl;
	for (int i = 0; i < count; i++){
		for (int j = 0; j < 4; j++) {
			data_in >> userinput[i][j];
			verbose << userinput[i][j] << "  ";
		}
		verbose << endl;
	}

	int numsegs = userinput.size() * 2;
	
	//    int k = 0;
	
	vector<SEGMENT> mysegment;                          //creating objects to hold knot information
	vector<CROSS> mycross;
	vector<KNOT> myknot;
	vector<LOOP> myloop;
	vector<PAIR> mypair;
	
	for (int i = 0; i < numsegs; i++) {
		mysegment.push_back(SEGMENT());                 //setting up segments from user input
		mysegment[i].id = i;
		mysegment[i].looped = false;
		//mysegment[i].aftcross=0;
	}
	
	for (int i = 0; i < userinput.size(); i++) {
		mycross.push_back(CROSS());                     //setting up segments and crossings from user input
		mycross[i].id = i;
		for (int j = 0; j < userinput[i].size(); j++) {
			mysegment[userinput[i][j]].itsC.push_back(&mycross[i]);
			mycross[i].itsS.push_back(&mysegment[userinput[i][j]]);
		}
	}
	
	verbose << endl << endl << endl;
	if (mysegment.size() * 0.5 != mycross.size()) {                 //check to see if PD notation is for a knot or an arc
		cout << "You have entered a PD notation for an arc." << endl;
		cout << "Analysis is not currently supported for arcs. Sorry :(" << endl;
		//goto arcanalysis;
	} else verbose << "You have entered the PD notation for a closed knot." << endl;
	
	
	int numLp = 0;						//number of L+ crossings
	int numLm = 0;						//number of L- crossings
	for (int i = 0; i < mycross.size(); i++) {
		if (mycross[i].itsS[1]->id > mycross[i].itsS[3]->id) {		//if statement computes if crossing is L+ or L-
			if (mycross[i].itsS[1]->id == (mysegment.size() - 1) && mycross[i].itsS[3]->id == 0) {
				mycross[i].Lpm = 1;
				numLm += 1;
			} else {
				mycross[i].Lpm = 0;
				numLp += 1;
			}
		}
		if (mycross[i].itsS[1]->id < mycross[i].itsS[3]->id) {		//if statment computes if the crossing is L+ or L-
			if (mycross[i].itsS[3]->id == (mysegment.size() - 1) && mycross[i].itsS[1]->id == 0) {
				mycross[i].Lpm = 0;
				numLp += 1;
			} else {
				mycross[i].Lpm = 1;
				numLm += 1;
			}
		}
	}
	
	int W = numLp - numLm; 											//This is the writhe of the knot
																	//info for data file
	data << "This file contains all of the alexander polynomials for each smoothing. To get the Jones polynomial take the sum of these and multiply by -(A^3)^" << W << "(-A^2-A^-2)^-1" << endl << endl;										
	
	
	verbose << endl << endl << "There are " << numLp << " L+ crossings and " << numLm << " L- crossings." << endl;
	for (int i = 0; i < mycross.size(); i++) {
		verbose << "Crossing " << i << " has ";						//printing info to comment stream
		if (mycross[i].Lpm == 0) {
			verbose << "L+";
		} else verbose << "L-";
		verbose << " orientation." << endl;
	}
	verbose << endl << endl << "The knot has a writhe of " << W << endl << endl;
	
	
	vector<SEGMENT *> old ;											//placeholder vector
	for (int i = 0; i < 4; i++)
	{																//setup placeholder
		old.push_back(&mysegment[i]);
	}
	
	for (int i = 0; i < mycross.size(); i++)
	{
		if (mycross[i].itsS[1]->id > mycross[i].itsS[3]->id && i != mycross.size()-1 )
		{
			old[3] = mycross[i].itsS[3];	//rearranges the crossing to be L- from L+
			old[0] = mycross[i].itsS[0];	//All crossings set to L- configuration to make smoothing easier
			old[1] = mycross[i].itsS[1];
			old[2] = mycross[i].itsS[2];
			
			mycross[i].itsS[0] = old[3];
			mycross[i].itsS[1] = old[0];
			mycross[i].itsS[2] = old[1];
			mycross[i].itsS[3] = old[2];
		} else if (mycross[i].itsS[1]->id < mycross[i].itsS[3]->id && i == mycross.size()-1) {
			old[3] = mycross[i].itsS[3];	//rearranges the crossing to be L- from L+
			old[0] = mycross[i].itsS[0];	//special case for last crossing
			old[1] = mycross[i].itsS[1];
			old[2] = mycross[i].itsS[2];
			
			mycross[i].itsS[0] = old[3];
			mycross[i].itsS[1] = old[0];
			mycross[i].itsS[2] = old[1];
			mycross[i].itsS[3] = old[2];
		}
	}
	
	verbose << "Smoothing A )( is represented by 0. Smoothing A^-1 is represented by 1." << endl << endl << endl;
	
	
	int max_count = pow(2,(mycross.size()));				//number of possible smoothings
	vector<int> smoothings(mycross.size());					//vector to store smoothing info
	
	
	for(int count = 0; count < max_count; count++)
	{
		double fraction_completed = ( ((double)count + 1.0) / ((double)max_count) );   //progress bar
        ProgressBar(fraction_completed);
		
															// Using a binary counter to go through all iterations of smoothings
		verbose << "Smoothing: " ;
		
		for(int offset = mycross.size()-1; offset >= 0; offset--) 
		{
			smoothings[offset] = ((count & (1 << offset)) >> offset);	//binary counter--saved to variable
			verbose << ((count & (1 << offset)) >> offset);				//binary counter--saved to comment string
			if (mycross[offset].Lpm == ((count & (1 << offset)) >> offset) ){		//smoothing info saved to Lpm variable. 0 for A and 1 for A^-1
				mycross[offset].Lpm = ((count & (1 << offset)) >> offset);			//Lpm switched here according to the binary counter
			} else if (mycross[offset].Lpm != ((count & (1 << offset)) >> offset) && mycross[offset].Lpm == 0) {
				mycross[offset].Lpm = 1;
			} else if (mycross[offset].Lpm != ((count & (1 << offset)) >> offset) && mycross[offset].Lpm == 1) {
				mycross[offset].Lpm = 0;
			}
			
		} //end offset for loop
		
																		//blanking out loops and structures for a new run
		for (int i = 0; i < numsegs; i++) {
			mysegment[i].looped = false;
		}
		int numlps = 0;
		myloop.erase(myloop.begin(),myloop.end());
		mypair.erase(mypair.begin(),mypair.end());
		
		verbose << endl;
		int number_of_loops = 0;
		
		
		int numpairs = 0;
		for (int i = 0; i < mycross.size(); i++) 						//Use smoothings to "pair up"" segments
		{
			if (mycross[i].Lpm == 0)
			{														//for A smoothing, pair them this way...
				mypair.push_back(PAIR());
				mypair[numpairs].id = numpairs;
				mypair[numpairs].itsS.push_back(&mysegment[mycross[i].itsS[0]->id]);
				mypair[numpairs].itsS.push_back(&mysegment[mycross[i].itsS[1]->id]);
				numpairs += 1;
				mypair.push_back(PAIR());
				mypair[numpairs].id = numpairs;
				mypair[numpairs].itsS.push_back(&mysegment[mycross[i].itsS[2]->id]);
				mypair[numpairs].itsS.push_back(&mysegment[mycross[i].itsS[3]->id]);
				numpairs += 1;
				
			} else if (mycross[i].Lpm == 1) {
				mypair.push_back(PAIR());							//for A^-1 smoothing pair them this way...
				mypair[numpairs].id = numpairs;
				mypair[numpairs].itsS.push_back(&mysegment[mycross[i].itsS[0]->id]);
				mypair[numpairs].itsS.push_back(&mysegment[mycross[i].itsS[3]->id]);
				numpairs += 1;
				mypair.push_back(PAIR());
				mypair[numpairs].id = numpairs;
				mypair[numpairs].itsS.push_back(&mysegment[mycross[i].itsS[2]->id]);
				mypair[numpairs].itsS.push_back(&mysegment[mycross[i].itsS[1]->id]);
				numpairs += 1;
			}
		}
		
		int number_of_segments_looped = 0;
		bool need_new_loop = true;
		
		while (number_of_segments_looped < mysegment.size() )		//while there are still segments that have not been paired...
		{
			if (need_new_loop == true) 								//if nothing can be added onto existing loops, make a new loop.
			{
				myloop.push_back(LOOP());
																	//find first pair that has not been looped.
				for (int i = 0; i < mypair.size(); i++)
				{
					if (mypair[i].itsS[0]->looped==false && mypair[i].itsS[1]->looped==false)
					{
						myloop[number_of_loops].itsS.push_back(mypair[i].itsS[0]);
						myloop[number_of_loops].itsS.push_back(mypair[i].itsS[1]);
						mypair[i].itsS[0]->looped = true;			//add the pair into a loop
						mypair[i].itsS[1]->looped = true;
						need_new_loop = false; 
						number_of_loops += 1;
						number_of_segments_looped += 2;
						goto checkpoint;							//exit if/for loop and check to add next pair to loops.
					}
				}
				
			}
			for (int i = 0; i < mypair.size(); i++)
			{
				
																	//check all of the pairs to see if any of them can be added.
				if (mypair[i].itsS[0]->looped != mypair[i].itsS[1]->looped ) 
				{ 													//if the pair is ready to add (one segment has been looped, the other has not)...
					
					for (int j = 0; j < myloop.size(); j++)
					{ 												//...Check all the loops to see which one the pair should be added to
						if (myloop[j].itsS.back()->id == mypair[i].itsS[0]->id) 
						{
							myloop[j].itsS.push_back(mypair[i].itsS[1]);
							number_of_segments_looped += 1;			//add the segment to the loop.
							mypair[i].itsS[1]->looped = true;
							goto checkpoint;						//exit if/for loop and check the other pairs
						} else if (myloop[j].itsS.back()->id == mypair[i].itsS[1]->id) {
							myloop[j].itsS.push_back(mypair[i].itsS[0]);
							number_of_segments_looped += 1;			//add the segment to the loop.
							mypair[i].itsS[0]->looped = true;
							goto checkpoint;						//exit if/for loop and check the other pairs
						} 
					}
				}
				
			}
			
			need_new_loop = true; 									//if none of the pairs were added, then a new loop is created.
			
			checkpoint: ; 											//if the pair was added, start over and check all the other pairs.
		}
		
		int smooth_factor = 0;										//computing polynomial
		
		for (int i = 0; i < mycross.size(); i++)
		{															//finding smoothing factor from the smoothing data for polynomial
			if (smoothings[i] == 0) smooth_factor += 1;
			if (smoothings[i] == 1) smooth_factor -= 1;
		}
		data << "A^(" << smooth_factor << ")*(-A^2-A^(-2))^" << myloop.size() << endl;		//This line prints Jones polynomial information to data.out
		
		
		verbose << "This smoothing has " << myloop.size() << " loops." << endl;
		for (int i = 0; i < myloop.size(); i++) {
			verbose << "Loop " << i << " has segments: ";			//print some info to comment stream
			for (int j = 0; j < myloop[i].itsS.size(); j++) {
				verbose << myloop[i].itsS[j]->id << "  ";
			}
			verbose << endl;
		}
		
		verbose << endl;
		
	} //end count for loop
	
	
	
	

	
	
	arcanalysis: ;												//here is where you can add analysis for arcs
	
	cout << endl << "Program has completed." << endl;
}
