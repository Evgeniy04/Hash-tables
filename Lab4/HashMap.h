#pragma once
#include "List.h"

struct HashMap
{
private:
	int _capacity;
	int _elementCount;
	List* _buckets;
	int GetCapacity() const { return _capacity; };
	void SetCapacity(int newCapacity);
	int GetElementCount() const { return _elementCount; };
	void SetElementCount(int newElementCount);
	List* GetBuckets() const { return _buckets; };
	void SetBuckets(List* newBuckets) { _buckets = newBuckets; };

	uint64_t Hash(const unsigned char* x, size_t len, size_t hash_size);
public:
	HashMap(int capacity);
	~HashMap();

	void Insert(Entry* entry);
	char* Find(char* key);
	void Remove(char* key);
};

