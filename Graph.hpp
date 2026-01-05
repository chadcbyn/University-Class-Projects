#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <limits>
#include <queue>
#include <utility>

/*
 Name: Chad Bynum
 Email: ccbynum@crimson.ua.edu
 Course Section: Fall 2025 CS 201
 Homework #: 4
 To Compile: g++ -Wall GraphDemo.cpp
 To Run: ./a.out inputX.txt
*/

class Vertex {
public:
	bool visited;
	int distance;
	int previous;
	int finish;
	std::list<int> adj;
};

class Graph {
public:
	Graph(int V, int E, std::pair<int, int> *edges) {
		_V = V;
		_E = E;
		vertices = new Vertex[_V];
		_time = 0;
		for (int i = 0; i < _V; i++) {
                    vertices[i].visited = false;
                    vertices[i].distance = 65535; // Instead using INFINITY, you can use a large int number to initialize your graph
                    vertices[i].previous = -1;
		}
		for (int i = 0; i < _E; i++) {
		    addEdge(edges[i].first, edges[i].second);
		}
	}

	virtual ~Graph() {
		for (int i=0; i<_V; ++i) {
		    auto adj = vertices[i].adj;
		    adj.clear(); // clear list
		}

		delete[] vertices; // delete array of vertices
	}

	int V() {
		return _V;
	}

	int E() {
		return _E;
	}

	void addEdge(int u, int v) {
		vertices[u].adj.push_back(v);
	}

	std::list<int> getEdges(int u) {
		return vertices[u].adj;
	}

	int degree(int u) {
		return vertices[u].adj.size();
	}

	void bfs(int s) {
		// initialize
		for (int i = 0; i < _V; ++i) {
			vertices[i].visited = false;
			vertices[i].distance = std::numeric_limits<int>::max();
			vertices[i].previous = -1;
		}

		std::queue<int> q;
		std::list<int> bfs_order;
		vertices[s].visited = true;
		vertices[s].distance = 0;
		vertices[s].previous = -1;
		q.push(s);

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			bfs_order.push_back(u);
			for (const auto &v : vertices[u].adj) {
				if (!vertices[v].visited) {
					vertices[v].visited = true;
					vertices[v].distance = vertices[u].distance + 1;
					vertices[v].previous = u;
					q.push(v);
				}
			}
		}

		// output FINAL list
		for (const auto &v : bfs_order) {
			std::cout << v << " ";
		}
		std::cout << std::endl;
	}

	void dfs() {
		// reset
		for (int i = 0; i < _V; ++i) {
			vertices[i].visited = false;
			vertices[i].previous = -1;
			vertices[i].finish = 0;
		}
		_time = 0;
		

		for (int i = 0; i < _V; ++i) {
			if (!vertices[i].visited) {
				// Start a new tree with root i
				std::list<int> tree_vertices;
				dfs_visit(i, tree_vertices);
				
				// Print the tree: show root and all paths from root to vertices
				int root = i;
				// Print root by itself first
				std::cout << root;
				// Then print paths from root to all other vertices in the tree
				for (const auto &v : tree_vertices) {
					if (v != root) {
						std::cout << std::endl;
						print_path(root, v);
					}
				}
				std::cout << std::endl;
			}
		}
	}

	void dfs_visit(int u, std::list<int> &tree_vertices) {
		vertices[u].visited = true;
		tree_vertices.push_back(u);
		// discovery time
		_time++;
		vertices[u].distance = _time;
		for (const auto &v : vertices[u].adj) {
			if (!vertices[v].visited) {
				vertices[v].previous = u;
				dfs_visit(v, tree_vertices);
			}
		}
		// finish time
		_time++;
		vertices[u].finish = _time;
	}

	void print_path(int s, int v) {
		if (v == s)
		   std::cout << s;
		else if (vertices[v].previous == -1)
		   std::cout << "not connected";
		else {
		   print_path(s,vertices[v].previous);
		   std::cout << "->" << v;
		}
	}

	std::string toString() {
		std::stringbuf buffer;
		std::ostream os(&buffer);
		os << "Vertices = " << _V << ", Edges = " << _E << std::endl;
		for (int i = 0; i < _V; ++i) {
		    os << i << "(" << degree(i) << "): ";
		    for (const auto& l : vertices[i].adj) 
			os << l << " ";
		    os << std::endl;
		}

		return buffer.str();
	}
private:
	int _V; // no. of vertices
	int _E; // no. of edges
	Vertex *vertices; // array of vertices
	int _time; // DFS time counter
};

#endif
