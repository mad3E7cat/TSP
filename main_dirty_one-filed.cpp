#include <iostream>
#include "tsp.h"
using namespace std;

int main()
{
	char choice = 0;
	cout << "\t\tTravelling Salesman Problem";
	cout << "\n\n\n";
	cout << "\tGreedy Algorythm\n";
	TSP tsp_problem1(7);
	string name;
	cout << "\nEnter the filename: ";
	cin >> name;
	tsp_problem1.fileInput(name);
	tsp_problem1.matrixOutput();
	tsp_problem1.greedySolve(5);
	tsp_problem1.resultOutput();
	tsp_problem1.graphVizOutput();
	return 0;
}