#include <iostream>
using namespace std;

class Student {
public:
	float GPA;
};

void SWAP(Student a, Student b[2])
{
	float* temp = &b[0].GPA;
	cout << temp;
	b[0].GPA = a.GPA;
	a.GPA = temp;
}

int main()
{
	Student x = { 3.5 }, y[2] = { 3.7,3.3 };
	SWAP(x, y);

	cout << x.GPA << endl;
	cout << y[0].GPA << endl;

	return 0;
}

