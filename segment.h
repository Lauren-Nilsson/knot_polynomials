//
// Created by lauren on 3/19/18.
//

#ifndef TOPOLOGY_SEGMENT_H
#define TOPOLOGY_SEGMENT_H


#include <vector>

class KNOT;
class CROSS;

class SEGMENT{
public:                                 //member variables
    int id;
    bool looped;
    int aftcross;
    std::vector<KNOT *> itsK;
    std::vector<CROSS *> itsC;
    //member functions
};



#endif //TOPOLOGY_SEGMENT_H
