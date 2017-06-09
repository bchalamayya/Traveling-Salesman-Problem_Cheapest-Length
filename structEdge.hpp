/*************************************************
 * Author: Matt Nutsch
 * Date: 6/6/2017
 * CS325, Spring 2017
 * Description: Header file for struct for edge.
 ************************************************/

#ifndef structEdge_hpp
#define structEdge_hpp

#include <stdio.h>

struct graphEdge
{
    int edgeNumber;
    int originCity;
    int destinationCity;
	double distance;
};

#endif /* structEdge_hpp */
