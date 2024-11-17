#include <stdexcept>
#include <cmath>
#include <algorithm>
#include "HashMap.h"

using namespace std;

HashMap::HashMap()
{
	SetCapacity(4);
    SetElementCount(0);
    SetBuckets(new List*[GetCapacity()]);
    fill(GetBuckets(), GetBuckets() + GetCapacity(), nullptr);
}

HashMap::~HashMap()
{
    for (int i = 0; i < GetCapacity(); i++)
    {
        if (!GetBuckets()[i]) continue;
        delete GetBuckets()[i];
    }
	delete[] GetBuckets();
}

/// <summary>
/// Сеттер Capacity.
/// </summary>
/// <param name="newCapacity">Целое не отрицательное число, степень 2.</param>
void HashMap::SetCapacity(int newCapacity)
{
	if (newCapacity < 0 && floor(log2(newCapacity)) != log2(newCapacity))
	{
		throw invalid_argument("Capacity cannot be negative.");
	}
	_capacity = newCapacity;
}

void HashMap::SetElementCount(int newElementCount)
{
	if (newElementCount < 0 && newElementCount > GetCapacity() + 1)
	{
		throw invalid_argument("Capacity cannot be negative.");
	}
	_elementCount = newElementCount;
}

/// <summary>
/// Хеш-функция.
/// </summary>
/// <param name="key">Значение, которое необходимо захешировать.</param>
/// <param name="hash_size">Длину результирующего хеш-значения в битах.</param>
/// <returns>Индекс массива, куда поместить элемент.</returns>
uint64_t HashMap::Hash(const string& key, int hash_size)
{
    if (hash_size < 0 || hash_size > 64)
    {
        throw invalid_argument("hash_size cannot be negative and more than 64.");
    }
    if (key.empty()) {
        throw invalid_argument("key cannot be empty.");
    }

    // Переменная для хранения промежуточного результата вычисления хеша для каждого символа в строке x
    unsigned char h;
    // Массив из 8 байтов для хранения окончательных промежуточных значений хеша для каждого из 8 циклов.
    // Эти байты будут позже скомбинированы в 64 - битное значение(тип uint64_t)
    unsigned char hh[8]{};
    // 0-255 shuffled in any (random) order suffices
    static const unsigned char T[256] = {
         98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219, //  1
         61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115, //  2
         90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10, //  3
        237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121, //  4
        123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55, //  5
         59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222, //  6
        197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186, //  7
         39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99, //  8
        154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254, //  9
        133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139, // 10
        189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44, // 11
        183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12, // 12
        221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166, // 13
          3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117, // 14
        238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110, // 15
         43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239  // 16
    };

    for (int j = 0; j < 8; ++j) {
        h = T[(key[0] + j) % 256];
        for (int i = 1; i < key.size(); ++i) {
            // Используем оператор побитового исключающего ИЛИ для обновления хеш-значения
            h = T[h ^ key[i]];
        }
        hh[j] = h;
    }

    uint64_t result = 0;
    int bytes_to_use = hash_size / 8;  // Количество байтов, которые будут использоваться для хеша
    int residue = hash_size % 8;

    for (int k = 0; k < bytes_to_use; ++k) {
        result = (result << 8) | hh[k];
    }

    if (residue > 0) {
        result = (result << residue) | (hh[bytes_to_use] & ((1 << residue) - 1));
    }

    return result;
}

void HashMap::Rehash()
{
    int oldCapacity = GetCapacity();
    List** oldBuckets = GetBuckets();
    int newCapacity;
    if (GetElementCount() / oldCapacity > 0.9)
    {
        newCapacity = oldCapacity * 2;
    }
    else if (GetElementCount() / oldCapacity < 0.45)
    {
        newCapacity = oldCapacity / 2;
    }
    else
    {
        return;
    }
    SetCapacity(newCapacity);

    List** newBuckets = new List * [newCapacity];
    fill(newBuckets, newBuckets + newCapacity, nullptr);

    for (int i = 0; i < oldCapacity; i++)
    {
        if (!oldBuckets[i]) continue;
        Node* currentNode = oldBuckets[i]->GetHead();
        while (currentNode != nullptr)
        {
            Entry* entry = currentNode->GetData();
            size_t hash_size = (size_t)log2(newCapacity);
            uint64_t newInsertIndex = Hash(entry->Key, hash_size);

            if (!newBuckets[newInsertIndex])
            {
                newBuckets[newInsertIndex] = new List();
            }
            newBuckets[newInsertIndex]->Add(entry);

            currentNode = currentNode->GetNext();
        }
        delete oldBuckets[i];
    }
    delete[] oldBuckets;
    SetBuckets(newBuckets);
}

void HashMap::Insert(Entry* entry)
{
    int capacity = GetCapacity();
    size_t hash_size = (size_t)log2(capacity);
    uint64_t insertIndex = Hash(entry->Key, hash_size);
    List** buckets = GetBuckets();

    if (!buckets[insertIndex])
    {
        buckets[insertIndex] = new List();
    }

    bool isFinded = false;
    Node* prevNode = nullptr;
    Node* foundNode = buckets[insertIndex]->GetHead();
    for (int i = 0; i < buckets[insertIndex]->GetCount(); i++)
    {
        if (foundNode->GetData()->Key == entry->Key)
        {
            isFinded = true;
            break;
        }
        prevNode = foundNode;
        foundNode = foundNode->GetNext();
    }

    if (isFinded)
    {
        if (foundNode->GetData()->Value == entry->Value)
        {
            delete entry;
        }
        else
        {
            buckets[insertIndex]->Remove(prevNode, foundNode);
            buckets[insertIndex]->Add(entry);
        }
        return;
    }
    buckets[insertIndex]->Add(entry);

    SetElementCount(GetElementCount() + 1);
    if (GetElementCount() / capacity > 0.9)
    {
        Rehash();
    }
}


void HashMap::Remove(string key)
{
    int capacity = GetCapacity();
    size_t hash_size = (size_t)log2(capacity);
    uint64_t targetIndex = Hash(key, hash_size);
    if (!GetBuckets()[targetIndex]) return;
    GetBuckets()[targetIndex]->Remove(key);
    if (!GetBuckets()[targetIndex]->GetCount())
    {
        delete GetBuckets()[targetIndex];
        GetBuckets()[targetIndex] = nullptr;
    }
    SetElementCount(GetElementCount() - 1);
    if (GetElementCount() / capacity < 0.45 && capacity >= 8)
    {
        Rehash();
    }
}

string HashMap::Find(string key)
{
    int capacity = GetCapacity();
    size_t hash_size = (size_t)log2(capacity);
    uint64_t targetIndex = Hash(key, hash_size);
    if (!GetBuckets()[targetIndex]) throw invalid_argument("Element '" + key + "' not found.");

    bool isFinded = false;
    Node* prevNode = nullptr;
    Node* foundNode = GetBuckets()[targetIndex]->GetHead();
    for (int i = 0; i < GetBuckets()[targetIndex]->GetCount(); i++)
    {
        if (foundNode->GetData()->Key == key)
        {
            isFinded = true;
            break;
        }
        prevNode = foundNode;
        foundNode = foundNode->GetNext();
    }

    if (isFinded)
    {
        string value = foundNode->GetData()->Value;
        return value;
    }
    else
    {
        throw invalid_argument("Element '" + key + "' not found.");
    }
}