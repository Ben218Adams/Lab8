
#include "Graph.h"

#include <stdexcept>
#include <sstream>
#include <ostream>
#include <iomanip>
#include <queue>


// add a new node to the graph
// only failure is if graph arrays are full
void Graph::addNode(char name)
{
	// alternately, double the size of everything and start over
	if (numNodes >= SIZE)
		throw std::overflow_error("Graph size exceeded!!");

	// create a node with this name
	// initialize it with no edges and not yet visited
	Node * temp = new Node;
	temp->name = name;
	temp->visited = false;
	temp->connects = nullptr;

	// add to the list of nodes in graph
	nodeList[numNodes++] = temp;
}


// add a new edge to the graph
// return false and do nothing if either end is invalid
// otherwise add to both nodes edge lists and to the matrix
bool Graph::addEdge(char starts, char ends)
{
	if (starts == ends)
		return false;

	int startIndex = findNode(starts);
	int endIndex = findNode(ends);

	if (startIndex == -1 or endIndex == -1)
		return false;

	// set both links in edgeMatrix
	edgeMatrix[startIndex][endIndex] = 1;
	edgeMatrix[endIndex][startIndex] = 1;

	// create two new edges (one for each direction)
	// and add one to each nodes list of edges
	Edge * startEnd = new Edge;
	startEnd->endIndex = endIndex;
	startEnd->next = nullptr;
	startEnd->next = nodeList[startIndex]->connects;
	nodeList[startIndex]->connects = startEnd;

	Edge * endStart = new Edge;
	endStart->endIndex = startIndex;
	endStart->next = nullptr;
	endStart->next = nodeList[endIndex]->connects;
	nodeList[endIndex]->connects = endStart;

	return true;
}


// linear search for a node with this name
// return -1 if not found
// otherwise return its index in the nodeList
int Graph::findNode(char name)
{
	for (int i = 0; i < numNodes; i++)
		if (nodeList[i]->name == name)
			return i;
	return -1;
}


// listing of nodes in the order
// they were added to the graph
std::string Graph::listNodes()
{
	std::string theList = "The Nodes are: ";
	for (int i = 0; i < numNodes; i++)
	{
		theList += nodeList[i]->name;
		theList += " ";
	}
	return theList;
}


// for each node in graph,
// display its edges, using the edgelist
std::string Graph::displayEdges()
{
	std::stringstream ss;
	ss << "The EdgeList is: (Node: its edges)\n";

	for (int i = 0; i < numNodes; i++)
	{
		// add the node name to the display
		ss << nodeList[i]->name;
		ss << ": ";

		// walk down its list of edges and add them also
		Edge* ptr = nodeList[i]->connects;
		while (ptr != nullptr)
		{
			ss << nodeList[ptr->endIndex]->name;
			ss << " ";
			ptr = ptr->next;
		}
		// end this line of output
		ss << std::endl;
	}
	return ss.str();
}


// display the adjacency matrix
// as 0 for no connection and 1 for connection
std::string Graph::displayMatrix()
{
	std::stringstream ss;
	ss << "The edgeMatrix is: \n";

	// output header line of destinations
	ss << std::setw(2) << " ";
	for (int i = 0; i < numNodes; i++)
		ss << std::setw(4) << nodeList[i]->name;
	ss << std::endl;

	// now output the array
	for (int i = 0; i < numNodes; i++)
	{
		// add the starting node
		ss << std::setw(2) << nodeList[i]->name;

		// now add its connections
		for (int j = 0; j < numNodes; j++)
			ss << std::setw(4) << edgeMatrix[i][j];

		// end the row
		ss << std::endl;
	}
	return ss.str();
}

std::string Graph::displayUnvisited()
{
	std::string buff = "";
	for (int i = 0; i < SIZE/2; i++)
	{
		if (nodeList[i]->visited == false)
		{
			buff += nodeList[i]->name;		// this only returns first unvisited char. Lazy.
		}
	}
	return buff;
}

// depth first traversal
// starts at a given node
// outputs a list of nodes visited
// and a list of any unreached nodes
std::string Graph::depthFirst(char name)
{
	std::string buffer = "Depth first traversal starting at ";
	buffer += name;
	buffer += "\n";
	return buffer;

}

//Rec func calls can act as stack

// breadth first traversal
// starts at a given node
// outputs a list of nodes visited
// and a list of any unreached nodes
std::string Graph::breadthFirst(char name)
{
	std::string buffer = "Breadth first traversal starting at ";
	buffer += name;
	buffer += "\n";
	buffer += recBreadthFirst(nodeList[findNode(name)]);
	buffer += "\n";
	buffer += "Unvisited nodes: " + displayUnvisited();
	resetVisited();
	return buffer;
}

std::string Graph::recBreadthFirst(Node* tempNode)	// recursive func calls 
{
	std::stringstream recBuff;

	if(tempNode != nullptr)
	{
		std::queue<Node*> myqueue;

		tempNode->visited = true;
		int nodeKey = findNode(tempNode->name);		// nodeKey
		recBuff << tempNode->name << " ";
		for (int i = 0; i < SIZE; i++)
		{
			if ((edgeMatrix[nodeKey][i] == 1) && (nodeList[i]->visited == false))
				myqueue.push(nodeList[i]);
		}
		while (!myqueue.empty())
		{
			Node* top = myqueue.front();
			myqueue.pop();
			recBuff << recBreadthFirst(top);
		}
	}
	else 
		recBuff << "";
	return recBuff.str();
}

// helper function to reset all nodes to not visited
void Graph::resetVisited()
{
	for (int i = 0; i < numNodes; i++)
		nodeList[i]->visited = false;
}

