/************************************************
 * Author: Patrick Mullaney
 * Date: 5/29/2017
 * CS325, Spring 2017
 * Description: Main driver for program for TSP.
 ************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include "structCity.hpp"
#include "structEdge.hpp"
#include <iomanip>
#include <cmath>
#include <ctime>
//#include "nearestNeighbor.hpp"
//#include "repNeighbor.hpp"
#include "cheapestLink.hpp"

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, const char * argv[])
{
    /* Seed rand */
    srand(time(NULL));
        
    /* Will take arguments from command line or default to example 1. */
    const char* fileName = "test-input-1.txt";
    
    std::ofstream outputFile;
    string tour = ".tour";
    if(argc > 1)
    {
        fileName = argv[1];
        string fileN(fileName);
       // outputFile.open(fileN + tour);
        tour = fileN+tour;
    }
    else
	{
        tour = fileName+tour;
    }
	
    std::ifstream inputFile(fileName);
    string readFile(fileName);

    string line;
    string number;
    
    vector<struct city> cities;
    
    if(inputFile.is_open())
    {
        // Read input line by line.
        while(getline(inputFile, line))
        {
            // Get city info.
            std::stringstream stream(line);
            vector<int> numbers((std::istream_iterator<int>(stream)),
                                (std::istream_iterator<int>()));
            
            // Assign to city and add to vector.
            struct city c;
            c.cityNum = numbers[0];
            c.x = numbers[1];
            c.y = numbers[2];
            c.visited = false;
            cities.push_back(c);
        }
        inputFile.close();
        
        double diff;
        clock_t start, end;
   
        /* Nearest neighbor algorithm */
		/*
        cout << "Testing nearestNeighbor....." << endl;
        start = clock();
        struct tour t = nearestNeighbor(cities);
        end = clock();
        diff = (end-start);
        diff = diff/CLOCKS_PER_SEC;
		// diff = diff * 1000;
        int tourLength = t.distance;
        cout << "Length of nearest tour: " << tourLength << endl;
        cout.precision(10);
        cout << "Time nearest (m/s): " << std::fixed << diff << endl;
        */
		/* cout << "Testing repetitive Neighbor....." << endl;
        start = clock();
        struct tour r = repNearest(cities);
        end = clock();
        diff = (end-start);
        diff = diff/CLOCKS_PER_SEC;
        int repTourLength = r.distance;
        cout << "Length of repetitive: " << repTourLength << endl;
        cout << "Time of repetitive: " << diff << endl; */
        
		cout << "Testing Cheapest Link....." << endl;
        start = clock();
        struct tour t = cheapestLink(cities);
        end = clock();
        diff = (end-start);
        diff = diff/CLOCKS_PER_SEC;
		// diff = diff * 1000;
        int tourLength = t.distance;
        cout << "Length of nearest tour: " << tourLength << endl;
        cout.precision(10);
        cout << "Time nearest (m/s): " << std::fixed << diff << endl;
		
        // Output to file
        outputFile.open(tour);
        if(outputFile.is_open())
        {
            outputFile << tourLength << "\n";
            cout << "Length of tour: " << tourLength << endl;
            for(int i = 0; i < t.path.size(); i++)
            {
                outputFile << t.path[i].cityNum << "\n";
                //outputFile.flush();
            }
            outputFile.flush();
            outputFile.close();
        }
        else
		{
			cout << "File did not open for write" << endl;
		}
    }
    else
	{
        cout << "File not found." << endl;
    }
	
    return 0;
}

