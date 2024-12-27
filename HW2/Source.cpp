#include<iostream>
#include<fstream>
#include<vector>
#include <iomanip>
#include <queue>

using namespace std;
typedef struct {
	int from;
	int to;
	int weight;
}edge;

void Prim(vector<vector<int>> graph,int start) {
	int n = graph.size();
	vector<bool> visit(n, false);
	vector<int> parent(n, -1);
	vector<edge>edges;
	vector<int> minweight(n, INT_MAX);

	int total_weight = 0;
	minweight[start] = 0;
	
	for (int count = 0; count < n -1; count++)
	{
		int u = -1;
		for (int i = 0; i < n; i++)
		{
			if (!visit[i] && (u == -1 || minweight[i] < minweight[u])) {
				u = i;
			}
		}
		visit[u] = true;
		for (int  i = 0; i < n; i++)
		{
			if (graph[u][i] != 0 && !visit[i] && graph[u][i] < minweight[i])
			{
				minweight[i] = graph[u][i];
				parent[i] = u;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if(parent[i] != -1)
			edges.push_back({ parent[i], i, graph[parent[i]][i] });
	}
	for (int i = 0; i < edges.size(); i++)
	{
		cout << "Edge " << i + 1 << ":(" << char(edges[i].from + 'a') << "," << char(edges[i].to + 'a') << ") Weight : " << edges[i].weight << endl;
		total_weight += edges[i].weight;
	}
	cout << "\n\nTotal Weight : " << total_weight<<endl;
}
int main() {
	fstream file;
	string path = "Graph.txt";
	file.open(path);
	if (!file.is_open())
	{
		cout << "file erro !!\n";
		file.close();
		return 0;
	}
	int node = 0;
	file >> node;
	vector<vector<int>> graph (node,vector<int>(node,0));
	
	for (int i = 0; i < node; i++){
		for (int j = 0; j < node; j++) {
			file >> graph[i][j];
		}
	}

	Prim(graph,0);


	return 0;
}