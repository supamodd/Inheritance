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
	//Абстрактный класс
};
class Lion :public Cat
{
	//Конкретный класс
public:
	void Sound()override
	{
		cout << "Ррррррр" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Animal animal;	//E0322,C2259
	//Cat cat;
	Lion lion;
}