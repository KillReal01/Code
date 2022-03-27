#include <iostream>
#include <fstream>
#include "struct.h"
#include "vector.h"

struct edge {
	int src, dest;
	int size;
};

const int count_v = 50;

void insertVertexList(vector<std::string>& vertices, std::string str);
int convertName(vector<std::string>& vertices, std::string str);
bool readFile(std::string file_name, vector<edge>& edges, vector<std::string>& vertex_collection);

void quickSortWeight(vector<edge>& arr, int begin, int end);
void quickSortName(vector<edge>& arr, vector<std::string>& vertex_collection, int begin, int end);

void printGraph(vector<edge>& edges, vector<std::string>& v);

int findDS(vector<int>& disjointSet, int index);
void unionDS(vector<int>& disjointSet, int a, int b);
int totalWeight(vector<edge>& edges);
void Krascal(vector<edge>& edges, vector<edge>& mst, vector<std::string>& vertex_collection);

void BFS(vector<edge>& edges, vector<std::string>& vertex_collection, int u);
void DFS(vector<edge>& edges, vector<std::string>& vertex_collection, int u);

int main() {
	vector<edge> edges, mst;
	vector<std::string> vertex_collection;
	std::string str = "input.txt";
	if (readFile(str, edges, vertex_collection)) {
		Krascal(edges, mst, vertex_collection);
		std::cout << "MST:\n";
		printGraph(mst, vertex_collection);
		std::cout << totalWeight(mst);

		std::cout << "\n";
		BFS(edges, vertex_collection, 0);
		DFS(edges, vertex_collection, 0);
	}
	return 0;
}

bool readFile(std::string file_name, vector<edge>& edges, vector<std::string>& vertex_collection) {
	std::ifstream file;
	file.open(file_name);
	if (!file.is_open()) {
		std::cout << "file can not be open!\n";
		return false;
	}
	else {
		std::string src, dest;
		int size, id_s, id_d;
		while (!file.eof())
		{
			file >> src >> dest >> size;
			insertVertexList(vertex_collection, src);
			insertVertexList(vertex_collection, dest);
			id_s = convertName(vertex_collection, src);
			id_d = convertName(vertex_collection, dest);
			edges.push_back({ id_s, id_d, size });
		}
		file.close();
		return true;
	}
}

void insertVertexList(vector<std::string>& vertex_collection, std::string str) {
	bool flag = true;
	for (int i = 0; i < vertex_collection.size(); i++) {
		if (vertex_collection[i] == str) {
			flag = false;
			break;
		}
	}
	if (flag)
		vertex_collection.push_back(str);
}

int convertName(vector<std::string>& vertex_collection, std::string str) {
	for (int i = 0; i < vertex_collection.size(); i++) {
		if (vertex_collection[i] == str) {
			return i;
		}
	}
	return count_v + 1;
}

void quickSortWeight(vector<edge>& arr, int begin, int end) {
	int i = begin, j = end;
	edge mid = arr[(i + j) / 2];
	while (i < j)
	{
		while (arr[i].size < mid.size) {
			i++;
		}
		while (arr[j].size > mid.size) {
			j--;
		}
		if (i <= j) {
			std::swap(arr[i], arr[j]);
			i++; j--;
		}
	}
	if (begin < j) {
		quickSortWeight(arr, begin, j);
	}
	if (i < end) {
		quickSortWeight(arr, i, end);
	}
}

void quickSortName(vector<edge>& arr, vector<std::string>& v, int begin, int end)
{
	int i = begin, j = end;
	std::pair<std::string, std::string> mid, tmp;
	mid = std::make_pair(v[arr[(i + j) / 2].src], v[arr[(i + j) / 2].dest]);
	while (i < j) {
		tmp = std::make_pair(v[arr[i].src], v[arr[i].dest]);
		while (tmp < mid) {
			i++;
			tmp = std::make_pair(v[arr[i].src], v[arr[i].dest]);
		}
		tmp = std::make_pair(v[arr[j].src], v[arr[j].dest]);
		while (tmp > mid) {
			j--;
			tmp = std::make_pair(v[arr[j].src], v[arr[j].dest]);
		}
		if (i <= j) {
			std::swap(arr[i], arr[j]);
			i++; j--;
		}
	}
	if (begin < j) {
		quickSortName(arr, v, begin, j);
	}
	if (i < end) {
		quickSortName(arr, v, i, end);
	}
}

void printGraph(vector<edge>& edges, vector<std::string>& v) {
	for (int i = 0; i < edges.size(); i++) {
		std::cout << v[edges[i].src] << " " << v[edges[i].dest];
		//std::cout << " " << edges[i].size;
		std::cout << "\n";
	}
}

int findDS(vector<int>& disjointSet, int index) {
	return disjointSet[index];
}

void unionDS(vector<int>& disjointSet, int a, int b) {
	int k_a = 0, k_b = 0;
	for (int i = 0; i < disjointSet.size(); i++) {
		if (disjointSet[i] == disjointSet[a]) k_a++;
		if (disjointSet[i] == disjointSet[b]) k_b++;
	}
	if (k_a > k_b)
		std::swap(a, b);
	int tmp = disjointSet[b];
	for (int i = 0; i < disjointSet.size(); i++)
		if (disjointSet[i] == tmp)
			disjointSet[i] = a;
}

int totalWeight(vector<edge>& edges) {
	int sum = 0;
	for (int i = 0; i < edges.size(); i++)
		sum += edges[i].size;
	return sum;
}

void Krascal(vector<edge>& edges, vector<edge>& mst, vector<std::string>& vertex_collection) {
	vector<int> disjointSet(vertex_collection.size());
	for (int i = 0; i < disjointSet.size(); i++)
		disjointSet[i] = i;
	quickSortWeight(edges, 0, edges.size() - 1);

	int i = 0;
	mst.push_back(edges[i]);
	unionDS(disjointSet, edges[i].src, edges[i].dest);

	while (edges.size() - 1 != i) {
		int a = edges[i + 1].src, b = edges[i + 1].dest;
		int k1 = findDS(disjointSet, disjointSet[a]), k2 = findDS(disjointSet, disjointSet[b]);
		if (k1 != k2) {
			unionDS(disjointSet, k1, k2);
			mst.push_back(edges[i + 1]);
		}
		i++;
	}
	quickSortName(mst, vertex_collection, 0, mst.size() - 1);
}

void BFS(vector<edge>& edges, vector<std::string>& vertex_collection, int u) {
	vector<bool> used(vertex_collection.size());
	for (int i = 0; i < vertex_collection.size(); i++)
		used[i] = false;

	quickSortName(edges, vertex_collection, 0, edges.size() - 1);
	std::cout << "\nBFS: ";
	queue<int> q;
	q.push(u);
	used[u] = true;

	while (!q.is_empty()) {
		u = q.front();
		std::cout << vertex_collection[u] << " ";
		q.pop();
		
		for (int i = 0; i < edges.size(); i++) {
			if (edges[i].src == u) {
				int v = edges[i].dest;
				if (!used[v]) {
					used[v] = true;
					q.push(v);
				}
			}
		}
	}
}

void DFS(vector<edge>& edges, vector<std::string>& vertex_collection, int u) {
	vector<bool> used(vertex_collection.size());
	int v;
	for (int i = 0; i < vertex_collection.size(); i++)
		used[i] = false;
	quickSortName(edges, vertex_collection, 0, edges.size() - 1);
	std::cout << "\nDFS: ";
	stack<int> s;
	s.push(u);
	used[u] = true;
	while (!s.is_empty()) {
		u = s.top();
		if (used[u]) {
			std::cout << vertex_collection[u] << " ";
			s.pop();
		}
		else {
			used[u] = true;
		}
		for (int i = edges.size() - 1; i >= 0; i--) {
			if (edges[i].src == u) {
				v = edges[i].dest;
				if (!used[v]) {
					used[v] = true;
					s.push(v);
				}
			}
		}
	}
}
