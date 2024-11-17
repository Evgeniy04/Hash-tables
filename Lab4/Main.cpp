#include <iostream>
#include "HashMap.h"
#include "List.h"
#include "Entry.h"

using namespace std;

/// <summary>
/// Вывести все элементы списка.
/// </summary>
/// <param name="list">Список.</param>
void PrintList(const List* list)
{
	Node* currentNode = list->GetHead();
	while (currentNode != nullptr)
	{
		if (currentNode)
		{
			cout << currentNode->GetData()->Key << ": " << currentNode->GetData()->Value << "; ";
		}
		currentNode = currentNode->GetNext();
	}
	cout << endl;
}

/// <summary>
/// Вывести все элементы словаря.
/// </summary>
/// <param name="hashMap">Словарь.</param>
void PrintHashMap(HashMap* hashMap)
{
	List** buckets = hashMap->GetBuckets();
	int capacity = hashMap->GetCapacity();
	for (int i = 0; i < capacity; i++)
	{
		if (buckets[i])
		{
			PrintList(buckets[i]);
			continue;
		}
		cout << "NULL" << endl;
	}
}

int main()
{
	HashMap* hashMap = new HashMap();
	hashMap->Insert(new Entry("c", "value"));
	hashMap->Insert(new Entry("a", "value"));
	hashMap->Insert(new Entry("c", "12"));
	hashMap->Insert(new Entry("d", "qwe"));
	hashMap->Remove("a");
	PrintHashMap(hashMap);
	cout << hashMap->Find("d");
}