#pragma once
#include "List.h"

/// <summary>
/// �� �������.
/// </summary>
struct HashMap
{
private:
	int _capacity;
	int _elementCount;
	List** _buckets;

	/// <summary>
	/// ���-�������.
	/// </summary>
	/// <param name="key">��������, ������� ���������� ������������.</param>
	/// <param name="hash_size">����� ��������������� ���-�������� � �����.</param>
	/// <returns>�������� �� 0 �� 2^hash_size.</returns>
	uint64_t Hash(const string& key, int hash_size);

	/// <summary>
	/// ������ Capacity.
	/// </summary>
	/// <param name="newCapacity">����� �� ������������� �����, ������� 2.</param>
	void SetCapacity(int newCapacity);

	/// <summary>
	/// �������� ���������� �������.
	/// </summary>
	/// <returns>���������� �������.</returns>
	int GetElementCount() const { return _elementCount; };

	/// <summary>
	/// �������� ���������� �������.
	/// </summary>
	/// <param name="newElementCount">����� ���������� �������.</param>
	void SetElementCount(int newElementCount);

	/// <summary>
	/// �������� ������ �������.
	/// </summary>
	/// <param name="newBuckets">����� ������ �������.</param>
	void SetBuckets(List** newBuckets) { _buckets = newBuckets; };

	/// <summary>
	/// ������� ���������������.
	/// </summary>
	void Rehash();

public:

	/// <summary>
	/// �����������.
	/// </summary>
	HashMap();

	/// <summary>
	/// ����������.
	/// </summary>
	~HashMap();

	/// <summary>
	/// �������� ���������� �������.
	/// </summary>
	/// <returns>���������� �������.</returns>
	int GetCapacity() const { return _capacity; };

	/// <summary>
	/// �������� ������ �������.
	/// </summary>
	/// <returns>������ �������.</returns>
	List** GetBuckets() const { return _buckets; };

	/// <summary>
	/// �������� ������.
	/// </summary>
	/// <param name="entry">������.</param>
	void Insert(string key, string value);

	/// <summary>
	/// ������� ������.
	/// </summary>
	/// <param name="key">���� ������.</param>
	void Remove(string key);

	/// <summary>
	/// ����� ������.
	/// </summary>
	/// <param name="key">���� ������.</param>
	/// <returns>�������� ������.</returns>
	string Find(string key);
};

