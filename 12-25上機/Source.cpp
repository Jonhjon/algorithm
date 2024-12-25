#include<iostream>
#include<fstream>
#include<vector>
#include <iomanip>
#include <queue>

using namespace std;

bool BFS(vector<vector<int>> matrix, vector<vector<int>>& flow, int start, int end, vector<int>& parent) {
	int n = flow.size();
	vector<bool> visit(n, false);
	queue<int>q;
	int queue[10] = { 0 };
	int rear = 0,front = -1;

	//q.push(start);
	queue[rear++] = start;
	
	visit[start] = true;
	parent[start] = -1;
	int min_flow = 0;
	//while (!q.empty())
	while (front < rear)
	{
		//int u = q.front();
		int u = queue[++front];
		//q.pop();
		for (int i = 0; i < n; i++)
		{
			if (!visit[i] && (flow[u][i] != matrix[u][i]))
			{
				//q.push(i);
				queue[rear++] = i;
				visit[i] = true;
				parent[i] = u;

				if (i == end)
				{
					return true;
				}
			}
		}
	}
	return false;
}

int Ford_Fulkerson(vector<vector<int>> matrix, vector<vector<int>>& flow, int start, int end) {
	int n = matrix.size();
	vector<int>parent(n);
	int maxflow = 0;

	while (BFS(matrix, flow, start, end, parent))
	{
		int pathflow = INT_MAX;
		for (int i = end; i != start; i = parent[i])
		{
			int u = parent[i];
			pathflow = min(pathflow, matrix[u][i]-flow[u][i]);
		}

		for (int i = end; i != start; i = parent[i])
		{
			int u = parent[i];
			flow[u][i] += pathflow;
		}
		maxflow += pathflow;
	}
	return maxflow;
}
void Print_matrix(vector<vector<int>> matrix, vector<vector<int>> flow, int len) {
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			cout << setw(3) << flow[i][j] << "/" << setw(2) << matrix[i][j] << ",";
		}cout << endl;
	}
}

int main() {
	fstream file;
	string path = "Graph.txt";
	file.open(path);
	int start = 0;
	int end = 5;

	if (!file.is_open())
	{
		cout << "file erro!!\n";
		file.close();
		return 0;
	}
	int len;
	file >> len;
	vector<vector<int>> matrix(len, vector<int>(len));
	vector<vector<int>> flow(len, vector<int>(len));
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++) {
			file >> matrix[i][j];
		}
	}
	file.close();

	int max_flow = Ford_Fulkerson(matrix, flow, start, end);
	Print_matrix(matrix, flow, len);
	cout <<endl<< "Maximum Flow : " << max_flow << endl;

	return 0;
}
