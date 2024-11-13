#pragma once
#include "Entry.h"

struct Node
{
private:
	Entry* _data;
	Node* _next;
public:
	Node(Entry* data, Node* next);

	Entry* GetData() const { return _data; }
	void SetData(Entry* newData) { _data = newData; }
	Node* GetNext() const { return _next; }
	void SetNext(Node* newNext) { _next = newNext; }
};

