#include <cpr/cpr.h>
#include <iostream>
#include <string.h>
#include <nlohmann/json.hpp>

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

int main(int argc, char **argv)
{
    /* cpr::Response r = cpr::Get(cpr::Url{"http://localhost:3000/api/student"});
    r.status_code;            // 200
    r.header["content-type"]; // application/json; charset=utf-8
    r.text;                   // JSON text string

    cout << "text" << r.text; */
    /*  cpr::Response r = cpr::Post(cpr::Url{"localhost:3000/api/student"},
                                cpr::Body{"This is raw POST data"},
                                cpr::Header{{"Content-Type", "text/plain"}});
    cout << r.text << endl; */

    /*    string name, usn, password, password2;
    cout << "NAME : ";
    getline(cin, name);
    cout << "USN : ";
    getline(cin, usn);
    cout << "Password : ";
    getline(cin, password);
    cout << "Repeat Password : ";
    getline(cin, password2);
    json j2 = {
        {"name", name},
        {"usn", usn},
        {"password", password},
        {"password2", password2}}; */

    /*      cpr::Response r = cpr::Post(cpr::Url{"localhost:3000/api/student"},
                                cpr::Body{"This is raw POST data"},
                                cpr::Header{{"Content-Type", "text/plain"}});
    cout << r.status_code << endl; */
    // facultyUpload();
    // getAssignment();
    // assignScore();
    getScore();
}

void registerStudent()
{
    json j2 = {
        {"name", "sachin"},
        {"usn", "12345"},
        {"department", "ise"},
        {"password", "1234"},
        {"password2", "1234"},
        {"mailid", "sack19is@cmrit.ac.in"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/student"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get(); // Since the request is complete, this returns immediately
    std::cout << r.text << std::endl;
}

void registerFaculty()
{

    //Test Data
    json j2 = {
        {"name", "sachin"},
        {"facultyId", "12345"},
        {"department", "ise"},
        {"password", "1234"},
        {"password2", "1234"},
        {"mailId", "sack19is@cmrit.ac.in"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/faculty"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
    std::cout << r.text << std::endl;
}

void loginStudent()
{
    //Test Data
    json j2 = {
        {"usn", "12345"},
        {"password", "1234"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/student/login"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
    std::cout << r.text << std::endl;
}

void loginFaculty()
{
    json j2 = {
        {"facultyId", "12345"},
        {"password", "1234"}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/faculty/login"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
    std::cout << r.text << std::endl;
}

void studentUpload()
{
    json j2 = {{"filePath", "/Users/naveen/development/cpp-hackathon/sample.txt"}, {"usn", "12345"}};

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
    std::cout << r.text << std::endl;
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

    string usn1 = "12345";
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
    string usn = "12345";

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
}

void getScore()
{
    string usn = "12345";
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:3000/api/student/score/" + usn});
    cout << r.text;
}