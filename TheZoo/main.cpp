#include<iostream>
using namespace std;

class Animal
{
	//
public:
	virtual void Sound() = 0;
};
class Cat :public Animal
{
	//����������� �����
};
class Lion :public Cat
{
	//���������� �����
public:
	void Sound()override
	{
		cout << "�������" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Animal animal;	//E0322,C2259
	//Cat cat;
	Lion lion;
}