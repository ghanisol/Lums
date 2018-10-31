#include <iostream>
#include <vector>

using namespace std;
class people;
class student;
class instructor;
class zambeel;
class course;

class people
{
		public:
		string name;
		string password;
		string department;

		people();
		people(string n, string pass, string dept);
		void setName(string n);
		void setPass(string pass);
		void setDept(string dept);
		string getName();
		string getPass();
		string getDept();
		virtual string getType();
		virtual void viewInfo();
		virtual void viewCourses();
		virtual void addCourse(course* temp_course);
		virtual void dropCourse(course* temp_course);
		virtual void viewCourseStudents();
		friend ostream& operator <<(ostream& outs, const people& temp);

};

class student : public people
{
	public:
		float gpa;
		vector<course*>courses;
	
		student();
		student(string n, string pass, string dept, float temp_gpa);
		void setGpa(float temp_gpa);
		float getGpa();
		virtual string getType();
		virtual void viewInfo();
		virtual void viewCourses();
		virtual void addCourse(course* temp_course);
		virtual void dropCourse(course* temp_course);
		friend ostream& operator <<(ostream& outs, const student& temp);
		
	
};

class instructor : public people
{
	public:
		vector<course*>courses;
	
		instructor();
		instructor(string n, string pass, string dept);
		virtual string getType();
		virtual void viewInfo();
		virtual void viewCourses();
		virtual void viewCourseStudents();
		virtual void addCourse(course* temp_course);
		friend ostream& operator <<(ostream& outs, const instructor& temp);
};

class course
{
	public:
		string name;
		string code;
		int cap;
		string instructor;
		vector<people*>students;	
	
		course();
		course(string n, string temp_code, int temp_cap, string ins);
		void setName(string n);
		void setCode(string c);
		void setCap(int c);
		void setInstructor(string ins);
		string getName();
		string getCode();
		int getCap();
		virtual void viewCourseStudents();
		void addStudent(people* temp);
		void dropStudent(people* temp);
		string getInstructor();
		friend ostream& operator <<(ostream& outs, const course& temp);
};

class zambeel
{
	public:
		vector<people*>users;
		vector<course*>courses;
	
		zambeel();
		void signIn();
		void signUp();
		void studentMenu(people* temp);
		void instructorMenu(people* temp);
		void viewAllStudents();
		void viewAllInstructors();
		void viewAllCourses();
		void enrollACourse(people* temp);
		void dropACourse(people* temp);
		void dropAStudent();
		void createACourse(people* temp);
		friend ostream& operator <<(ostream& outs, const student& temp);
		friend ostream& operator <<(ostream& outs, const instructor& temp);
		friend ostream& operator <<(ostream& outs, const course& temp);
		people* getUser(string n);
		course* getCourse(string c);
};
















