#include "tsp.h"
TSP::TSP(int _cities)
{
	cities = _cities;
	result_output = new int[cities + 1];
	Matrix = new int*[cities];
	for(int i = 0; i < cities; i++)
	{
		Matrix[ i ] = new int[cities];
	}
}
TSP::~TSP()
{
	delete result_output;
	for(int i = 0; i < cities; i++)
	{
		delete Matrix[i];
	}
	delete []Matrix;
	cities = 0;
}
int TSP::fileInput(std::string name)
{
	std::ifstream inFile(name);
	if(inFile.is_open())
	{
		for(int i = 0; i < cities; i++)
		{
			for(int j = 0; j < cities; j++)
			{
				inFile >> Matrix[ i ][ j ];
			}
		}
		inFile.close();
		return 0;
	}
	else
	{
		std::cout << "Unable to open file...";
		return -1;
	}
	system("clear");
}
void TSP::greedySolve(int start_city)
{
	system("clear");
	std::cout << "Beginning from city #" << start_city << std::endl;
	int arr_res[ cities ];
	int i, j; 
	int res = 0; // count of path length
	int min; // the minimum cost vertex we are to go to
	int tmp = start_city - 1; // city in which we are at the moment
    bool visited[ cities ] = { false }; // visited array
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
    result_output[ 0 ] = start_city;
    for(i = 0; i < cities - 1; i++)
    {
        result_output[ i + 1 ] = arr_res[ i ]  + 1;
    }
    result_output[ cities ] = start_city;
   	//graphVizOutput(Matrix, cities, result_output, res);
	//return 0;
}
void TSP::resultOutput()
{
	system("clear");
    std::cout<<"\nThe path: \n" << std::endl;
    for(int i = 0; i <= cities; i++)
    {
    	std::cout << result_output[ i ] << " ";
    }
    std::cout << std::endl;
}
void TSP::matrixOutput()
{
	std::cout << "\n\n";
	for(int i = 0; i < cities; i++)
	{
		std::cout << "\n\n";
		for (int j = 0; j < cities; j++)
		{
			std::cout << Matrix[ i ][ j ] << " ";
		}
	}
	std::cout << "\n\n" << std::endl;
}
void TSP::graphVizOutput()
{
	//file 1
	std::ofstream outFile1("out_basic.dot"); //*.dot ?
	outFile1 << "graph\n{\n";
	for(int i = 0; i < cities; i++)
	{
		for(int j = i; j < cities; j++)
		{
			if(Matrix[ i ][ j ] > 0)
			{
			 	outFile1 << "\t" << i + 1 << "--" << j + 1 <<"[label=\"" << Matrix[ i ][ j ] <<"\",weight=\"" << Matrix[ i ][ j ] << "\"];\n";
			}
		}
	}
	outFile1 << "}";
	outFile1.close();
	//file 2
	std::ofstream outFile2("out_path.dot"); //*.dot ?
	outFile2 << "graph\n{\n";
	bool M_chck[cities][cities];
	for(int i = 0; i < cities; i++)
	{
		for(int j = 0; j < cities; j++)
		{
			M_chck[ i ][ j ] = false;
		}
	}
	int i_c = 0;
	for(int i = 0; i < cities; i++)
	{
		for(int j = 0; j < cities; j++)
		{
			if( ((i == (result_output[ i_c ] - 1)) && (j == (result_output[ i_c + 1] - 1))) || ((i == (result_output[ i_c + 1] - 1)) && (j == (result_output[ i_c ] - 1))) )
			{
				outFile2 << "\t" << i + 1 << "--" << j + 1 <<"[label=\"" << Matrix[ i ][ j ] <<"\",weight=\"" << Matrix[ i ][ j ] << "\", color=\"red\"];\n";
				Matrix[j][i] = 0;
				i_c++;
				i = 0;
				j = 0;
				M_chck[ i ][ j ] = true;
				M_chck[ j ][ i ] = true;
			}
		}
	}
	for(int i = 0; i < cities; i++)
	{
		for(int j = i; j < cities; j++)
		{
			if((M_chck[ i ][ j ] == false) && (Matrix[i][j] > 0) && (Matrix[j][i] > 0) && (M_chck[ j ][ i ] == false) && (i != j) )
			{
			 	outFile2 << "\t" << i + 1 << "--" << j + 1 <<"[label=\"" << Matrix[ i ][ j ] <<"\",weight=\"" << Matrix[ i ][ j ] << "\"];\n";
			}
		}
	}
	outFile2 << "}";
	outFile2.close();
	system("dot -Tps out_basic.dot -o graph.ps");
	system("dot -Tps out_path.dot -o path.ps");
}