#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct vertex{
	string name;
	vector<vertex*> paths;

	vertex(string n) : name(n) {}
};

struct edge{
	vertex* v1;
	vertex* v2;
	int weight = 0;

	edge(vertex* v1, vertex* v2, int w) : v1(v1),v2(v2),weight(w) {}
};

struct graph{
	vector<vertex*> vertices;
	vector<edge*> edges;

	void addVertex(string name) {vertices.push_back(new vertex(name));}
	void addEdge(vertex* a, vertex* b, int w){
		edges.push_back(new edge(a,b,w));
		a->paths.push_back(b);
	}
	void deleteEdge(vertex* a, vertex* b) {
		if (a && b){
			int index = getIndex(a->paths, b);
			if (index != -1){
				a->paths.erase(a->paths.begin()+index);
				for (int i = 0;i< edges.size();i++){
					if ((edges[i]->v1 == a) && (edges[i]->v2 == b)){
						edge* deleteMe = edges[i];
						edges.erase(edges.begin()+i);
						delete deleteMe;
						break;
					}
				}
			}
		}
	}
	void deleteVertex(vertex* a){
		if (a){
			for (vertex* pathway : a->paths){
				deleteEdge(a,pathway);
			}
			vertices.erase(vertices.begin()+getIndex(vertices,a));
			delete a;
		}
	}
	vertex* locate(string name) {for (const auto& v : vertices) {if (v->name == name){return v;}}return nullptr;}
	int getIndex(vector<vertex*> a, vertex* b){for (int i = 0;i < a.size(); i++){if (a[i] == b){return i;}}return -1;}
	void printGraph() {
		cout << " \t";
		for (const auto& v : vertices) {cout << v->name << "\t";}
		cout << endl;
		for (const auto& v : vertices) {
			cout << v->name << "\t";
			for (const auto& b : vertices){
				if (this->getIndex(v->paths, b) != -1){cout << "1\t";}else{cout << "0\t";}
			}
			cout << endl;
		}
	}
	int getEdgeWeight(vertex* v1, vertex* v2){for (const auto& e : edges) {if (e->v1 == v1 && e->v2 == v2) {return e->weight;}}}
	int findSmallestDist(vertex* v1, vertex* v2){
		
		vector<vertex*> visited;
		vector<vertex*> unvisited = vertices;
		vector<int> shortestLengths(vertices.size(), 99999);
		vector<vertex*> prevVertex(vertices.size(),nullptr);
		shortestLengths[find(vertices.begin(), vertices.end(), v1)-vertices.begin()] = 0;

		vertex* current;
		int currIndex;

		while (unvisited.size() > 0){

			//Gets minimum lengths of unvisited vertices
			int min = 100000;
			for (int i = 0;i< vertices.size();i++){
				if ((getIndex(unvisited, vertices[i] != -1) && (shortestLengths[i] < min)){
					min = shortestLengths[i];
					current = vertices[i];
					currIndex = i;
				}
			}

			//for current vertex, examine distance of each neighbor from starting vertex and update accordingly for shortest length
			for (int i = 0; i < current->paths; i++){
				vertex* neighbor = current->paths[i];
				int neighborIndex = getIndex(current->paths,neighbor);
				if (getIndex(unvisited, neighbor) != -1){
					int neighborDistance = shortestLengths[currIndex] + getEdgeWeight(current, neighbor);
					if (neighborDistance < shortestLengths[neighborIndex]){
						shortestLengths[neighborIndex] = neighborDistance;
						prevVertex[neighborIndex] = current;
					}
				}
			}

			//Move vertex from unvisited to visited
			visited.push_back(current);
			unvisited.erase(unvisited.begin() + getIndex(unvisited, current));
		}
		
		//use v2
		
		


		return 0;
	}

};

int main(){
	string command;
	graph* GRAPH = new graph();
	bool run = true;

	while (run){
		cout << "Actions:\n[A]dd [V]ertex\n[A]dd [E]dge\n[D]elete [V]ertex\n[D]elete [E]dge\n[S]how graph\n[F]ind shortest path\n[Q]uit):" << endl;
		cin >> command;

		if (command == "AV"){
			string VertexName;
			cout << "Enter name: ";
			cin >> VertexName;
			GRAPH->addVertex(VertexName); //Add confirmation that name dosen't alreay exist
		}
		else if (command == "DV"){
			string VertexName;
			cout << "Enter name: ";
			cin >> VertexName;
			vertex* deleteMe = GRAPH->locate(VertexName);
			GRAPH->deleteVertex(deleteMe);
		}
		else if (command == "AE"){
			string VertexName1, VertexName2;
			float weight;
			cout << "Enter vertices (" " in between): ";
			cin >> VertexName1 >> VertexName2;
			vertex* v1 = GRAPH->locate(VertexName1);
			vertex* v2 = GRAPH->locate(VertexName2);
			if (v1 && v2) {cout << "Weight: "; cin >> weight; GRAPH->addEdge(v1,v2,weight);}
			else{cout << "Invalid vertices" << endl;}
		}
		else if (command == "DE"){
			string VertexName1, VertexName2;
			cout << "Enter vertices (" " in between): ";
			cin >> VertexName1 >> VertexName2;
			vertex* v1 = GRAPH->locate(VertexName1);
			vertex* v2 = GRAPH->locate(VertexName2);
			GRAPH->deleteEdge(v1,v2);
		}
		else if (command == "F"){
			string VertexName1, VertexName2;
			cout << "Enter vertices ("" in between): ";
			cin >> VertexName1 >> VertexName2;
			vertex* v1 = GRAPH->locate(VertexName1);
			vertex* v2 = GRAPH->locate(VertexName2);
			if (v1 && v2) {cout << "Shortest Path Length: " << GRAPH->findSmallestDist(v1,v2) << endl;}
			else{cout << "Invalid vertices" << endl;}
	
		}
		else if (command == "S"){
			GRAPH->printGraph();
		}
		else if (command == "Q"){
			run = false;
			//Remember to wipe allocated memory
		}
		else{cout << "Unrecognized Command" << endl;}

	}
	cout << "Thank you for using Graph Creator!" << endl;
	return 0;
}
