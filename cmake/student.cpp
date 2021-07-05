#include "student.h"
#include "utill.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include<string.h>

using json = nlohmann::json;
using namespace std;
using namespace student;

void Student::loadStartupMenu()
{
    cout<<"1. Log in"<<endl<<"2. Register"<<endl;

    int ch;
    cout<<"Enter your choice"<<endl;
    cin>>ch;
    utill::clearScr();
    (ch==1)?login():signup();
    
};

void Student::login()
{
    //Test Data
    string usn,password;
    cout<<"\nEnter USN : "<<endl;
    cin>>usn;
    cout<<"Enter Password: "<<endl;
    cin>>password;
    
    json j2 = {
        {"usn", usn},
        {"password", password}};

    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url{"http://localhost:3000/api/student/login"},
                                           cpr::Body{j2.dump()},
                                           cpr::Header{{"Content-Type", "application/json"}});

    fr.wait();
    cpr::Response r = fr.get();
   
    // std::cout << r.text << std::endl;
    if(r.status_code==400){
        utill::clearScr();
        json res = json::parse(r.text);
        std::string msg = res.value("text", "oops");
        cout<<msg<<endl;
        loadStartupMenu();
    } else if(r.status_code==0){
        cout<<"Server Error"<<endl;
        loadStartupMenu();
    }
}

void Student::signup()
{
    cout<<"Register user!"<<endl;

}