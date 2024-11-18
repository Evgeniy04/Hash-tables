#pragma once
#include "Node.h"
#include "Entry.h"

/// <summary>
/// �� ����������� ������.
/// </summary>
struct List
{
private:
	Node* _head = nullptr;
	Node* _tail;
	int _count;

	/// <summary>
	/// �������� �������� ���� ������.
	/// </summary>
	/// <param name="newHead">����� ����.</param>
	void SetHead(Node* newHead) { _head = newHead; }

	/// <summary>
	/// �������� ��������� ���� ������.
	/// </summary>
	/// <returns>����.</returns>
	Node* GetTail() const { return _tail; }

	/// <summary>
	/// �������� ��������� ���� ������.
	/// </summary>
	/// <param name="newTail">����� ����.</param>
	void SetTail(Node* newTail) { _tail = newTail; }

	/// <summary>
	/// �������� ���������� ���������.
	/// </summary>
	/// <param name="newCount">����� ���������� ���������.</param>
	void SetCount(int newCount) { _count = newCount; }

	/// <summary>
	/// �������� �������� ���������� ��������� �� �����-�� ��������.
	/// </summary>
	/// <param name="offset">�������� ���������.</param>
	void AddOffsetCount(int offset) { _count += offset; }

public:
	/// <summary>
	/// �����������.
	/// </summary>
	List();

	/// <summary>
	/// ����������.
	/// </summary>
	~List();

	/// <summary>
	/// �������� �������� ���� ������.
	/// </summary>
	/// <returns>����.</returns>
	Node* GetHead() const { return _head; }

	/// <summary>
	/// �������� ���������� ���������.
	/// </summary>
	/// <returns>���������� ���������.</returns>
	int GetCount() const { return _count; }

	/// <summary>
	/// �������� �������.
	/// </summary>
	/// <param name="data">������ (����-��������).</param>
	void Add(Entry* data);

	/// <summary>
	/// ������� �������.
	/// </summary>
	/// <param name="key">���� ������.</param>
	void Remove(string key);

	/// <summary>
	/// ������� ������� �� ����.
	/// </summary>
	/// <param name="prevNode">���������� ����.</param>
	/// <param name="targetNode">����, ������� ���������� �������.</param>
	void Remove(Node* prevNode, Node* targetNode);
};

