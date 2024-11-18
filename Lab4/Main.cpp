#include <iostream>
#include <sstream>
#include "HashMap.h"
#include "List.h"
#include "Entry.h"

using namespace std;

/// <summary>
/// Валидация ввода числа.
/// </summary>
/// <returns>Число, введённое пользователем.</returns>
static int CinInt()
{
	string input;
	int number;

	while (true)
	{
		cin >> input;

		stringstream ss(input);
		if (ss >> number && ss.eof())
		{
			break;
		}

		cout << "Error!" << endl;
	}
	return number;
}

/// <summary>
/// Ввод строки.
/// </summary>
/// <returns>Строка, введённое пользователем.</returns>
static string CinString()
{
	string input;
	cin >> input;
	return input;
}

/// <summary>
/// Вывести все элементы списка.
/// </summary>
/// <param name="list">Список.</param>
void PrintList(const List* list)
{
	string* values = list->GetValues();
	for (int i = 0; i < list->GetCount(); ++i)
	{
		cout << values[i];
	}
	cout << endl;
	delete[] values;
}

/// <summary>
/// Вывести все элементы словаря.
/// </summary>
/// <param name="hashMap">Словарь.</param>
void PrintHashMap(HashMap* hashMap)
{
	List** buckets = hashMap->GetBuckets();
	int capacity = hashMap->GetCapacity();
	for (int i = 0; i < capacity; i++)
	{
		if (buckets[i])
		{
			PrintList(buckets[i]);
			continue;
		}
		cout << "NULL" << endl;
	}
}

int main()
{
	HashMap* hashMap = new HashMap();

	bool flag = true;
	while (flag)
	{
		cout << "Current HashMap: " << endl;
		PrintHashMap(hashMap);
		cout << "Actions:" << endl;
		cout << "[1] Insert" << endl;
		cout << "[2] Remove" << endl;
		cout << "[3] Find" << endl;
		cout << "[0] Exit the program" << endl << endl;

		int cmd = CinInt();
		system("cls");
		switch (cmd)
		{
			case 1:
			{
				cout << "[1] Enter the key: ";
				string key = CinString();
				cout << "[1] Enter the value: ";
				string value = CinString();
				hashMap->Insert(new Entry(key, value));
				break;
			}
			case 2:
			{
				cout << "[2] Enter the key: ";
				string key = CinString();
				hashMap->Remove(key);
				break;
			}
			case 3:
			{
				cout << "[3] Enter the key: ";
				string key = CinString();
				try
				{
					cout << "Found value: " << hashMap->Find(key) << endl;
				}
				catch (exception& e)
				{
					cout << e.what() << '\n';
				}
				break;
			}
			case 0:
			{
				flag = false;
				break;
			}
			default:
			{
				cout << "Invalid command!" << endl;
			}
		}
	}

	delete hashMap;
}