#include<iostream>
#include<fstream>
#include<stdio.h>
#include<algorithm>
using namespace std;
#define Max 20
typedef struct edge {
	int from;
	int to;
	int weight;
}edge;


int find(int parent[], int i) {
	if (parent[i] == i)
		return parent[i];
	find(parent, parent[i]);
}

int Partition(edge edges[], int p, int r) {
	int x = edges[r].weight;
	int i = p - 1;
	edge temp;
	for (int j = p; j < r; j++)
	{
		if (edges[j].weight <= x) {
			i++;
			temp = edges[j];
			edges[j] = edges[i];
			edges[i] = temp;
		}
	}
	temp = edges[i + 1];
	edges[i + 1] = edges[r];
	edges[r] = temp;
	return i + 1;
}
void Quicksort(edge edges[], int p, int r) {
	if (p < r)
	{
		int q = Partition(edges, p, r);
		Quicksort(edges, p, q - 1);
		Quicksort(edges, q + 1, r);
	}
}
void KruskalMST(edge edges[], int edge_count, int vector) {
	int parent[20] = { 0 };
	int rank[20] = { 0 };
	//bool *vist=new bool[vector];

	for (int i = 0; i < vector; i++)
	{
		parent[i] = i;
		rank[i] = 0;
		//vist[i] = false;
	}

	edge result[Max];
	int e = 0;
	int i = 0;
	cout << "point1	point2	cost\n";

	while (e < vector - 1 && i < edge_count)
	{
		edge edge_next = edges[i++];

		int x = find(parent, edge_next.from);
		int y = find(parent, edge_next.to);

		if (x != y)
		{
			result[e++] = edge_next;
			cout << edge_next.from << "\t" << edge_next.to << "\t" << edge_next.weight << endl;
			parent[y] = x;

			//Union(parent,rank,x,y);
		}
	}
	int total_weight = 0;

	for (int i = 0; i < e; i++)
	{
		//cout << result[i].from << "\t" << result[i].to << "\t" << result[i].weight << endl;
		total_weight += result[i].weight;
	}
	cout << "\ntotal weight : " << total_weight;
}

int main()
{
	fstream file;
	int num = 0;
	int count = 0;
	file.open("Data.txt");
	if (!file.is_open())
	{
		cout << "file erro!!\n";
		file.close();
		return 0;
	}
	edge edge[50] = { 0 };
	int len_num = 0;
	file >> len_num;
	for (int i = 0; i < len_num; i++)
	{
		for (int j = 0; j < len_num; j++)
		{
			file >> num;
			if (num != 0 && j >= i)
			{
				edge[count].from = i;
				edge[count].to = j;
				edge[count].weight = num;
				count++;
			}
		}
	}
	Quicksort(edge, 0, count - 1);
	//sort(edge, edge + count, weight_compare);
	cout << "point1	point2	cost\n";
	for (int i = 0; i < count; i++)
	{
		cout << edge[i].from << "\t" << edge[i].to << "\t" << edge[i].weight << endl;
	}
	cout << endl << endl;
	KruskalMST(edge, count, len_num);

	return 0;
}