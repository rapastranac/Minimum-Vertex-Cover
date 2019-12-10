#include "externals.h"

void Vertex_max_degree(Graph& g, int N_vertices) {
	int tmp;
	/*Finding vertex degrees, in order to start exploring by these ones.*/
	for (int i = 0; i < N_vertices; i++)
	{
		tmp = g.adj[i].size() - 1;
		g.Vertex_degree.push_back(tmp);
		if (tmp > g.max) g.max = tmp;
	}
	for (int i = 0; i < N_vertices; i++)
	{
		if (g.Vertex_degree[i] == g.max) {
			g.Max_degree_pos.push_back(i);
		}
	}
}