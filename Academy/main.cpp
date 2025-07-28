#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	//static const double PI = 3.14;	//E1591
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 3;
	static int count;		//static member declaration
	std::string last_name;
	std::string first_name;
	int age;
public:
	static int get_count()
	{
		return count;
	}
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//				Конструкторы:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		count++;
		cout << "HConstrutor:\t" << this << endl;
	}
	virtual ~Human()
	{
		count--;
		cout << "HDestructor:\t" << this << endl;
	}

	//				  Методы:
	virtual std::ostream& info(std::ostream& os)const
	{
		//return os << last_name << " " << first_name << " " << age;
		os.width(LAST_NAME_WIDTH);	//ширина поля для фамилии
		os << std::left; //выравнивание влево
		os << last_name;
		os.width(FIRST_NAME_WIDTH); //ширина поля для имени
		os << first_name;
		os.width(AGE_WIDTH); //ширина поля для возраста
		os << age;
		return os;
	}

	virtual void save(std::ofstream& ofs) const 
	{
		ofs << "Human\n"; //Сохраняем тип класса
		ofs << last_name << "\n"; //Сохраняем фамилию
		ofs << first_name << "\n"; //Сохраняем имя
		ofs << age << "\n"; //Сохраняем возраст
	}

	virtual void load(std::ifstream& ifs) 
	{
		std::getline(ifs, last_name); //Загружаем фамилию
		std::getline(ifs, first_name); //Загружаем имя
		ifs >> age; //Загружаем возраст
		ifs.ignore(); // Пропускаем символ новой строки после возраста
	}
};
//static member definition:
int Human::count = 0;	//Определение статической переменной - обязательно вне класса.
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
	//return os << obj.get_last_name() << " " << obj.get_first_name() << " " << obj.get_age();
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student :public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 5;
	std::string speciality;
	std::string group;
	double rating;		//Оценка
	double attendance;	//Посещаемость
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//				Конструкторы:
	Student
	(
		HUMAN_TAKE_PARAMETERS,
		STUDENT_TAKE_PARAMETERS
	) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//					Методы:
	std::ostream& info(std::ostream& os)const override
	{
		Human::info(os); //Вызываем метод info базового класса
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(GROUP_WIDTH);
		os << group;
		os.width(RATING_WIDTH);
		os << rating;
		os.width(RATING_WIDTH);
		os << attendance;
		return os;

		//Human::info(os) << " ";
		//return os << speciality << " " << group << " " << rating << " " << attendance;
	}
	void save(std::ofstream& ofs) const override
	{
		ofs << "Student\n"; //Сохраняем тип класса
		Human::save(ofs); // Вызываем метод save базового класса Human для сохранения его данных.
		ofs << speciality << "\n"; //Сохраняем специальность
		ofs << group << "\n"; //Сохраняем группу
		ofs << rating << "\n"; //Сохраняем оценку
		ofs << attendance << "\n"; //Сохраняем посещаемость
	}

	void load(std::ifstream& ifs) override 
	{
		Human::load(ifs); // Загружаем данные базового класса Human
		std::getline(ifs, speciality); //Загружаем специальность
		std::getline(ifs, group); //Загружаем группу
		ifs >> rating; //Загружаем оценку
		ifs.ignore(); // Пропускаем символ новой строки после оценки
		ifs >> attendance; //Загружаем посещаемость
		ifs.ignore(); // Пропускаем символ новой строки после посещаемости
	}
};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher :public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int EXPERIENCE_WIDTH = 3;
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}

	//				Конструкторы:
	Teacher
	(
		HUMAN_TAKE_PARAMETERS,
		TEACHER_TAKE_PARAMETERS
	) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//				Методы:
	std::ostream& info(std::ostream& os)const override
	{
		Human::info(os); //Вызываем метод info базового класса
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(EXPERIENCE_WIDTH);
		os << experience;
		return os;
		//Human::info(os) << " ";
		//return os << speciality << " " << experience;
	}
	void save(std::ofstream& ofs) const override {
		ofs << "Teacher\n"; //Сохраняем тип класса
		Human::save(ofs); // Сохраняем данные базового класса Human
		ofs << speciality << "\n"; //Сохраняем специальность
		ofs << experience << "\n"; //Сохраняем опыт
	}
	void load(std::ifstream& ifs) override {
		Human::load(ifs); // Загружаем данные базового класса Human
		std::getline(ifs, speciality); //Загружаем специальность
		ifs >> experience; //Загружаем опыт
		ifs.ignore(); // Пропускаем символ новой строки после опыта
	}
};

class Graduate :public Student
{
	std::string subject;
public:
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject)
		:Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		this->subject = subject;
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	std::ostream& info(std::ostream& os)const override
	{
		Student::info(os) << " ";
		return os << subject;
	}
	void save(std::ofstream& ofs) const override
	{
		ofs << "Graduate\n"; //Сохраняем тип класса
		Student::save(ofs); // Сохраняем данные базового класса Student
		ofs << subject << "\n"; //Сохраняем тему дипломной работы
	}

	void load(std::ifstream& ifs) override {
		Student::load(ifs); // Загружаем данные базового класса Student
		std::getline(ifs, subject); //Загружаем тему дипломной работы
	}
};

// Функция для сохранения группы в файл
void saveGroupToFile(const std::vector<Human*>& group, const std::string& filename) 
{
	std::ofstream ofs(filename); // Открываем файл для записи
	if (ofs.is_open()) {
		ofs << group.size() << "\n";  // Сохраняем количество элементов в группе.
		for (const Human* person : group) {
			person->save(ofs); // Сохраняем каждый объект в файле, используя полиморфизм.
		}
		ofs.close(); // Закрываем файл
		std::cout << "Группа сохранена в файл: " << filename << std::endl;
	}
	else {
		std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
	}
}

// Функция для загрузки группы из файла
std::vector<Human*> loadGroupFromFile(const std::string& filename) 
{
	std::vector<Human*> group; // Вектор для хранения загруженной группы
	std::ifstream ifs(filename); // Открываем файл для чтения
	if (ifs.is_open()) {
		int groupSize;
		ifs >> groupSize; // Читаем количество элементов в группе
		ifs.ignore(); // Пропускаем символ новой строки после количества

		for (int i = 0; i < groupSize; ++i) {
			std::string classType;
			std::getline(ifs, classType); // Читаем тип класса из файла

			Human* person = nullptr;
			if (classType == "Human") {
				person = new Human("", "", 0); // Создаем объект Human
			}
			else if (classType == "Student") {
				person = new Student("", "", 0, "", "", 0, 0); // Создаем объект Student
			}
			else if (classType == "Teacher") {
				person = new Teacher("", "", 0, "", 0); // Создаем объект Teacher
			}
			else if (classType == "Graduate") {
				person = new Graduate("", "", 0, "", "", 0, 0, ""); // Создаем объект Graduate
			}
			else {
				std::cerr << "Неизвестный тип класса в файле: " << classType << std::endl;
				ifs.close();
				// Освобождаем выделенную память
				for (Human* h : group) {
					delete h;
				}
				return {}; // Возвращаем пустой вектор
			}

			if (person) {
				person->load(ifs); // Загружаем данные объекта из файла, используя полиморфизм.
				group.push_back(person); // Добавляем объект в группу
			}
		}

		ifs.close(); // Закрываем файл
		std::cout << "Группа загружена из файла: " << filename << std::endl;
	}
	else {
		std::cerr << "Не удалось открыть файл для чтения: " << filename << std::endl;
	}
	return group; // Возвращаем загруженную группу
}

void main()
{
	setlocale(LC_ALL, "");

	// Создаем группу людей
	std::vector<Human*> group = 
	{
		new Human("Montana", "Antonio", 25),
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 40, "Criminalistic", "WW_220", 40, 60, "How to catch Heisenberg"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20),
		new Graduate("Targarian", "Daineris", 22, "Flight", "GoT", 91, 92, "How to make smoke"),
		new Teacher("Schwartzneger", "Arnold", 85, "Heavy Metal", 60)
	};

	// Выводим группу на экран
	cout << "Исходная группа:\n";
	for (const Human* person : group) 
	{
		cout << *person << endl;
		cout << delimiter << endl;
	}

	// Сохраняем группу в файл
	saveGroupToFile(group, "group.txt");

	// Освобождаем память, выделенную для исходной группы
	for (Human* person : group) 
	{
		delete person;
	}
	group.clear();

	// Загружаем группу из файла
	std::vector<Human*> loadedGroup = loadGroupFromFile("group.txt");

	// Выводим загруженную группу на экран
	cout << "\nЗагруженная группа:\n";
	if (!loadedGroup.empty()) {
		for (const Human* person : loadedGroup) 
		{
			cout << *person << endl;
			cout << delimiter << endl;
		}
	}

	// Освобождаем память, выделенную для загруженной группы
	for (Human* person : loadedGroup) 
	{
		delete person;
	}
}