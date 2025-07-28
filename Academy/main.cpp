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

	//				������������:
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

	//				  ������:
	virtual std::ostream& info(std::ostream& os)const
	{
		//return os << last_name << " " << first_name << " " << age;
		os.width(LAST_NAME_WIDTH);	//������ ���� ��� �������
		os << std::left; //������������ �����
		os << last_name;
		os.width(FIRST_NAME_WIDTH); //������ ���� ��� �����
		os << first_name;
		os.width(AGE_WIDTH); //������ ���� ��� ��������
		os << age;
		return os;
	}

	virtual void save(std::ofstream& ofs) const 
	{
		ofs << "Human\n"; //��������� ��� ������
		ofs << last_name << "\n"; //��������� �������
		ofs << first_name << "\n"; //��������� ���
		ofs << age << "\n"; //��������� �������
	}

	virtual void load(std::ifstream& ifs) 
	{
		std::getline(ifs, last_name); //��������� �������
		std::getline(ifs, first_name); //��������� ���
		ifs >> age; //��������� �������
		ifs.ignore(); // ���������� ������ ����� ������ ����� ��������
	}
};
//static member definition:
int Human::count = 0;	//����������� ����������� ���������� - ����������� ��� ������.
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
	double rating;		//������
	double attendance;	//������������
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

	//				������������:
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

	//					������:
	std::ostream& info(std::ostream& os)const override
	{
		Human::info(os); //�������� ����� info �������� ������
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
		ofs << "Student\n"; //��������� ��� ������
		Human::save(ofs); // �������� ����� save �������� ������ Human ��� ���������� ��� ������.
		ofs << speciality << "\n"; //��������� �������������
		ofs << group << "\n"; //��������� ������
		ofs << rating << "\n"; //��������� ������
		ofs << attendance << "\n"; //��������� ������������
	}

	void load(std::ifstream& ifs) override 
	{
		Human::load(ifs); // ��������� ������ �������� ������ Human
		std::getline(ifs, speciality); //��������� �������������
		std::getline(ifs, group); //��������� ������
		ifs >> rating; //��������� ������
		ifs.ignore(); // ���������� ������ ����� ������ ����� ������
		ifs >> attendance; //��������� ������������
		ifs.ignore(); // ���������� ������ ����� ������ ����� ������������
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

	//				������������:
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

	//				������:
	std::ostream& info(std::ostream& os)const override
	{
		Human::info(os); //�������� ����� info �������� ������
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(EXPERIENCE_WIDTH);
		os << experience;
		return os;
		//Human::info(os) << " ";
		//return os << speciality << " " << experience;
	}
	void save(std::ofstream& ofs) const override {
		ofs << "Teacher\n"; //��������� ��� ������
		Human::save(ofs); // ��������� ������ �������� ������ Human
		ofs << speciality << "\n"; //��������� �������������
		ofs << experience << "\n"; //��������� ����
	}
	void load(std::ifstream& ifs) override {
		Human::load(ifs); // ��������� ������ �������� ������ Human
		std::getline(ifs, speciality); //��������� �������������
		ifs >> experience; //��������� ����
		ifs.ignore(); // ���������� ������ ����� ������ ����� �����
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
		ofs << "Graduate\n"; //��������� ��� ������
		Student::save(ofs); // ��������� ������ �������� ������ Student
		ofs << subject << "\n"; //��������� ���� ��������� ������
	}

	void load(std::ifstream& ifs) override {
		Student::load(ifs); // ��������� ������ �������� ������ Student
		std::getline(ifs, subject); //��������� ���� ��������� ������
	}
};

// ������� ��� ���������� ������ � ����
void saveGroupToFile(const std::vector<Human*>& group, const std::string& filename) 
{
	std::ofstream ofs(filename); // ��������� ���� ��� ������
	if (ofs.is_open()) {
		ofs << group.size() << "\n";  // ��������� ���������� ��������� � ������.
		for (const Human* person : group) {
			person->save(ofs); // ��������� ������ ������ � �����, ��������� �����������.
		}
		ofs.close(); // ��������� ����
		std::cout << "������ ��������� � ����: " << filename << std::endl;
	}
	else {
		std::cerr << "�� ������� ������� ���� ��� ������: " << filename << std::endl;
	}
}

// ������� ��� �������� ������ �� �����
std::vector<Human*> loadGroupFromFile(const std::string& filename) 
{
	std::vector<Human*> group; // ������ ��� �������� ����������� ������
	std::ifstream ifs(filename); // ��������� ���� ��� ������
	if (ifs.is_open()) {
		int groupSize;
		ifs >> groupSize; // ������ ���������� ��������� � ������
		ifs.ignore(); // ���������� ������ ����� ������ ����� ����������

		for (int i = 0; i < groupSize; ++i) {
			std::string classType;
			std::getline(ifs, classType); // ������ ��� ������ �� �����

			Human* person = nullptr;
			if (classType == "Human") {
				person = new Human("", "", 0); // ������� ������ Human
			}
			else if (classType == "Student") {
				person = new Student("", "", 0, "", "", 0, 0); // ������� ������ Student
			}
			else if (classType == "Teacher") {
				person = new Teacher("", "", 0, "", 0); // ������� ������ Teacher
			}
			else if (classType == "Graduate") {
				person = new Graduate("", "", 0, "", "", 0, 0, ""); // ������� ������ Graduate
			}
			else {
				std::cerr << "����������� ��� ������ � �����: " << classType << std::endl;
				ifs.close();
				// ����������� ���������� ������
				for (Human* h : group) {
					delete h;
				}
				return {}; // ���������� ������ ������
			}

			if (person) {
				person->load(ifs); // ��������� ������ ������� �� �����, ��������� �����������.
				group.push_back(person); // ��������� ������ � ������
			}
		}

		ifs.close(); // ��������� ����
		std::cout << "������ ��������� �� �����: " << filename << std::endl;
	}
	else {
		std::cerr << "�� ������� ������� ���� ��� ������: " << filename << std::endl;
	}
	return group; // ���������� ����������� ������
}

void main()
{
	setlocale(LC_ALL, "");

	// ������� ������ �����
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

	// ������� ������ �� �����
	cout << "�������� ������:\n";
	for (const Human* person : group) 
	{
		cout << *person << endl;
		cout << delimiter << endl;
	}

	// ��������� ������ � ����
	saveGroupToFile(group, "group.txt");

	// ����������� ������, ���������� ��� �������� ������
	for (Human* person : group) 
	{
		delete person;
	}
	group.clear();

	// ��������� ������ �� �����
	std::vector<Human*> loadedGroup = loadGroupFromFile("group.txt");

	// ������� ����������� ������ �� �����
	cout << "\n����������� ������:\n";
	if (!loadedGroup.empty()) {
		for (const Human* person : loadedGroup) 
		{
			cout << *person << endl;
			cout << delimiter << endl;
		}
	}

	// ����������� ������, ���������� ��� ����������� ������
	for (Human* person : loadedGroup) 
	{
		delete person;
	}
}