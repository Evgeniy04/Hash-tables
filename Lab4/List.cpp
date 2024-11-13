#include <string>
#include <stdexcept>
#include "List.h"
#include "Node.h"
#include "Entry.h"

using namespace std;

List::List()
{
	SetCount(0);
	SetHead(nullptr);
	SetTail(nullptr);
}

List::~List()
{
	Node* currentNode = GetHead();
	while (currentNode)
	{
		Node* temp = currentNode->GetNext();
		delete currentNode;
		currentNode = temp;
	}
}

void List::Add(Entry* data)
{
	Node** prevFoundNodes = LinearSearch(data->Key);
	Node* foundNode = prevFoundNodes[1];
	delete[] prevFoundNodes;

	if (foundNode && foundNode->GetData()->Value == data->Value)
	{
		delete data;
		return;
	}

	Node* headNode = GetHead();
	Node* tailNode = GetTail();

	Node* newNode = new Node(data, nullptr);
	AddOffsetCount(1);

	if (!headNode)
	{
		SetHead(newNode);
	}
	else if (!tailNode)
	{
		headNode->SetNext(newNode);
		SetTail(newNode);
	}
	else
	{
		tailNode->SetNext(newNode);
		SetTail(newNode);
	}
}

void List::Remove(char* key)
{
	Node** prevTargetNodes = LinearSearch(key);
	Node* prevNode = prevTargetNodes[0];
	Node* targetNode = prevTargetNodes[1];
	Node* nextNode = targetNode->GetNext();

	if (!prevNode && !nextNode)
	{
		SetHead(nullptr);
		SetTail(nullptr);
	}
	else if (!prevNode)
	{
		SetHead(nextNode);
		if (nextNode == GetTail())
		{
			SetTail(nullptr);
		}
	}
	else if (!nextNode)
	{
		prevNode->SetNext(nullptr);
		if (targetNode != GetHead())
		{
			SetTail(prevNode);
		}
	}
	else
	{
		prevNode->SetNext(nextNode);
	}

	delete targetNode;
	delete[] prevTargetNodes;
	AddOffsetCount(-1);
}

Node** List::LinearSearch(char* key)
{
	Node* prevNode = nullptr;
	Node* currentNode = GetHead();
	Node** nodes = new Node*[2] { prevNode, currentNode };
	for (int i = 0; i < GetCount(); i++)
	{
		if (currentNode->GetData()->Key == key)
		{
			return nodes;
		}
		prevNode = currentNode;
		currentNode = currentNode->GetNext();
	}

	delete[] nodes;
	throw runtime_error("Key not found.");
}