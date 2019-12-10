#include<iostream> 
#include <list> 
#include <vector>
#include "util.h"
#include "externals.h"
#include "Graph.h"
#include <ctime>


using namespace std;
// This struct represents a undirected graph using adjacency list 
int maxThreads = 11;
ctpl::thread_pool pool(maxThreads);
long long int leaves;
int numThreads;	
std::mutex mtx;
int maxDepth = 20;
int measured_Depth = 0;

int main()
{
	vector<int> Visited;		/*vertices visited by the algorithm (Minimum vertex cover)*/
	vector<int> VCMin;
	Graph g;					/*create a graph*/
	g.V = 90;					/*number of vertices in graph*/
	g.adj.resize(g.V);			/*giving dimension to graph*/
	readfile(g);				/*read graph from file*/
	Vertex_max_degree(g, g.V);	/*counting the edges of each vertex*/
	leaves = 0;
	numThreads = 0;

	clock_t begin = clock();
	VCMin = MVC(0, g, Visited, 0);	/*minimum vertex cover*/
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	//Printing the minimum vertex cover
	int sizemvc = VCMin.size();
	printf("---------------------------------------------------------- \n");
	printf("Minimum vertex cover is: ");
	for (int i = 0; i < VCMin.size(); i++) cout << VCMin[i] << "\t";
	printf("\n");
	printf("Size: %i \n", sizemvc);
	printf("Elapsed time : %f \n", elapsed_secs);
	printf("Number of leaves : %i \n", leaves);
	printf("Maximum depth reached : %i \n", measured_Depth);
	printf("---------------------------------------------------------- \n");
	system("pause");
	return 0;
}
