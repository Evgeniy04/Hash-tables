#pragma once
#include "Node.h"
#include "Entry.h"

struct List
{
private:
	Node* _head = nullptr;
	Node* _tail;
	int _count;

	Node* GetHead() const { return _head; }
	void SetHead(Node* newHead) { _head = newHead; }
	Node* GetTail() const { return _tail; }
	void SetTail(Node* newTail) { _tail = newTail; }
	void SetCount(int newCount) { _count = newCount; }
	void AddOffsetCount(int offset) { _count += offset; }
public:
	List();
	~List();

	int GetCount() const { return _count; }
	void Add(Entry* data);
	void Remove(char* key);
	Node** LinearSearch(char* element);
};
