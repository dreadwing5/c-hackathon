#include "utill.h"
#include "student.h"
using namespace std;

void utill::createStudent()
{
    student::Student st1;
    st1.loadStartupMenu();
}

void utill::createFaculty()
{
    student::Student st2;
    // ft1.loadFacultyMenu();
    cout << "Faculty Created";
}
void utill::on_Load()
{

    int ch1;

    cout << "Who are you? " << endl
         << "1. Student " << endl
         << "2. Teacher" << endl
         << "Enter your choice" << endl;
    cin >> ch1;
    clearScr();
    (ch1 == 1) ? utill::createStudent() : utill::createFaculty();
}

void utill::clearScr()
{
    cout << "\033[2J\033[1;1H";
}