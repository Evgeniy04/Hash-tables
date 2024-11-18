#pragma once
#include "Entry.h"

/// <summary>
/// Узел списка.
/// </summary>
struct Node
{
private:
	Entry* _data;
	Node* _next;

public:
	/// <summary>
	/// Конструктор.
	/// </summary>
	/// <param name="data">Запись (ключ-значение).</param>
	/// <param name="next">Следующий узел.</param>
	Node(Entry* data, Node* next);
	/// <summary>
	/// Деструктор.
	/// </summary>
	~Node();

	/// <summary>
	/// Получить запись (ключ-значение).
	/// </summary>
	/// <returns>Запись.</returns>
	Entry* GetData() const { return _data; }

	/// <summary>
	/// Изменить запись (ключ-значение).
	/// </summary>
	/// <param name="newData">Запись.</param>
	void SetData(Entry* newData) { _data = newData; }

	/// <summary>
	/// Получить следующий узел.
	/// </summary>
	/// <returns>Узел.</returns>
	Node* GetNext() const { return _next; }
	
	/// <summary>
	/// Изменить следующий узел.
	/// </summary>
	/// <param name="newNext">Узел.</param>
	void SetNext(Node* newNext) { _next = newNext; }
};

