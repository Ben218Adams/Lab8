// Dis is main
// Ben Adams 
// Lab 8
//
//

//  Main.cpp
//  Example Non-directed, non-weighted graph test driver
//
//  Created by Jim Bailey on 11/25/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include <iostream>

#include "Graph.h"		// modified from og driver

using namespace std;

int main()
{
	// define graph
	Graph tree;

	// add ad list nodes
	tree.addNode('A');
	tree.addNode('C');
	tree.addNode('T');
	tree.addNode('Z');
	tree.addNode('X');
	tree.addNode('K');
	tree.addNode('Q');
	tree.addNode('J');
	tree.addNode('M');
	tree.addNode('U');

	cout << tree.listNodes() << endl << endl;

	// add and list edges
	tree.addEdge('A', 'C');
	tree.addEdge('A', 'T');
	tree.addEdge('A', 'Z');
	tree.addEdge('X', 'C');
	tree.addEdge('C', 'K');
	tree.addEdge('T', 'Q');
	tree.addEdge('K', 'Q');
	tree.addEdge('Q', 'J');
	tree.addEdge('J', 'M');
	tree.addEdge('Z', 'X');

	cout << tree.displayEdges() << endl << endl;

	cout << tree.displayMatrix() << endl << endl;

	// display breadth first min tree
	cout << tree.breadthFirst('Q') << endl;

	// display depth first min tree
	cout << tree.depthFirst('Q') << endl;

	return 0;
}



