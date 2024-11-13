#pragma once
struct Entry
{
	Entry(char* key, char* value);
	~Entry();

	char* Key;
	char* Value;
};

