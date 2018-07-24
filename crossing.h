//
// Created by lauren on 3/19/18.
//

#ifndef TOPOLOGY_CROSSING_H
#define TOPOLOGY_CROSSING_H


#include <vector>

class KNOT;
class SEGMENT;

class CROSS{
public:                                 //member variables
    int id;
    std::vector<KNOT *> itsK;
    std::vector<SEGMENT *> itsS;
    int Lpm;
    //member functions
};



#endif //TOPOLOGY_CROSSING_H
