#pragma once
#include "string"

using namespace std;

/// <summary>
/// Запись (ключ-значение).
/// </summary>
struct Entry
{
	/// <summary>
	/// Конструктор.
	/// </summary>
	/// <param name="key">Ключ.</param>
	/// <param name="value">Значение.</param>
	Entry(string key, string value);

	string Key;
	string Value;
};

