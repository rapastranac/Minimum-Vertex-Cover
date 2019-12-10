#include"externals.h"

std::vector<int> MVC(int id, Graph &g, std::vector<int> &Visited, int depth) {
	int tmp1 = g.adj.size();		/*Size of adjacency list, if tmp1 = 0; then there is no more edges in graph*/

	//How deep the function is
	/*mtx.lock();
	if (depth > measured_Depth) {
		measured_Depth = depth;
	}
	mtx.unlock();*/

	if (tmp1 == 0) {
		leaves++;
		return Visited;	/*Terminal case*/
	}
	//-------------
	vector<int> VC1;
	vector<int> VC2;
	vector<int> C1 = Visited;
	vector<int> C2 = Visited;
	Graph G1 = g;	/*Let G1 be a copy of G*/
	Graph G2 = g;	/*Let G2 be a copy of G*/
	int r = 0;
	int rn = 0;	/*row position of */
	int tmp2 = G1.Max_degree_pos.size();
	bool gotIn = false;

	/*Let v be a vertex of G with the maximum number
	of neighbors*/
	/* initialize random seed: */
	srand(time(NULL));
	int random = 0;
	random = rand() % tmp2;

	std::future<std::vector<int>> C1_tmp;

	//--------
	/*First compute the vertex cover VC1 in which we include v*/
	/*Remove v and its edges from G1*/
	r = G1.Max_degree_pos[random];	/*position of any of the highest degree vertices, choosen randomly*/
									//r = G1.Max_degree_pos[0];		/*temporary, to fix value at 1, don't forget to erase*/
	C1.push_back(G1.adj[r][0]);
	G1.remove_edge(r, G1.adj[r][0]);

		
	mtx.lock();
	if (numThreads<maxThreads) {
		numThreads++;
		gotIn = true;
		mtx.unlock();
		C1_tmp = pool.push(MVC, ref(G1),  ref(C1), ref(depth));
	}
	else {
		mtx.unlock();
		VC1 = MVC(0, G1, C1, depth++);
	}
	compute_VC2(g, r, tmp1, G2, rn, C2, VC2, depth++);

	if (gotIn) {
		VC1 = C1_tmp.get();
	}
	mtx.lock();
	if (gotIn) {
		numThreads--;
		mtx.unlock();
	}
	else{ 
		mtx.unlock(); 
	}

	if (VC1.size() >= VC2.size()) return VC2;
	else return VC1;
}

//void compute_VC1(int id, int& r, Graph& G1, int random, std::vector<int>& C1, std::vector<int>& VC1, int depth)
//{
//	/*First compute the vertex cover VC1 in which we include v*/
//	/*Remove v and its edges from G1*/
//	r = G1.Max_degree_pos[random];	/*position of any of the highest degree vertices, choosen randomly*/
//									//r = G1.Max_degree_pos[0];		/*temporary, to fix value at 1, don't forget to erase*/
//	C1.push_back(G1.adj[r][0]);
//	G1.remove_edge(r, G1.adj[r][0]);
//	//VC1 = MVC(G1, C1, left + 1, right);
//}
void compute_VC2(Graph& g, int r, int tmp1, Graph& G2, int& rn, std::vector<int>& C2, std::vector<int>& VC2, int depth)
{
	/*w represents the neighbours of v*/
	/*Remove w and its edges from G2*/
	int w;
	int n_tmp = g.adj[r].size();	/*size of the row containing neighbours of v*/
	for (int j = 1; j < n_tmp; j++)
	{
		w = g.adj[r][j];
		for (int i = 0; i < tmp1; i++)	/*Searching position of w within G2*/
		{
			if (G2.adj[i][0] == w) /*it can be improved by binary search*/
			{
				rn = i;
				break;
			}
		}
		/*Look up r within G2*/
		C2.push_back(w);
		G2.remove_edge(rn, w);
	}
	VC2 = MVC(0, G2, C2, depth++);
}

