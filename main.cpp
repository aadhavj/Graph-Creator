#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct vertex{
	string name;
	vector<vertex*> paths;

	vertex(string n) : name(n) {}
};

struct edge{
	vertex* v1;
	vertex* v2;
	float weight = 0;

	edge(vertex* v1, vertex* v2, float w) : v1(v1),v2(v2),weight(w) {}
};

struct graph{
	vector<vertex*> vertices;
	vector<edge*> edges;

	void addVertex(string name) {vertices.push_back(new vertex(name));}
	void addEdge(vertex* a, vertex* b, float w){
		edges.push_back(new edge(a,b,w));
		a->paths.push_back(b);
		b->paths.push_back(a);
	}
	vertex* locate(string name) {for (const auto& v : vertices) {if (v->name == name){return v;}}return nullptr;}
	void printGraph() {for (const auto& v : vertices) {cout << "Name: " << v->name << endl; cout << "Leads:"; for (const auto& p : v->paths) {cout << p->name << " ";}cout << endl;}}		
};

int main(){
	string command;
	graph* GRAPH = new graph();
	bool run = true;

	while (run){
		cout << "Action ([A]dd [V]ertex, [A]dd [E]dge, [S]how graph,[Q]uit):" << endl;
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
}
