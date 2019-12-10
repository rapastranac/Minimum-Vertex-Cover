#include "externals.h"

void readfile(Graph& g) {
	using namespace std;
	string line;
	vector<string> split;
	int i = 0;
	while (1)
	{
		line = Util::GetFileLine("List.txt", i);
		if (line == "") break;
		split = Util::Split(line, "\t");
		g.addEdge(Util::ToInt(split[0]), Util::ToInt(split[0]));
		for (int i = 1; i != split.size(); i++) {
			g.addEdge(Util::ToInt(split[0]), Util::ToInt(split[i]));
		}
		i++;
	}
}