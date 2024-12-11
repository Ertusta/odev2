#include <iostream>
using namespace std;


class courseType {//yan class
private:
    string courseName;
    string courseNo;
    int courseCredit;
    char courseGrade;

public:
    courseType(string courseName, string courseNo, int courseCredit, char courseGrade);
    void setCourseinfo();
    void print(int a);
    void print(int a, int b);//iki tane olcak
    int getCredit();
    int getCourseNumber();
    char getGrade();
    ~courseType();
};



class studentType {//ana class
private:
    string firstName;
    int studentID;
    int numberOfCourses;
    bool isTuitionPaid;
    courseType* coursesEnrolled;//dinamik bellek tahsis etcez herhalde bi yerde

public:
    studentType(string firstName, int studentID,  int numberOfCourses, bool istuitionPaid);
    void setInfo();//input.txt den okuycak muhtemelen
    void setName();
    void getName();
    void print();//başka dosya oluşturacak herhalde bunlar
    void print(int a);
    void print(int a,int b);//3 tane olcak
    int getHoursEnrolled();
    char getGpa();
    float getBillingAmount();
    ~studentType();

};


class personType : public studentType{//çocuk
protected:
    string lastName;
public:
 personType(string firstName, string lastName, int studentID, int numberOfCourses, bool isTuitionPaid);
 ~personType();
};

int main() {

    return 0;
}
