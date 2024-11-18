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
	Node* currentNode = list->GetHead();
	while (currentNode != nullptr)
	{
		if (currentNode)
		{
			cout << currentNode->GetData()->Key << ": " << currentNode->GetData()->Value << "; ";
		}
		currentNode = currentNode->GetNext();
	}
	cout << endl;
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

void TestForHash(HashMap* hashMap)
{
	// Граничные значения для hash_size
	cout << hashMap->Hash("abc", 0) << endl;  // Ожидаемый результат: 0, так как hash_size = 0
	cout << hashMap->Hash("abc", 64) << endl; // Ожидаемый результат: корректный 64-битный хеш
	cout << hashMap->Hash("abc", 1) << endl;  // Ожидаемый результат: хеш из 1 бита
	cout << hashMap->Hash("abc", 63) << endl; // Ожидаемый результат: хеш из 63 бит

	// Неверные значения для hash_size
	try {
		cout << hashMap->Hash("abc", -1) << endl;
	}
	catch (const invalid_argument& e) {
		cout << e.what() << '\n';
	}
	try {
		cout << hashMap->Hash("abc", 65) << endl;
	}
	catch (const invalid_argument& e) {
		cout << e.what() << '\n';
	}

	// Пустая строка
	try {
		cout << hashMap->Hash("", 32) << endl;
	}
	catch (const invalid_argument& e) {
		cout << e.what() << '\n';
	}

	// Разные длины ключа
	cout << hashMap->Hash("a", 16) << endl;     // Короткий ключ
	cout << hashMap->Hash("abc", 16) << endl;   // Средний ключ
	cout << hashMap->Hash("abcdefghijklmnopqrstuvwxyz", 16) << endl; // Длинный ключ

	// Различные символы
	cout << hashMap->Hash("12345", 32) << endl;             // Цифры
	cout << hashMap->Hash("ABCDE", 32) << endl;             // Верхний регистр
	cout << hashMap->Hash("abcde", 32) << endl;             // Нижний регистр
	cout << hashMap->Hash("a b c d e", 32) << endl;         // С пробелами
	cout << hashMap->Hash("!@#$%^&*()", 32) << endl;        // Нестандартные символы

	// Сочетания границ
	try {
		cout << hashMap->Hash("", 0) << endl;               // Пустой ключ, минимальный hash_size
	}
	catch (const invalid_argument& e) {
		cout << e.what() << '\n';
	}
	cout << hashMap->Hash("abcdefghijklmnopqrstuvwxyz", 64) << endl; // Максимальный ключ, максимальный hash_size
}

void ASSERT(bool value)
{
	if (!value)
	{
		throw new exception("TestForHashMap.");
	}
}

void TestForHashMap(HashMap& hashMap)
{
	// Добавление уникальных записей
	hashMap.Insert(new Entry("key1", "value1"));
	hashMap.Insert(new Entry("key2", "value2"));

	ASSERT(hashMap.Find("key1") == "value1");
	ASSERT(hashMap.Find("key2") == "value2");

	// Обновление записи с одинаковым ключом
	hashMap.Insert(new Entry("key", "value1"));
	hashMap.Insert(new Entry("key", "value2"));

	ASSERT(hashMap.Find("key") == "value2");

	// Длинные ключ и значение
	std::string longKey(1000, 'a');
	std::string longValue(1000, 'b');
	hashMap.Insert(new Entry(longKey, longValue));
	ASSERT(hashMap.Find(longKey) == longValue);

	// Большое число записей
	for (int i = 0; i < 10000; ++i) {
		hashMap.Insert(new Entry("key" + std::to_string(i), "value" + std::to_string(i)));
	}
	for (int i = 0; i < 10000; ++i) {
		ASSERT(hashMap.Find("key" + std::to_string(i)) == "value" + std::to_string(i));
	}


	// Обработка коллизий
	hashMap.Insert(new Entry("key1", "value1"));
	hashMap.Insert(new Entry("key2", "value2"));

	ASSERT(hashMap.Find("key1") == "value1");
	ASSERT(hashMap.Find("key2") == "value2");


	// Исключение при отсутствии ключа
	try {
		hashMap.Find("nonexistent_key");
	}
	catch (const std::invalid_argument& e) {
		ASSERT(true);
	}
	PrintHashMap(&hashMap);
}

int main()
{
	HashMap* hashMap = new HashMap();
	List* list = new List();

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
}