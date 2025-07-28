#include<iostream>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");

#ifdef WRITE_TO_FILE
	//1) —оздаем поток:
	std::ofstream fout;

	//2) ќткрываем поток:
	fout.open("File01.txt", std::fstream::app);	//app - append (добавить в конец)

	//3) ѕишем в поток:
	fout << "Hello Files!" << endl;;

	//4) ѕотоки как холодильник, если он был открыт, его об€зательно нужно закрыть!!!!!
	fout.close();

	system("notepad File.txt");
#endif // WRITE_TO_FILE

	//1) —оздаем и открываем поток:
	std::ifstream fin("File01.txt");

	//2) ѕровер€ем открылс€ ли поток:
	if (fin.is_open())
	{
		while (!fin.eof())	//eof() - End Of File;
		{
			const int SIZE = 256;
			char sz_buffer[SIZE] = {};
			//fin >> sz_buffer;
			fin.getline(sz_buffer, SIZE);
			cout << sz_buffer << endl;
		}
		fin.close();	//поток есть смысл закрывать, только если он был открыт
	}
	else
	{
		std::cerr << "Error: file not foud" << endl;
	}
}