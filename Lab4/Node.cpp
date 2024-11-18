#include "Node.h"

Node::Node(Entry* data, Node* next)
{
	SetData(data);
	SetNext(next);
}

Node::~Node()
{
	delete _data;
}