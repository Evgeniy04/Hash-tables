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

	//Node* headNode = GetHead();
	//Node* tailNode = GetTail();
	//Node* newNode = new Node(data, nullptr);
	//AddOffsetCount(1);

	//if (!headNode)  // Если список пустой
	//{
	//	SetHead(newNode);
	//	SetTail(newNode);  // Добавить эту строку
	//}
	//else  // Если в списке есть элементы
	//{
	//	GetTail()->SetNext(newNode);
	//	SetTail(newNode);
	//}
}

void List::Remove(Node* prevNode, Node* targetNode)
{
	if (!targetNode)
	{
		return;
	}
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

	delete targetNode->GetData();
	delete targetNode;
	AddOffsetCount(-1);
}

void List::Remove(string key)
{
	Node* prevNode = nullptr;
	Node* targetNode = GetHead();

	while (targetNode != nullptr) // Изменение здесь
	{
		if (targetNode->GetData()->Key == key)
		{
			// Используем существующий метод Remove для удаления узла
			Remove(prevNode, targetNode);
			return;
		}
		prevNode = targetNode;
		targetNode = targetNode->GetNext();
	}
}