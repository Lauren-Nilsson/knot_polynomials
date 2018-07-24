//
// Created by lauren on 3/22/18.
//

#ifndef TOPOLOGY_LOOP_H
#define TOPOLOGY_LOOP_H

#include <vector>

class KNOT;
class CROSS;
class SEGMENT;

class LOOP{
public:                                 //member variables
    int id;
    std::vector<KNOT *> itsK;
    std::vector<CROSS *> itsC;
    std::vector<SEGMENT *> itsS;
    //member functions
};





#endif //TOPOLOGY_LOOP_H
