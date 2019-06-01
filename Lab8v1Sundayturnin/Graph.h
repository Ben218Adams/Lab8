#pragma once

// Most of this structure ripped off from that
//  ...Created by Jim Bailey on 11/25/17.

#ifndef GRAPH_H
#define GRAPH_H

#include <string>

struct Edge
{
	int endIndex;
	Edge* next;
};

struct Node
{
	char name;
	bool visited;
	Edge* connects;
};


class Graph
{
public:
	Graph()
	{
		numNodes = 0;	// initialize number of nodes in list
		for (int i = 0; i < SIZE; i++)	// initialize nodeList to nullptrs
			this->nodeList[i] = nullptr;	// Adding Curlys here 
		for (int i = 0; i < SIZE; i++)	// set up edge Matrix to start with no edges
			for (int j = 0; j < SIZE; j++)
				this->edgeMatrix[i][j] = {0};		// Adding Curlys here 
	}
	virtual ~Graph()
	{
		// delete all connections from each node in nodeList
		for (int i = 0; i < numNodes; i++)
		{
			// similar to destructor on linked list
			Edge* ptr = nodeList[i]->connects;
			while (ptr != nullptr)
			{
				Edge* temp = ptr;
				ptr = ptr->next;
				delete temp;
			}
		}
	}

	void addNode(char name);
	bool addEdge(char starts, char ends);

	std::string listNodes();
	std::string displayEdges();
	std::string displayMatrix();
	std::string displayUnvisited();

	std::string breadthFirst(char name);
	std::string recBreadthFirst(Node* tempNode);
	std::string depthFirst(char name);
	std::string recDepthFirst(Node* tempNode);

private:
	static const int SIZE = 20;
	int numNodes;
	Node* nodeList[SIZE];
	int edgeMatrix[SIZE][SIZE];

	int findNode(char name);
	void resetVisited();
};

#endif // GRAPH_H

