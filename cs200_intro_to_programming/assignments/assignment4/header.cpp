#include <iostream>
#include <vector>
#include "header.h"

using namespace std;

/* people class member func. */

people::people()
{
	
}

people::people(string n, string pass, string dept)
{
	name = n;
	password = pass;
	department = dept;
}

void people::setName(string n)
{
	name = n;
}

void people::setPass(string pass)
{
	password = pass;
}

void people::setDept(string dept)
{	
	department = dept;
}

string people::getName()
{
	return name;
}

string people::getPass()
{
	return password;
}

string people::getDept()
{
	return department;
}

string people::getType()
{
	return "people";	
}

void people::viewInfo()
{
	cout << "Name : " << name << endl
		<< "Dept. : " << department << endl;
}

void people::viewCourses()
{
	
}

void people::addCourse(course* temp_course)
{
	
}

void people::dropCourse(course* temp_course)
{
	
}

void people::viewCourseStudents()
{
	
}

/* student class member func. */

student::student()
{
	
}

student::student(string n, string pass, string dept, float temp_gpa)
{
	name = n;
	password = pass;
	department = dept;
	gpa = temp_gpa;
}

void student::setGpa(float temp_gpa)
{
	gpa = temp_gpa;
}

float student::getGpa()
{
	return gpa;
}

string student::getType()
{
	return "student";	
}

void student::viewInfo()
{
	cout << "Name : " << name << "\t" << "Dept. : " << department << "\t" << "GPA : " << gpa << endl;
}

void student::viewCourses()
{
	for (int i = 0; i < courses.size(); i++)
	{
		cout << i+1 << " : " << courses[i]->getCode() << "\t" << courses[i]->getCap() << "\t" << courses[i]->getName() << "\t" << courses[i]->getInstructor() << endl;
	}
}

void student::addCourse(course* temp_course)
{
	courses.push_back(temp_course);
	temp_course->setCap(temp_course->getCap() - 1);
}

void student::dropCourse(course* temp_course)
{
	int temp_i = -1;
	for (int i = 0; i < courses.size(); i++)
	{
		if (temp_course->getCode() == courses[i]->getCode())
		{
			temp_i = i;
		}
	}
	if (temp_i != -1)
	{
		courses.erase(courses.begin() + temp_i);
		temp_course->setCap(temp_course->getCap() + 1);
	}
	else
	{
		cout << "\n\n Course Not Found! \n\n";
	}
}
		
/* instructor class member func. */

instructor::instructor()
{
	
}

instructor::instructor(string n, string pass, string dept)
{
	name = n;
	password = pass;
	department = dept;
}

string instructor::getType()
{
	return "instructor";	
}

void instructor::viewInfo()
{
	cout << "Name : " << name << "\t" << "Dept. : " << department << endl;
}

void instructor::viewCourses()
{
	for (int i = 0; i < courses.size(); i++)
	{
		cout << i+1 << " : " << courses[i]->getCode() << "\t" << courses[i]->getCap() << "\t" << courses[i]->getName() << endl;
	}
}

void instructor::addCourse(course* temp_course)
{
	courses.push_back(temp_course);
}

void instructor::viewCourseStudents()
{
	for (int i = 0; i < courses.size(); i++)
	{
		cout << courses[i]->getCode() << endl;
		courses[i]->viewCourseStudents();
	}
	cout << endl << endl;
}

/* course class member func. */		
		
course::course()
{
	
}

course::course(string n, string temp_code, int temp_cap, string ins)
{
	name = n;
	code = temp_code;
	cap = temp_cap;
	instructor = ins;
}

void course::setName(string n)
{
	name = n;
}

void course::setCode(string c)
{
	code = c;
}

void course::setCap(int c)
{
	cap = c;
}

void course::setInstructor(string ins)
{
	instructor = ins;
}

string course::getName()
{
	return name;
}

string course::getCode()
{
	return code;
}

string course::getInstructor()
{
	return instructor;
}

int course::getCap()
{
	return cap;
}

void course::addStudent(people* temp)
{
	students.push_back(temp);
}

void course::dropStudent(people* temp)
{
	int temp_i = -1;
	for (int i = 0; i < students.size(); i++)
	{
		if (students[i]->getName() == temp->getName())
		{
			temp_i = i;
		}
	}
	if (temp_i != -1)
	{
		students.erase(students.begin() + temp_i);
	}
	else
	{
		cout << "\n\n Student not Found! \n\n";
	}
}

void course::viewCourseStudents()
{
	for (int i = 0; i < students.size(); i++)
	{
		students[i]->viewInfo();
	}
}

/* zambeel class member function */

zambeel::zambeel()
{
	
}

void zambeel::signIn()
{
	string user;
	string pass;
	cout << "\n*******************\n"
		<< "Login Screen\n"
		<< "*******************\n\n";
	cout << "\nName : ";
	cin >> user;
	cout << "Password : ";
	cin >> pass;
	
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->getName() == user && users[i]->getPass() == pass)
		{
			if (users[i]->getType() == "student")
			{
				studentMenu(users[i]);
				return;
			}
			else if (users[i]->getType() == "instructor")
			{
				instructorMenu(users[i]);
				return;
			}
			break;
		}
	}
	
	cout << "\nSorry you don't exist in zambeel! or the password you entered is incorrect!'\n";
	return;
}

void zambeel::signUp()
{
	string name;
	string pass;
	string dept;
	float gpa;
	bool isStudent;
	bool isUnique = true;
	
	cout << "\n*******************\n"
		<< "SignUp Screen\n"
		<< "*******************\n\n";
	do
	{
		cout << "\nName : ";
		cin >> name;
		cout << "Password : ";
		cin >> pass;
		cout << "Department : ";
		cin >> dept;
		cout << "GPA : ";
		cin >> gpa;
		cout << "Are you an instructor, or a student?\n"
			<< "Press 0 for instructor, or press 1 for student!\n\n";
		cin >> isStudent;
		
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i]->getName() == name)
			{
				isUnique = false;
				cout << "\n\n This lad already exist in zambeel! \n\n";
				break;
			}
		}
		
	} while (isUnique == false);
	
	if (isStudent)
	{
		student* temp = new student(name, pass, dept, gpa);
		users.push_back(temp);
	}
	else if (!isStudent)
	{
		instructor* temp = new instructor(name, pass, dept);
		users.push_back(temp);
	}
	return;
}

void zambeel::studentMenu(people* temp)
{
	cout << "\n*******************\n"
		<< "Welcome " << temp->getName() << endl 
		<< "*******************\n\n";
	
	while (true)
	{
		cout << "\n1. View All Instructors\n"
			<< "2. View Offered Courses\n"
			<< "3. View Enrolled Courses\n"
			<< "4. Enroll a Course\n"
			<< "5. Drop a Course\n"
			<< "6. Logout\n\n";
		
		int option;
		cin >> option;
		
		if (option == 1)
		{
			viewAllInstructors();
		}
		else if (option == 2)
		{
			viewAllCourses();
		}
		else if (option == 3)
		{
			temp->viewCourses();
		}
		else if (option == 4)
		{
			enrollACourse(temp);
		}
		else if (option == 5)
		{
			dropACourse(temp);
		}
		else if (option == 6)
		{
			return;
		}
		else 
		{
			cout << "\nInvalid Option\n\n";
		}
	}
}

void zambeel::instructorMenu(people* temp)
{
	cout << "\n*******************\n"
		<< "Welcome " << temp->getName() << endl 
		<< "*******************\n\n";
	
	while (true)
	{
		cout << "\n1. Create a Course\n"
			<< "2. View All Students\n"
			<< "3. View Students Enrolled in your Courses\n"
			<< "4. Drop a Student from a Course\n"
			<< "5. Logout\n\n";
		
		int option;
		cin >> option;
		
		if (option == 1)
		{
			createACourse(temp);
		}
		else if (option == 2)
		{
			viewAllStudents();
		}
		else if (option == 3)
		{
			temp->viewCourseStudents();
		}
		else if (option == 4)
		{
			dropAStudent();
		}
		else if (option == 5)
		{
			return;
		}
		else 
		{
			cout << "\nInvalid Option\n\n";
		}
	}
}

void zambeel::viewAllStudents()
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->getType() == "student")
		{
			users[i]->viewInfo();
		}
	}
}

void zambeel::viewAllInstructors()
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->getType() == "instructor")
		{
			users[i]->viewInfo();
		}
	}
}

void zambeel::viewAllCourses()
{
	for (int i = 0; i < courses.size(); i++)
	{
		cout << courses[i]->code << "\t" << courses[i]->name << "\t" << courses[i]->cap << "\t" << courses[i]->instructor << endl;
	}
}

people* zambeel::getUser(string n)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->name == n)
		{
			return users[i];
		}
	}
	cout << "User does not exist!\n";
}


course* zambeel::getCourse(string c)
{
	for (int i = 0; i < courses.size(); i++)
	{
		if (courses[i]->code == c)
		{
			return courses[i];
		}
	}
	cout << "Course does not exist!\n";
}

void zambeel::enrollACourse(people* temp)
{
	string temp_code;
	cout << "Enter Course Code : ";
	cin >> temp_code;
	
	course* temp_course = getCourse(temp_code);
	temp_course->addStudent(temp);
	temp->addCourse(temp_course);
}

void zambeel::createACourse(people* temp)
{
	string temp_code;
	string n;
	int temp_cap;
	cout << "Code : ";
	cin >> temp_code;
	cout << "Name : ";
	cin >> n;
	cout << "Cap : ";
	cin >> temp_cap;
	course* temp_course = new course(n, temp_code, temp_cap, temp->getName());
	courses.push_back(temp_course);
	temp->addCourse(temp_course);
}

void zambeel::dropACourse(people* temp)
{
	string temp_code;
	cout << "Enter Course Code : ";
	cin >> temp_code;
	
	course* temp_course = getCourse(temp_code);
	temp->dropCourse(temp_course);
	temp_course->dropStudent(temp);
}

void zambeel::dropAStudent()
{
	string temp_name;
	cout << "Enter Student Name: ";
	cin >> temp_name;
	people* temp_student = getUser(temp_name);
	string temp_code;
	cout << "Enter Course Code : ";
	cin >> temp_code;
	course* temp_course = getCourse(temp_code);
	
	temp_course->dropStudent(temp_student);
	temp_student->dropCourse(temp_course);
}
	

/* Friend Functions */
ostream& operator <<(ostream& outs, const student*& temp)
{	
	outs << temp->name << "\t" << temp->department << "\t" << temp->gpa << endl;
		 
	return outs;
}

ostream& operator <<(ostream& outs, const instructor*& temp)
{	
	outs << temp->name << "\t" << temp->department << "\t" << endl;
		 
	return outs;
}
	
ostream& operator <<(ostream& outs, const course*& temp)
{	
	outs << temp->code << "\t" << temp->name << "\t" << temp->cap << "\t" << temp->instructor << endl;
		 
	return outs;
}	

		
	
	
	
	
	
	
	
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
