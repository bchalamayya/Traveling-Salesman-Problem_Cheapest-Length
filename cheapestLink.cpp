/***********************************************************
 * Author: Matt Nutsch
 * Date: 6/8/2017
 * CS325, Spring 2017
 * Description: Implementation file for Cheapest Link. 
 * algorithm for TSP.
 * Pseudocode is based on the algorithm explanation found in
 * in this video: https://www.youtube.com/watch?v=nYKsLRxIBmA
 ***********************************************************/

#include "cheapestLink.hpp"
#include "structEdge.hpp"
 
using std::cout;
using std::endl;

struct tour cheapestLink(vector<struct city> cities)
{
	//declare variables
	vector<struct city> path; 
	int distance = 0; //to store the total distance
	int numberOfEdges = 0; //to track how many edges we have in total
	vector<struct graphEdge> allEdges;	//track all of the edges
	vector<struct graphEdge> edgesUsed;	//track the edges used, and their individual distances
	int numberOfEdgesUsed = 0; //to track how many edges we have used
	
	graphEdge tempEdge; //used for manipulating the vector of edges

	//find all of the edges and their distance
	//cout << "number of cities = " << cities.size() << endl;
	cout << "Identifying the edges in the graph..." << endl;
	for(int i = 0; i < (cities.size()); i++) //for each city
	{
		//cout << "City # " << cities[i].cityNum << " coordinates: " << cities[i].x << ", " << cities[i].y << endl;
		for(int j = 0; j < (cities.size()); j++) //to every other city
		{
			//cout << "Looking at edge from City # " << cities[i].cityNum << " to " << cities[j].cityNum << endl;
			//find the distance
			//cout << "Distance from City # " << cities[i].cityNum << " to " << cities[j].cityNum << " = " << distanceFromCL(cities[i], cities[j]) << endl;
			
			//as long as the origin and destination are different
			if(i != j)
			{
				//take all the weights and make a list
				tempEdge.edgeNumber = numberOfEdges;
				tempEdge.originCity = i;
				tempEdge.destinationCity = j;
				tempEdge.distance = distanceFromCL(cities[i], cities[j]);
				allEdges.push_back(tempEdge);
				//cout << "edge distance is " << allEdges[numberOfEdges].distance << endl;			
			
				numberOfEdges = numberOfEdges + 1;
			}
		}
	}
	//cout << "The number of edges is " << numberOfEdges << endl;
	
	//output the edge distances for debug
	/*
	cout << "All edges before sort:" << endl;
	for(int i = 0; i < numberOfEdges; i++) //for each city
	{
		cout << "Origin: " << allEdges[i].originCity << "; Dest: " << allEdges[i].destinationCity << "; Distance: " << allEdges[i].distance << endl;
	}
	*/
	
	//sort the list by smallest to largest edge values
	std::sort(allEdges.begin(), allEdges.end(), compareByLength);

	//output the edge distances for debug
	/*
	cout << "All edges after sort:" << endl;
	for(int i = 0; i < numberOfEdges; i++) //for each city
	{
		cout << i << ". Origin: " << allEdges[i].originCity << "; Dest: " << allEdges[i].destinationCity << "; Distance: " << allEdges[i].distance << endl;
	}
	*/
	
	cout << "finding the best path..." << endl;
	bool finishedLoop = false;
	bool originAlreadyUsed = false;
	bool destinationAlreadyUsed = false;
	bool inverseUsed = false;  	
	bool prematureCircuit = false;
	//loop through every edge
	int i = 0; //go to cheapest edge not used yet (increment i at the end of the loop as the edges are sorted)
	int tempInt = 0; //used in logic as a temporary store of info

	while(finishedLoop == false)
	{	
		cout << ".";
		//cout << i << ". ";
		//check if adding the current edge would create a circuit touching all vertices and if we are finished
		tempInt = checkIfACircuitFormed(allEdges, edgesUsed, edgesUsed.size(), allEdges.size(), allEdges[i].destinationCity, i, cities.size());
		
			//make sure that the origin has not already been used as an origin
			//also make sure that we didn't use the inverse of this edge
			//also make sure that destination has not already been used as a destination
			originAlreadyUsed = false;			
			inverseUsed = false;	
			destinationAlreadyUsed = false;
			prematureCircuit = false;
			for(int l = 0; l < numberOfEdgesUsed; l++)
			{
				if(edgesUsed[l].originCity == allEdges[i].originCity)
				{
					//skip this edge, because we already used the origin
					//cout << "skipping this edge, because we already used the origin" << endl;
					originAlreadyUsed = true;		
				}

				if((edgesUsed[l].originCity == allEdges[i].destinationCity) && (edgesUsed[l].destinationCity == allEdges[i].originCity))
				{
					//skip this edge, because we used it going the opposite direction
					//cout << "skipping this edge, because we already used it going the opposite direction" << endl;
					inverseUsed = true;
				}

				if(edgesUsed[l].destinationCity == allEdges[i].destinationCity)
				{
					//skip this edge, because we already used the destination
					//cout << "skipping this edge, because we already used the destination" << endl;
					destinationAlreadyUsed = true;		
				}  
				
			}
			
			
			//check if it would make a circuit too early
			if(tempInt == 1)
			{
				//cout << "partial circuit found :( skipping this edge" << endl;
			}
			else if((originAlreadyUsed == false) && (inverseUsed == false) && (destinationAlreadyUsed == false))
			{
				//add the edge to the path
				//cout << "adding this edge" << endl;
				tempEdge = allEdges[i];
        		edgesUsed.push_back(tempEdge);
            	numberOfEdgesUsed++;
						
				if(tempInt == 2)
				{
					//cout << "hamiltonian circuit found!" << endl;
					//if so, then stop the loop
					finishedLoop = true;
				}
			}
			
		
				
		//if we run out of edges then stop
		if(i == numberOfEdges)
		{
			//cout << "we ran out of edges to analyze. ending program. " << endl;
			finishedLoop = true;
		}
		i++;
		
		//debug, pause the program so that we can see results
		//std::cin.ignore().get();
	}
	
	//translate our vector of edges into a vector of vertices
	//cout << "number of edges used = " << numberOfEdgesUsed << endl;
	/*
	//show us the edges before organization
	cout << "the edges selected are:" << endl; 
	for(int i = 0; i < numberOfEdgesUsed; i++)
	{
		cout << "Origin: " << edgesUsed[i].originCity << "; Dest: " << edgesUsed[i].destinationCity << "; Distance: " << edgesUsed[i].distance << endl;
	}
	*/
	//organize our preferred segments into a cohesive path
	vector<struct graphEdge> edgesOrganized; //edges used, organized into a logical sequence  
	int edgesOrganizedCount = 0; //count of edges organized
	int indexOfEdgeToAdd; //temp value
	//add the first segment
	edgesOrganized.push_back(edgesUsed[0]);
	edgesOrganizedCount++; 
	//while the number of segments added < the total number of segments
	while(edgesOrganizedCount < numberOfEdgesUsed)
	{
		//find the id of the segment whose origin matches the previous segment's destination
		//cout << "looking for the index of the edge whose origin is " << edgesOrganized[(edgesOrganizedCount - 1)].destinationCity << endl;  
		for(int n = 0; n < numberOfEdgesUsed; n++)
		{
			if(edgesUsed[n].originCity == edgesOrganized[(edgesOrganizedCount - 1)].destinationCity)
			{
				indexOfEdgeToAdd = n;
				//cout << "edge found as index # " << n << endl;
			}
		}
		edgesOrganized.push_back(edgesUsed[indexOfEdgeToAdd]);
		edgesOrganizedCount++;
	}	  				

	//loop through the vector of edge path
	//cout << "the edges after organization are:" << endl;   
	for(int i = 0; i < numberOfEdgesUsed; i++)
	{
		//cout << "Origin: " << edgesOrganized[i].originCity << "; Dest: " << edgesOrganized[i].destinationCity << "; Distance: " << edgesOrganized[i].distance << endl;
		//add the destination to the vector of vertices
		path.push_back(cities[edgesOrganized[i].destinationCity]);
		
		//increase the distance
		distance = distance + edgesOrganized[i].distance;

		//cout << "distance is now " << distance << endl;
	}
	
	cout << endl;
	
	struct tour t;
    t.distance = distance;
   	t.path = path;
    return t;
}


//Distance formula to calculate distance from city a to city b.
//based on Patrick Mullaney's distanceForm function.
int distanceFromCL(struct city a, struct city b)
{

    int near;
    double n = 0.0;
    double x1 = a.x;
    double x2 = b.x;
    double y1 = a.y;
    double y2 = b.y;

    // Calculate distance.
    n = sqrt(pow((x1 - x2),2.0) + pow((y1 - y2),2.0));
    // Round up if rem >= .5 else round down.
    int temp = floor(n);
    double rem = n - temp;
    if (rem >= 0.5)
        near = ceil(n);
    else
        near = floor(n);

    return near;
}

//Utility function to help sorting vector of structs
//based on function found at: https://stackoverflow.com/questions/4892680/sorting-a-vector-of-structs
bool compareByLength(const graphEdge &a, const graphEdge &b)
{
    return a.distance < b.distance;
}

//function to detect if a circuit is formed
//0 = no a circuit was not formed
//1 = a circuit was formed, but it does not include all cities
//2 = a circuit was formed and it includes all cities 
int checkIfACircuitFormed(vector<struct graphEdge> allEdges, vector<struct graphEdge> paramEdges, int paramNumberOfParamEdges, int paramNumberOfAllEdges, int paramCitySought, int startingEdgeNumber, int numberOfAllCities)
{
	//allEdges = all edges
	////paramEdges = the edges already added
	////paramNumberOfParamEdges = number of edges sent
	////paramNumberOfAllEdges = number of all edges sent
	////paramCitySought = the city being inspected
	

	
	bool cityFound = false;
	//cout << "Looking to see if edge " << startingEdgeNumber << " leads back to itself" << endl;
	//cout << "The origin of edge " << startingEdgeNumber << " is " << allEdges[startingEdgeNumber].originCity << endl;
	//cout << "The destination of edge " << startingEdgeNumber << " is " << allEdges[startingEdgeNumber].destinationCity << endl;
	//cout << "There are " << paramNumberOfParamEdges << " edges already" << endl;
	//cout << "There are " << numberOfAllCities << " cities" << endl;
	struct graphEdge iteratorEdge; //used to iterate through the list  
	int edgesCounter = 0; //count of edges organized
	int indexOfEdgeToAdd = 9999999; //temp value
	
	//cout << "the initial destination city is " << allEdges[startingEdgeNumber].destinationCity << endl;
	//check if the destination is already in the list
	for(int n = 0; n < paramNumberOfParamEdges; n++)
	{
		if(paramEdges[n].originCity == allEdges[startingEdgeNumber].destinationCity)
		{
			indexOfEdgeToAdd = n;
			//cout << "starting with edgeUsed # " << indexOfEdgeToAdd << endl;
		}
	}

	if((paramNumberOfParamEdges > 0) && (indexOfEdgeToAdd != 9999999)) //if there is at least one edge and the destination is already in the list
	{
		//cout << "the starting edge is # " << indexOfEdgeToAdd << endl;
			
		//while the number of segments added < the total number of segments
		while(edgesCounter < paramNumberOfParamEdges)
		{
			//move the iterator to the next segment
			iteratorEdge = paramEdges[indexOfEdgeToAdd];
			
			if(iteratorEdge.destinationCity == allEdges[startingEdgeNumber].originCity)
			{
				//this forms a circuit
				cityFound = true;
				
				//check if we found all cities (one edge per vertex)
				if((paramNumberOfParamEdges + 1) == numberOfAllCities)
				{
					return 2; //we have a finished hamiltonian circuit
				}
			}
		
			//cout << "the current destination city is " << iteratorEdge.destinationCity << endl;
			//find the id of the segment whose origin matches the previous segment's destination
			for(int n = 0; n < paramNumberOfParamEdges; n++)
			{
				if(paramEdges[n].originCity == iteratorEdge.destinationCity)
				{
					indexOfEdgeToAdd = n;
					//cout << "new iterative edge found as edgesUsed index # " << n << endl; 
				}
			}
			
			edgesCounter++;
			
		}	
	}
	
	//check if the destination city is in the list of visited cities
	if(cityFound == true) 
	{
		//cout << "this is a premature circuit" << endl;

		return 1; //we have a finished circuit

	} 
	else 
	{
		//cout << "This is not a circuit" << endl;
		//the city is not in the list
		return 0;
	}	
	
	return 0;
}
