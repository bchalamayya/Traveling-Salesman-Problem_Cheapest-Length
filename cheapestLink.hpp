/***********************************************************
 * Author: Matt Nutsch
 * Date: 6/6/2017
 * CS325, Spring 2017
 * Description: Implementation file for Cheapest Link. 
 * algorithm for TSP.
 ***********************************************************/
 
#ifndef cheapestLink_hpp
#define cheapestLink_hpp

#include <stdio.h>
#include "structCity.hpp"
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "structTour.h"
#include "structEdge.hpp"
#include <algorithm> //for std::sort

using std::vector;

struct tour cheapestLink(vector<struct city> cities); //find the path using the cheapest link algorithm
int distanceFromCL(struct city a, struct city b); //calculate the distance between two points
bool compareByLength(const graphEdge &a, const graphEdge &b); //used to sort vectors of structs
int checkIfACircuitFormed(vector<struct graphEdge> allEdges, vector<struct graphEdge> paramEdges, int paramNumberOfParamEdges, int paramNumberOfAllEdges, int paramCitySought, int startingEdgeNumber, int numberOfAllCities);

#endif /* cheapestLink_hpp */
