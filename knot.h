//
// Created by lauren on 3/19/18.
//

#ifndef TOPOLOGY_KNOT_H
#define TOPOLOGY_KNOT_H


#include<vector>

class SEGMENT;
class CROSS;

class KNOT{
public:                                 //member variables
    int id;
    std::vector<SEGMENT *> itsS;
    std::vector<CROSS *> itsC;
                                        //member functions
};



#endif //TOPOLOGY_KNOT_H
