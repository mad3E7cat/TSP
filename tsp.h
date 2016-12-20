#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
class TSP
{
private:
	int** Matrix;
	int cities;
    int* result_output;

public:
	TSP(int _cities);
	~TSP();
	int fileInput(std::string name);
	void greedySolve(int start_city);
	void graphVizOutput();
	void matrixOutput();
	void resultOutput();
};
#include "tsp.cpp"
