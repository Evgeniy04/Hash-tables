#pragma once
#include "string"

using namespace std;

/// <summary>
/// ������ (����-��������).
/// </summary>
struct Entry
{
	/// <summary>
	/// �����������.
	/// </summary>
	/// <param name="key">����.</param>
	/// <param name="value">��������.</param>
	Entry(string key, string value);

	string Key;
	string Value;
};

