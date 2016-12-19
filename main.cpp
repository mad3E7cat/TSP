#include <iostream>
#include <stdio.h>
#include <fstream>
//add 2 out files - the input graph as it is and the input graph with marked path
using namespace std;
void graphVizOutput(int** M, int cities, int* path_arr, int size) // test version - only writes the full matrix into graph 
{
	ofstream outFile("out.dot"); //*.dot ?
	outFile << "graph\n{\n"; 
	for(int i = 0; i < cities; i++)
	{
		for(int j = 0; j < cities; j++)
		{
			if((i != j) &&(M[ i ][ j ] != 0))
			{
				outFile << "\t" << i + 1 << "--" << j + 1 <<"[label=\"" << M[ i ][ j ] <<"\",weight=\"" << M[ i ][ j ] << "\"];\n";
				M[j][i] = 0;
			}
		}
	}
	/////////////////////////////////////////
	// for(int i = 0; i < size - 1; i++)
	// {
	// 	outFile << "\t" << path_arr[ i ] + 1 << "--" << path_arr[ i + 1 ] + 1 <<"[label=\"" << M[ path_arr[ i ] ][ path_arr[ i + 1 ] ] <<"\",weight=\"" << M[ path_arr[ i ] ][ path_arr[ i + 1 ] ] << "\"];\n";
	// }
    outFile << "}";
	outFile.close();
}

int main()
{
	// file input begin
	system("clear");
	cout << "\n\t\t\t\t\t\tFILE INPUT\n";
	cout << "Enter the input filename: ";
	char name[64] = {'~'};
	int cities = 0;
	cin >> name;
	cout << "\nEnter number of cities:";
	cin >> cities;
	int** Matrix = new int*[cities];
	for(int i = 0; i < cities; i++)
	{
		Matrix[ i ] = new int[cities];
	}
	ifstream inFile(name);
	if(inFile.is_open())
	{
		for(int i = 0; i < cities; i++)
		{
			for(int j = 0; j < cities; j++)
			{
				inFile >> Matrix[ i ][ j ];
			}
		}
		///*
		cout << "\n\ntest matrix output:\n";
		for(int i = 0; i < cities; i++)
		{
			cout << "\n\n";
			for(int j = 0; j < cities; j++)
			{
				cout << Matrix[ i ][ j ] << " ";
			}
		}
		cout <<"\n\n";
		///*
		inFile.close();
	}
	else
	{
		cout << "Unable to open file...";
	}
	// file input finish
	//system("clear");
	char choice = 0;
	cout << "Travelling Salesman Problem";
	cout << "\n\n\n";
	cout << "Choose solution method:\n\n";
	cout << "1. Greedy Algorythm\n";
	cout << "\n2. Borders & Brunches\n";
	cin >> choice;
	if(choice == '1') //greedy algorythm
	{
		system("clear");
		int start_city = 0;
		cout << "Enter the city to begin with: " << endl;
		cin >> start_city;
		int arr_res[ 100 ]; // think of size
		int i, j; 
		int res = 0; // count of path length
		int min; // the minimum cost vertex we are to go to
		int tmp = start_city - 1; // city in which we are at the moment
	    bool visited[ 100 ] = { false }; // visited array
	    visited[ start_city - 1 ] = true; //searching from 'start_city'th city
	    for(i = 0; i < cities; i++)
	    {
	        min = -1;
	        for(j = 0; j < cities; j++)
	            if(!visited[j] && Matrix[ tmp ][ j ] > 0) // !visited[j] - если город j еще не посещали и Matrix[tmp][j]>0 - путь из города в котором находимся tmp в город j есть
	            {
	                if(min == -1) min = j;
	                else
	                {
	                    if(Matrix[ tmp ][ j ] < Matrix[ tmp ][ min ]) 
	                    {	
	                     	min = j;
	                    }
	                }
	            }
	        arr_res[ res++ ] = min; // add min vertex to result array
	        visited[ min ] = true; // min vertex is visited
	        tmp = min; // the current vertex is now min, so we write it to tmp
	    }
	    //output
	    cout<<"The path: \n" << endl;
	    cout << start_city  << " ";  // 
	    for(i = 0; i < cities - 1; i++)
	        cout << arr_res[ i ] + 1 << " ";
	    cout << start_city << endl;
		graphVizOutput(Matrix, cities, arr_res, res);
		return 0;
	}
	if(choice == '2') //borders and brunches 
	{
		// the upper border is the weight of the first counted path, the the lower border is every next weight of path, counted to the moment, if lower border is bigger then our upper border, we exclude this path from checking
		system("clear");
	}
	else
	{
		return -1;
	}
	return 0;
}
