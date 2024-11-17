#pragma once
#include "List.h"

struct HashMap
{
private:
	int _capacity;
	int _elementCount;
	List** _buckets;
	void SetCapacity(int newCapacity);
	int GetElementCount() const { return _elementCount; };
	void SetElementCount(int newElementCount);
	void SetBuckets(List** newBuckets) { _buckets = newBuckets; };
public:
	HashMap();
	~HashMap();

	uint64_t Hash(const string& key, int hash_size);
	int GetCapacity() const { return _capacity; };
	List** GetBuckets() const { return _buckets; };
	void Insert(Entry* entry);
	void Remove(string key);
	string Find(string key);
	void Rehash();
};

