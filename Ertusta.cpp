#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class courseType
{ // yan class
private:
    string courseName;
    string courseNo;
    int courseCredit;
    char courseGrade;

public:
    courseType(string courseName, string courseNo, int courseCredit, char courseGrade);
    void setCourseinfo();
    void print(int a)
    {
        cout << courseName << endl
             << courseNo << endl
             << courseCredit << endl
             << courseGrade<< endl
             << "--------------" << endl;;
    };
    void print(int a, int b); // iki tane olcak
    int getCredit();
    int getCourseNumber();
    char getGrade();
    ~courseType() {};
};

class personType
{ // ana
protected:
    string lastName;
    string firstName;

public:
    personType(string firstName, string lastName);
    ~personType() {};
};

class studentType : public personType
{ // çocuk
private:
    int studentID;
    int numberOfCourses;
    bool isTuitionPaid;
    courseType *coursesEnrolled; // dinamik bellek tahsis etcez herhalde bi yerde

public:
    studentType(string firstName, string lastName, int studentID, int numberOfCourses, bool istuitionPaid);
    void setInfo(); // input.txt den okuycak muhtemelen
    void setName();
    void getName();
    void print()
    {
        cout << firstName << endl
             << lastName << endl
             << studentID << endl
             << isTuitionPaid << endl
             << numberOfCourses << endl
             << "--------------" << endl;
    }; // başka dosya oluşturacak herhalde bunlar
    void print(int a);
    void print(int a, int b); // 3 tane olcak
    int getHoursEnrolled();
    char getGpa();
    float getBillingAmount();
    ~studentType() {};
};

personType::personType(string firstName, string lastName)
{
    this->firstName = firstName;
    this->lastName = lastName;
}

studentType::studentType(string firstName, string lastName, int studentID, int numberOfCourses, bool isTuitionPaid) : personType(firstName, lastName)
{

    this->studentID = studentID;             // Öğrenci ID'sini ata
    this->numberOfCourses = numberOfCourses; // Ders sayısını ata
    this->isTuitionPaid = isTuitionPaid;     // Harç ödendi mi durumunu ata
}

courseType::courseType(string courseName, string courseNo, int courseCredit, char courseGrade)
{
    this->courseName = courseName;
    this->courseNo = courseNo;
    this->courseCredit = courseCredit;
    this->courseGrade = courseGrade;
}

int takePerson(string line)
{
    stringstream ss(line);
    string firstName, lastName;
    int studentID, numberOfCourses;
    char istuitionPaid;

    ss >> firstName;
    ss.ignore(1);
    ss >> lastName;
    ss.ignore(1);
    ss >> studentID;
    ss.ignore(1);
    ss >> istuitionPaid;
    ss.ignore(1);
    ss >> numberOfCourses;
    ss.ignore(1);

    studentType a(firstName, lastName, studentID, numberOfCourses, istuitionPaid);
    a.print();
    ss.clear();

    return 0;
}

int takeCourse(string line)
{
    stringstream ss(line);
    ss.str(line); // Stringstream ile satırı işleme

    string courseName, courseNo;
    int courseCredit;
    char courseGrade;

    // Kurs adını, kurs numarasını, krediyi ve notu okuma
    ss >> courseName;
    ss.ignore(1);
    ss >> courseNo;
    ss.ignore(1);
    ss >> courseCredit;
    ss.ignore(1);
    ss >> courseGrade;

    courseType course(courseName, courseNo, courseCredit, courseGrade);

    course.print(8);

    ss.clear();

    return 0;
}
int main()
{
    int lineCounter = 0; // Satır sayısını tutmak için
    const string fileName = "input.txt";
    ifstream inputFile(fileName);
    string line;


    while (getline(inputFile, line) ) {
        stringstream iss(line);
        string word;
        int wordCount = 0;

        while (iss >> word) {
            wordCount++;
        }

        if (wordCount == 5) {
            takePerson(line);
        } else if (wordCount == 4) {
            takeCourse(line);
        } 
    }

    inputFile.close();
    return 0;
}
