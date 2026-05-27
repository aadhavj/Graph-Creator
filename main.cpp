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
	vertex* locate(string name) {for (const auto& v : vertices) {if (v->name == name){return v;}}return nullptr;}
	void printGraph() {for (const auto& v : vertices) {cout << "Name: " << v->name << endl; cout << "Leads:"; for (const auto& p : v->paths) {cout << p->name << " ";}cout << endl;}}
	int getEdgeWeight(vertex* v1, vertex* v2){for (const auto& e : edges) {if (e->v1 == v1 && e->v2 == v2) {return e->weight;}}}
	int findSmallestDist(vertex* v1, vertex* v2){
		vector<vertex*> visited;
		vector<vertex*> unvisited = vertices;
		vector<int> shortestLengths(vertices.size(), 99999);
		vector<vertex*> prevVertex(vertices.size(),nullptr);
		shortestLengths[find(vertices.begin(), vertices.end(), v1)-vertices.begin()] = 0;
		

		//unvisited.erase(unvisited.begin());
		return 0;
	}

};

int main(){
	string command;
	graph* GRAPH = new graph();
	bool run = true;

	while (run){
		cout << "Action ([A]dd [V]ertex, [A]dd [E]dge, [S]how graph, [F]ind shortest path, [Q]uit):" << endl;
		cin >> command;

		if (command == "AV"){
			string VertexName;
			cout << "Enter name: ";
			cin >> VertexName;
			GRAPH->addVertex(VertexName); //Add confirmation that name dosen't alreay exist
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
