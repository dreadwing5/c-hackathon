#include <cpr/cpr.h>
#include <iostream>
#include <string.h>
#include <nlohmann/json.hpp>
#include "student.h"
#include "utill.h"

using namespace std;
// for convenience
using json = nlohmann::json;

void registerStudent();
void registerFaculty();
void loginStudent();
void loginFaculty();
void studentUpload();
void facultyUpload();
void getAllAssignment();
void getAssignment();
void assignScore();
void getScore();
void notifyStudent(string id);
void getNotificationStudent();

int studentDashboard()
{
    int ch;

    while (1)
    {
        cout << "***********************      STUDENT  MENU        *******************************\n\n";
        cout << "1. View Assignments" << endl;
        cout << "2. View Notification" << endl;
        cout << "3. Upload Assignments" << endl;
        cout << "4. View Score" << endl;
        cout << "5. Exit" << endl;

        cout
            << "Enter your Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "\033[2J\033[1;1H";
            getAssignment();
            break;

        case 2:
            cout << "\033[2J\033[1;1H";
            getNotificationStudent();

            break;

        case 3:
            cout << "\033[2J\033[1;1H";
            studentUpload();

            break;

        case 4:
            cout << "\033[2J\033[1;1H";
            getScore();
            break;

        default:
            cout << "\033[2J\033[1;1H";
            return 0;
        }
    }
}

int facultyDashBoard()
{

    int ch;

    while (1)
    {
        cout << "***********************      FACULTY MENU        *******************************\n\n";
        cout << "1. Upload Assignments" << endl;
        cout << "2. View Notification" << endl;
        cout << "3. View All Assignments" << endl;
        cout << "4. Assign Score" << endl;
        cout << "5. Exit" << endl;

        cout
            << "Enter your Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "\033[2J\033[1;1H";
            facultyUpload();
            break;

        case 2:
            cout << "\033[2J\033[1;1H";
            cout << "Work in Progress....";

            break;

        case 3:
            cout << "\033[2J\033[1;1H";
            getAllAssignment();

            break;

        case 4:
            assignScore();
            break;

        default:
            cout << "\033[2J\033[1;1H";
            return 0;
        }
    }
}

int main(int argc, char **argv)
{

    // onLoad();
    // student::Student st;
    // st.do_something();
    utill::on_Load();
    /* int ch;
    while (1)
    {
        cout << "************************       MENU        *******************************\n\n";
        cout << "1. Student Login" << endl;
        cout << "2. Faculty Login" << endl;
        cout << "3. Student Registration" << endl;
        cout << "4. Faculty Registration" << endl;
        cout << "5. Exit" << endl;

        cout
            << "Enter your Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            loginStudent();
            cout << "\033[2J\033[1;1H";
            studentDashboard();
            break;

        case 2:
            loginFaculty();
            cout << "\033[2J\033[1;1H";
            facultyDashBoard();

            break;

        case 3:
            registerStudent();
            cout << "\033[2J\033[1;1H";
            studentDashboard();
            break;

        case 4:
            registerFaculty();
            cout << "\033[2J\033[1;1H";
            facultyDashBoard();

        default:
            return 0;
        }
    } */
}

//Helper Function -->Communicate with server
void loginStudent()
{
    //Test Data
    json j2 = {
        {"usn", "1CR19IS125"},
        {"password", "12345"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/student/login"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
    std::cout << r.text << std::endl;
}

void registerStudent()
{
    json j2 = {
        {"name", "sachin"},
        {"usn", "1CR19IS125"},
        {"department", "ise"},
        {"password", "12345"},
        {"password2", "12345"},
        {"mailid", "sack19is@cmrit.ac.in"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/student"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get(); // Since the request is complete, this returns immediately
    std::cout << r.text << std::endl;
}

void loginFaculty()
{
    json j2 = {
        {"facultyId", "12345"},
        {"password", "12345"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/faculty/login"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
    std::cout << r.text << std::endl;
}

void registerFaculty()
{

    //Test Data
    json j2 = {
        {"name", "sachin(FACULTY)"},
        {"facultyId", "12345"},
        {"department", "ise"},
        {"password", "12345"},
        {"password2", "12345"},
        {"mailId", "sack19is@cmrit.ac.in"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/faculty"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
    std::cout << r.text << std::endl;
}

void studentUpload()
{
    json j2 = {{"filePath", "/Users/naveen/development/cpp-hackathon/sample.txt"}, {"usn", "1CR19IS125"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/student/upload"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
    std::cout << r.text << std::endl;
}

void facultyUpload()
{

    json j2 = {{"filePath", "/Users/naveen/development/cpp-hackathon/sample.txt"}, {"facultyId", "12345"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/faculty/upload"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
    json j_complete = json::parse(r.text);

    std::string link = j_complete.value("fileName", "oops");
    notifyStudent(link);
}

void getAllAssignment()
{

    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:3000/api/faculty/assignment"});

    json j_complete = json::parse(r.text);

    for (auto &&i : j_complete)
    {

        std::string usn = i.value("usn", "oops");
        std::string name = i.value("name", "oops");
        std::string link = i.value("link", "oops");

        cout << "USN : " << usn << "\t"
             << "Name : " << name << "\t"
             << "Link : " << link << "\t\n";

        cout << endl;
    }
}

//get Particalur assignment a student

void getAssignment()
{

    string usn1 = "1CR19IS125";
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:3000/api/faculty/assignment/" + usn1});
    json j_complete = json::parse(r.text);
    std::string usn = j_complete.value("usn", "oops");
    std::string name = j_complete.value("name", "oops");
    std::string assignment = j_complete.value("assignment", "oops");

    cout << "USN : " << usn << "\t"
         << "Name : " << name << "\t"
         << "Link : " << assignment << "\t\n";

    cout << endl;
}

void assignScore()
{
    string usn = "1CR19IS125";

    json j2 = {
        {"Q1", "10"},
        {"Q2", "8"},
        {"Q3", "9"},
        {"Q4", "10"},
        {"Q5", "8"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/faculty/score/" + usn},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
    std::cout << r.text << std::endl;
    if (r.status_code == 200)
    {
        cout << "Mark Assigned Successfully!";
    }
}

void getScore()
{
    string usn = "1CR19IS125";
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:3000/api/student/score/" + usn});
    cout << r.text << endl;
}

void notifyStudent(string id)
{

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/faculty/notification/" + id},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
    std::cout << r.text << std::endl;
}

void getNotificationStudent()
{
    /*  string usn = "1234";
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:3000/api/student/notification/" + usn});
    std::cout << r.text << std::endl; */
    cout << "Work in Progress";
}
