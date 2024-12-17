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

    courseType() {}
    void setCourseinfo();
    void print(int a)
    {
        cout << courseName << endl
             << courseNo << endl
             << courseCredit << endl
             << courseGrade << endl
             << "--------------" << endl;
        ;
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
    personType(){

    }
    ~personType() {};
};

class studentType : public personType
{ // çocuk
private:
    int studentID;
    int numberOfCourses;
    bool isTuitionPaid;
    // dinamik bellek tahsis etcez herhalde bi yerde

public:
    courseType *coursesEnrolled;
    studentType(string firstName, string lastName, int studentID, int numberOfCourses, bool istuitionPaid);
    studentType()
    {

    }
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

courseType::courseType(string courseName, string courseNo, int courseCredit, char courseGrade)
{
    this->courseName = courseName;
    this->courseNo = courseNo;
    this->courseCredit = courseCredit;
    this->courseGrade = courseGrade;
}

studentType::studentType(string firstName, string lastName, int studentID, int numberOfCourses, bool isTuitionPaid) : personType(firstName, lastName)
{

    this->studentID = studentID;             // Öğrenci ID'sini ata
    this->numberOfCourses = numberOfCourses; // Ders sayısını ata
    this->isTuitionPaid = isTuitionPaid;     // Harç ödendi mi durumunu ata
    coursesEnrolled = new courseType[numberOfCourses];
}

studentType takePerson(string line)
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
    
    ss.clear();

    return a;
}

courseType takeCourse(string line)
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

    

    ss.clear();

    return course;
}
int main()
{
    int lineCounter = 0; // Satır sayısını tutmak için
    const string fileName = "input.txt";
    ifstream inputFile(fileName);
    string line;
    studentType *students ;
    students=new studentType[10];
    int counter1=0;
    int counter2=0;

    while (getline(inputFile, line))
    {
        stringstream iss(line);
        string word;
        int wordCount = 0;
        studentType target;
        
        

        while (iss >> word)
        {
            wordCount++;
        }

        if (wordCount == 5)
        {

            target = takePerson(line);
            students[counter1]=target;
            counter1++;
            counter2=0;
        }
        else if (wordCount == 4)
        {
            target.coursesEnrolled[counter2] = takeCourse(line);
            counter2++;
        }
    }

    students[0].print();
    students[0].coursesEnrolled[0].print(9);
    students[0].coursesEnrolled[1].print(9);
    students[0].coursesEnrolled[2].print(9);
    students[0].coursesEnrolled[3].print(9);
    students[1].print();
    students[1].coursesEnrolled[0].print(9);
    students[1].coursesEnrolled[1].print(9);
    students[1].coursesEnrolled[2].print(9);
    students[2].print();
    students[2].coursesEnrolled[0].print(9);
    students[2].coursesEnrolled[1].print(9);
  
    

    inputFile.close();
    return 0;
}
