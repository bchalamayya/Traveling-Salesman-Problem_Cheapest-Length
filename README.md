# Traveling-Salesman-Problem---Cheapest-Length

This is a c++ implementation of the Cheapest Link solution to the Traveling Salesman Problem. It was written as part of a project for a class in computer Algorithms. The goal was to come up with the best in class algorithm for solving the Traveling Salesman Problem. (For more info on the Traveling Salesman Problem, see the Wikipedia page: https://en.wikipedia.org/wiki/Travelling_salesman_problem.)

Algorithm: Cheapest Link Algorithm
 
Synopsis:
Cheapest Link is an algorithm which attempts to find the shortest by sequentially adding the shortest edges in the graph. The rationale is that by taking the shortest graph edges possible, then we get a reasonably short distance every time. 
 
Discussion:
I decided to try this algorithm after researching Google Maps. Google Maps actually uses numerous algorithms in parallel to find the best path to a destination. However "Cheapest Arc", a derivative of Cheapest Link was the first algorithm mentioned in Google's documentation. Google's documentation turned out to not be that helpful in writing the code, other than providing inspiration. Online lecture videos about the Cheapest Link algorithm provided clearer explanations on how to implement it. In particular the online video "Cheapest Link Algorithm" by MSLT Mathematics was very helpful in explaining the algorithm.
 
Pseudocode:
 
Main code
{
//Create a list of edges from the list of cities
For every city loop
    For every city loop again
        Add an edge to a vector containing the list of edges
        Calculate the length for the edge (distance between origin city and destination city)
        Skip items where the origin and the destination city are the same
 
Sort the list of edges by length in ascending order
 
//Select the edges to use
Loop
    Sequentially examine each available edge, starting with the shortest length
    Skip edges where the origin city has already been used.
    Skip edges where the destination city has already been used.
    Skip edges where we already used the inverse of the edge (where origin and destination are swapped).
    Skip edges which would make a circuit too early.
    Break the loop if we reach a Hamiltonian circuit, or if we run out of edges
    Otherwise add the current edge to a list of edges to use
 
Organize the selected selected edges into a cohesive path, based on the origin city of each each edge and destination city of the predecessor edge. (loop)
 
Calculate the total distance and copy the values to the output. (loop)
}
 
distanceFromCL //utiltity function for finding the distance between two cities
{ Given two sets of x and y coordinates, find the distance between them }
 
compareByLength() //utility function used in sorting
{ return a value indicating if the length of the first parameter is less than the length of the second parameter }
 
checkIfACircuitFormed() //function to check if adding an edge would create a premature circuit, a Hamilton circuit, or no circuit
{
    Check if the parameter edge's destination is already in the list
 
    If so, then loop for the number of edges already selected
        Iterate to the next edge based on the destination of the previous edge
        If the iterator's destination = parameter edge's destination AND the number of edges selected matches the number of cities, then return that we found a Hamiltonian circuit.
        Else If the iterator's destination = parameter edge's destination AND the number of edges selected does NOT match the number of cities, then return that we found a premature circuit.
        
    If we finish the loop without already returning a value, then return that adding the parameter edge would not create a circuit.
 
}
