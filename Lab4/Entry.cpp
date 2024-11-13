#include "Entry.h"

Entry::Entry(char* key, char* value)
{
	Key = key;
	Value = value;
}

Entry::~Entry()
{
	delete[] Key;
	delete[] Value;
}