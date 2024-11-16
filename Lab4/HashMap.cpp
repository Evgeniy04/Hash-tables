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
	delete[] GetBuckets();
}

/// <summary>
/// ������ Capacity.
/// </summary>
/// <param name="newCapacity">����� �� ������������� �����, ������� 2.</param>
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
/// ���-�������.
/// </summary>
/// <param name="key">��������, ������� ���������� ������������.</param>
/// <param name="hash_size">����� ��������������� ���-�������� � �����.</param>
/// <returns>������ �������, ���� ��������� �������.</returns>
uint64_t HashMap::Hash(const string& key, size_t hash_size)
{
    if (hash_size < 0 && hash_size > 64)
    {
        throw new invalid_argument("hash_size cannot be negative and more than 64.");
    }

    // ���������� ��� �������� �������������� ���������� ���������� ���� ��� ������� ������� � ������ x
    unsigned char h;
    // ������ �� 8 ������ ��� �������� ������������� ������������� �������� ���� ��� ������� �� 8 ������.
    // ��� ����� ����� ����� �������������� � 64 - ������ ��������(��� uint64_t)
    unsigned char hh[8];
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
            // ���������� �������� ���������� ������������ ��� ��� ���������� ���-��������
            h = T[h ^ key[i]];
        }
        hh[j] = h;
    }

    uint64_t result = 0;
    size_t bytes_to_use = hash_size / 8;  // ���������� ������, ������� ����� �������������� ��� ����

    // ��� ���� �������� ��� 8 ���, �� ����� ������������ �����
    if (hash_size < 8) {
        // �������� ������ ������ ��������� ���
        result = hh[0] & ((1 << hash_size) - 1);  // ��������� ������ ������ ������ ����
    }
    else {
        // ���� ��� 8 ��� ��� ������, ���������� ������ 8 ���
        for (size_t k = 0; k < bytes_to_use; ++k) {
            // ���������� ��������� �������� ������������ � ����������� ���
            result = (result << 8) | hh[k];
        }
    }

    return result;
}

void HashMap::Rehash()
{
    int oldCapacity = GetCapacity();
    List** oldBuckets = GetBuckets();
    int newCapacity = oldCapacity * 2;
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

    Node** prevFoundNodes = buckets[insertIndex]->LinearSearch(entry->Key);
    Node* foundNode = prevFoundNodes[1];

    if (foundNode)
    {
        if (foundNode->GetData()->Value == entry->Value)
        {
            delete entry;
        }
        else
        {
            buckets[insertIndex]->Remove(prevFoundNodes);
            buckets[insertIndex]->Add(entry);
        }
        delete[] prevFoundNodes;
        return;
    }
    buckets[insertIndex]->Add(entry);

    SetElementCount(GetElementCount() + 1);
    if (GetElementCount() / capacity + 0.15 > 1.0)
    {
        Rehash();
    }
}