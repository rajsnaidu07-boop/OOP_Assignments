#include <iostream>
using namespace std;
class Student {
private:
    string Name;
protected:
    int DOB;
public:
    Student(string name, int dob) : Name(name), DOB(dob) {}
    void display() {
        cout << "Name: " << Name << ", DOB: " << DOB << endl;
    }
};
class Grade : public Student {
    int marks;
public:
    Grade(string name, int dob, int m) : Student(name, dob), marks(m) {}
    void showGrade() {
        display();
        cout << "Marks: " << marks << ", DOB (protected access): " << DOB << endl;
    }
};
int main() {
    Grade myDetails("Raj", 2007, 85);
    myDetails.showGrade();
    return 0;
}
}
