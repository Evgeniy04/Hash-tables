#pragma once
#include "string"

using namespace std;

struct Entry
{
	Entry(string key, string value);

	string Key;
	string Value;
};

