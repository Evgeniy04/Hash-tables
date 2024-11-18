#pragma once
#include "List.h"

/// <summary>
/// СД Словарь.
/// </summary>
struct HashMap
{
private:
	int _capacity;
	int _elementCount;
	List** _buckets;

	/// <summary>
	/// Изменить количество бакетов. 
	/// </summary>
	/// <param name="newCapacity">Новое количество бакетов.</param>
	void SetCapacity(int newCapacity);

	/// <summary>
	/// Получить количество записей.
	/// </summary>
	/// <returns>Количество записей.</returns>
	int GetElementCount() const { return _elementCount; };

	/// <summary>
	/// Изменить количество записей.
	/// </summary>
	/// <param name="newElementCount">Новое количество записей.</param>
	void SetElementCount(int newElementCount);

	/// <summary>
	/// Заменить массив бакетов.
	/// </summary>
	/// <param name="newBuckets">Новый массив бакетов.</param>
	void SetBuckets(List** newBuckets) { _buckets = newBuckets; };

public:

	/// <summary>
	/// Конструктор.
	/// </summary>
	HashMap();

	/// <summary>
	/// Деструктор.
	/// </summary>
	~HashMap();

	/// <summary>
	/// Хеш-функция.
	/// </summary>
	/// <param name="key">Строка, которая должна быть захеширована.</param>
	/// <param name="hash_size">Размер хеша в битах.</param>
	/// <returns>Значение от 0 до 2^hash_size.</returns>
	uint64_t Hash(const string& key, int hash_size);

	/// <summary>
	/// Получить количество бакетов.
	/// </summary>
	/// <returns>Количество бакетов.</returns>
	int GetCapacity() const { return _capacity; };

	/// <summary>
	/// Получить массив бакетов.
	/// </summary>
	/// <returns>Массив бакетов.</returns>
	List** GetBuckets() const { return _buckets; };

	/// <summary>
	/// Вставить запись.
	/// </summary>
	/// <param name="entry">Запись.</param>
	void Insert(Entry* entry);

	/// <summary>
	/// Удалить запись.
	/// </summary>
	/// <param name="key">Ключ записи.</param>
	void Remove(string key);

	/// <summary>
	/// Найти запись.
	/// </summary>
	/// <param name="key">Ключ записи.</param>
	/// <returns>Значение записи.</returns>
	string Find(string key);

	/// <summary>
	/// Функция перехеширования.
	/// </summary>
	void Rehash();
};

