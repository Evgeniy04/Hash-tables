#pragma once
#include "Node.h"
#include "Entry.h"

/// <summary>
/// СД односвязный список.
/// </summary>
struct List
{
private:
	Node* _head = nullptr;
	Node* _tail;
	int _count;

	/// <summary>
	/// Изменить головной узел списка.
	/// </summary>
	/// <param name="newHead">Новый узел.</param>
	void SetHead(Node* newHead) { _head = newHead; }

	/// <summary>
	/// Получить хвостовой узел списка.
	/// </summary>
	/// <returns>Узел.</returns>
	Node* GetTail() const { return _tail; }

	/// <summary>
	/// Изменить хвостовой узел списка.
	/// </summary>
	/// <param name="newTail">Новый узел.</param>
	void SetTail(Node* newTail) { _tail = newTail; }

	/// <summary>
	/// Изменить количество элементов.
	/// </summary>
	/// <param name="newCount">Новое количество элементов.</param>
	void SetCount(int newCount) { _count = newCount; }

	/// <summary>
	/// Изменить значение количеству элементов на какое-то значение.
	/// </summary>
	/// <param name="offset">Значение изменения.</param>
	void AddOffsetCount(int offset) { _count += offset; }

public:
	/// <summary>
	/// Конструктор.
	/// </summary>
	List();

	/// <summary>
	/// Дестркутор.
	/// </summary>
	~List();

	/// <summary>
	/// Получить головной узел списка.
	/// </summary>
	/// <returns>Узел.</returns>
	Node* GetHead() const { return _head; }

	/// <summary>
	/// Получить количество элементов.
	/// </summary>
	/// <returns>Количество элементов.</returns>
	int GetCount() const { return _count; }

	/// <summary>
	/// Добавить элемент.
	/// </summary>
	/// <param name="data">Запись (ключ-значение).</param>
	void Add(Entry* data);

	/// <summary>
	/// Удалить элемент.
	/// </summary>
	/// <param name="key">Ключ записи.</param>
	void Remove(string key);

	/// <summary>
	/// Удалить элемент по узлу.
	/// </summary>
	/// <param name="prevNode">Предыдущий узел.</param>
	/// <param name="targetNode">Узел, который необходимо удалить.</param>
	void Remove(Node* prevNode, Node* targetNode);
};

