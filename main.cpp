#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class personType
{
protected:
    string firstName;
    string lastName;

public:
    void setName(const string &first, const string &last);
    string getName() const;
};

void personType::setName(const string &first, const string &last)
{
    firstName = first;
    lastName = last;
}

string personType::getName() const
{
    return firstName + " " + lastName;
}

class courseType
{
private:
    string courseName;
    string courseNumber;
    int creditHours;
    char grade;

public:
    void setCourseInfo(const string &name, const string &number, int credits, char gr);
    void print(ofstream &outFile) const;
    string getCourseNumber() const;
    int getCredits() const;
    char getGrade() const;
    courseType(const string &name, const string &number, int credits, char gr);
    courseType();
    ~courseType();
};

void courseType::setCourseInfo(const string &name, const string &number, int credits, char gr)
{
    courseName = name;
    courseNumber = number;
    creditHours = credits;
    grade = gr;
}

void courseType::print(ofstream &outFile) const
{
    outFile << left << setw(10) << courseNumber
            << setw(20) << courseName
            << setw(8) << creditHours
            << grade << endl;
}

string courseType::getCourseNumber() const { return courseNumber; }

int courseType::getCredits() const { return creditHours; }

char courseType::getGrade() const { return grade; }

courseType::courseType(const string &name, const string &number, int credits, char gr)
{
    courseName = name;
    courseNumber = number;
    creditHours = credits;
    grade = gr;
}

courseType::courseType() {}

courseType::~courseType() {}

class studentType : public personType
{
private:
    string studentID;
    bool isTuitionPaid;
    int numberOfCourses;
    courseType *courses;

public:
    studentType();
    ~studentType();
    void setInfo(const string &first, const string &last, const string &id, bool tuitionPaid, int numCourses);
    void setCourse(int index, const courseType &course);
    void sortCourses();
    int getTotalCredits() const;
    double getGPA() const;
    double billingAmount(int tuitionPerCredit) const;
    void print(ofstream &outFile, int tuitionPerCredit) const;
};

studentType ::studentType() : courses(nullptr), numberOfCourses(0) {}

studentType ::~studentType()
{
    delete[] courses;
}

void studentType ::setInfo(const string &first, const string &last, const string &id, bool tuitionPaid, int numCourses)
{
    setName(first, last);
    studentID = id;
    isTuitionPaid = tuitionPaid;
    numberOfCourses = numCourses;

    if (courses != nullptr)
        delete[] courses;

    courses = new courseType[numberOfCourses];
}

void studentType ::setCourse(int index, const courseType &course)
{
    if (index >= 0 && index < numberOfCourses)
    {
        courses[index] = course;
    }
}

void studentType ::sortCourses()
{
    for (int i = 0; i < numberOfCourses - 1; ++i)
    {
        for (int j = i + 1; j < numberOfCourses; ++j)
        {
            if (courses[i].getCourseNumber() > courses[j].getCourseNumber())
            {
                swap(courses[i], courses[j]);
            }
        }
    }
}

int studentType ::getTotalCredits() const
{
    int total = 0;
    for (int i = 0; i < numberOfCourses; ++i)
        total += courses[i].getCredits();
    return total;
}

double studentType ::getGPA() const
{
    if (!isTuitionPaid)
        return 0.0;

    double totalPoints = 0.0;
    int totalCredits = 0;

    for (int i = 0; i < numberOfCourses; ++i)
    {
        int credits = courses[i].getCredits();
        totalCredits += credits;

        switch (courses[i].getGrade())
        {
        case 'A':
            totalPoints += 4.0 * credits;
            break;
        case 'B':
            totalPoints += 3.0 * credits;
            break;
        case 'C':
            totalPoints += 2.0 * credits;
            break;
        case 'D':
            totalPoints += 1.0 * credits;
            break;
        case 'F':
            totalPoints += 0.0 * credits;
            break;
        }
    }

    if (totalCredits > 0)
    {
        return totalPoints / totalCredits;
    }
    else
    {
        return 0.0;
    }
}

double studentType ::billingAmount(int tuitionPerCredit) const
{
    return getTotalCredits() * tuitionPerCredit;
}

void studentType ::print(ofstream &outFile, int tuitionPerCredit) const
{
    outFile << "Student Name: " << getName() << endl;
    outFile << "Student ID: " << studentID << endl;
    outFile << "Number of courses enrolled: " << numberOfCourses << endl;

    if (isTuitionPaid)
    {
        outFile << left << setw(10) << "Course No"
                << setw(20) << "Course Name"
                << setw(8) << "Credits"
                << "Grade" << endl;

        for (int i = 0; i < numberOfCourses; ++i)
            courses[i].print(outFile);

        outFile << "Total number of credits: " << getTotalCredits() << endl;
        outFile << "Mid-Semester GPA: " << fixed << setprecision(2) << getGPA() << endl;
    }
    else
    {
        outFile << "notlar ogrenim ucreti odenmemesi nedeniyle bekletiliyor." << endl;
        outFile << "Harc miktari: $" << billingAmount(tuitionPerCredit) << endl;
    }

    outFile << endl;
}

int main()
{
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    int studentCount, tuitionPerCredit;
    inFile >> studentCount >> tuitionPerCredit;

    studentType *students = new studentType[studentCount];

    for (int i = 0; i < studentCount; ++i)
    {
        string firstName, lastName, studentID;
        char tuitionPaid;
        int numCourses;

        inFile >> firstName >> lastName >> studentID >> tuitionPaid >> numCourses;

        students[i].setInfo(firstName, lastName, studentID, tuitionPaid == 'Y', numCourses);

        for (int j = 0; j < numCourses; ++j)
        {
            string courseName, courseNumber;
            int creditHours;
            char grade;

            inFile >> courseName >> courseNumber >> creditHours >> grade;

            courseType course = courseType(courseName, courseNumber, creditHours, grade);

            students[i].setCourse(j, course);
        }

        students[i].sortCourses();
    }

    for (int i = 0; i < studentCount; ++i)
    {
        students[i].print(outFile, tuitionPerCredit);
    }

    delete[] students;

    inFile.close();
    outFile.close();

    cout << "Not raporu olusturuldu" << endl;
    return 0;
}