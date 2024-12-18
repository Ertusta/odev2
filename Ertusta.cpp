#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// personType class
class personType {
protected:
    string firstName;
    string lastName;

public:
    void setName(const string& first, const string& last) {
        firstName = first;
        lastName = last;
    }

    string getName() const {
        return firstName + " " + lastName;
    }

    void printName() const {
        cout << firstName << " " << lastName;
    }
};

// courseType class
class courseType {
private:
    string courseName;
    string courseNumber;
    int creditHours;
    char grade;

public:
    void setCourseInfo(const string& name, const string& number, int credits, char gr) {
        courseName = name;
        courseNumber = number;
        creditHours = credits;
        grade = gr;
    }

    void printCourseInfo(ofstream& outFile) const {
        outFile << left << setw(10) << courseNumber
             << setw(20) << courseName
             << setw(8) << creditHours
             << grade << endl;
    }

    string getCourseNumber() const { return courseNumber; }

    int getCreditHours() const { return creditHours; }

    char getGrade() const { return grade; }
};

// studentType class
class studentType : public personType {
private:
    string studentID;
    bool isTuitionPaid;
    int numberOfCourses;
    courseType* courses;

public:
    studentType() : courses(nullptr), numberOfCourses(0) {}

    ~studentType() {
        delete[] courses;
    }

    void setStudentInfo(const string& first, const string& last, const string& id, bool tuitionPaid, int numCourses) {
        setName(first, last);
        studentID = id;
        isTuitionPaid = tuitionPaid;
        numberOfCourses = numCourses;

        if (courses != nullptr)
            delete[] courses;

        courses = new courseType[numberOfCourses];
    }

    void setCourse(int index, const courseType& course) {
        if (index >= 0 && index < numberOfCourses) {
            courses[index] = course;
        }
    }

    void sortCourses() {
        for (int i = 0; i < numberOfCourses - 1; ++i) {
            for (int j = i + 1; j < numberOfCourses; ++j) {
                if (courses[i].getCourseNumber() > courses[j].getCourseNumber()) {
                    swap(courses[i], courses[j]);
                }
            }
        }
    }

    int getTotalCredits() const {
        int total = 0;
        for (int i = 0; i < numberOfCourses; ++i)
            total += courses[i].getCreditHours();
        return total;
    }

    double calculateGPA() const {
        if (!isTuitionPaid) return 0.0;

        double totalPoints = 0.0;
        int totalCredits = 0;

        for (int i = 0; i < numberOfCourses; ++i) {
            int credits = courses[i].getCreditHours();
            totalCredits += credits;

            switch (courses[i].getGrade()) {
            case 'A': totalPoints += 4.0 * credits; break;
            case 'B': totalPoints += 3.0 * credits; break;
            case 'C': totalPoints += 2.0 * credits; break;
            case 'D': totalPoints += 1.0 * credits; break;
            case 'F': totalPoints += 0.0 * credits; break;
            }
        }

        return totalCredits > 0 ? totalPoints / totalCredits : 0.0;
    }

    void printReport(ofstream& outFile, int tuitionPerCredit) const {
        outFile << "Student Name: " << getName() << endl;
        outFile << "Student ID: " << studentID << endl;
        outFile << "Number of courses enrolled: " << numberOfCourses << endl;

        if (isTuitionPaid) {
            outFile << left << setw(10) << "Course No"
                    << setw(20) << "Course Name"
                    << setw(8) << "Credits"
                    << "Grade" << endl;

            for (int i = 0; i < numberOfCourses; ++i)
                courses[i].printCourseInfo(outFile);

            outFile << "Total number of credits: " << getTotalCredits() << endl;
            outFile << "Mid-Semester GPA: " << fixed << setprecision(2) << calculateGPA() << endl;
        } else {
            outFile << "Grades are being withheld due to unpaid tuition." << endl;
            outFile << "Tuition due: $" << getTotalCredits() * tuitionPerCredit << endl;
        }

        outFile << endl;
    }
};

int main() {
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    if (!inFile || !outFile) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    int studentCount, tuitionPerCredit;
    inFile >> studentCount >> tuitionPerCredit;

    studentType* students = new studentType[studentCount];

    for (int i = 0; i < studentCount; ++i) {
        string firstName, lastName, studentID;
        char tuitionPaid;
        int numCourses;

        inFile >> firstName >> lastName >> studentID >> tuitionPaid >> numCourses;

        students[i].setStudentInfo(firstName, lastName, studentID, tuitionPaid == 'Y', numCourses);

        for (int j = 0; j < numCourses; ++j) {
            string courseName, courseNumber;
            int creditHours;
            char grade;

            inFile >> courseName >> courseNumber >> creditHours >> grade;

            courseType course;
            course.setCourseInfo(courseName, courseNumber, creditHours, grade);
            students[i].setCourse(j, course);
        }

        students[i].sortCourses();
    }

    for (int i = 0; i < studentCount; ++i) {
        students[i].printReport(outFile, tuitionPerCredit);
    }

    delete[] students;

    inFile.close();
    outFile.close();

    cout << "Reports generated successfully in output.txt." << endl;
    return 0;
}