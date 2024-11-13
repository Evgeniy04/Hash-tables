#include <iostream>
#include "HashMap.h"

using namespace std;

int main()
{
	HashMap* hashMap = new HashMap(4);
	uint64_t result = hashMap->Hash("A", 8);
	cout << result << endl;
	result = hashMap->Hash("B", 8);
	cout << result << endl;
	result = hashMap->Hash("C", 8);
	cout << result << endl;
	result = hashMap->Hash("A", 8);
	cout << result << endl;
}