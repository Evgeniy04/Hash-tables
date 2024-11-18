#pragma once
#include "Entry.h"

/// <summary>
/// ���� ������.
/// </summary>
struct Node
{
private:
	Entry* _data;
	Node* _next;

public:
	/// <summary>
	/// �����������.
	/// </summary>
	/// <param name="data">������ (����-��������).</param>
	/// <param name="next">��������� ����.</param>
	Node(Entry* data, Node* next);
	/// <summary>
	/// ����������.
	/// </summary>
	~Node();

	/// <summary>
	/// �������� ������ (����-��������).
	/// </summary>
	/// <returns>������.</returns>
	Entry* GetData() const { return _data; }

	/// <summary>
	/// �������� ������ (����-��������).
	/// </summary>
	/// <param name="newData">������.</param>
	void SetData(Entry* newData) { _data = newData; }

	/// <summary>
	/// �������� ��������� ����.
	/// </summary>
	/// <returns>����.</returns>
	Node* GetNext() const { return _next; }
	
	/// <summary>
	/// �������� ��������� ����.
	/// </summary>
	/// <param name="newNext">����.</param>
	void SetNext(Node* newNext) { _next = newNext; }
};

