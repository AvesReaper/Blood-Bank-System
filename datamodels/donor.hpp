#pragma once

#include <string>
#include <stdlib.h>
#include "../datastructures/date.hpp"

using namespace std;

class Donor
{
public:
    std::string name, type;
    unsigned int age, id;
    char antigen;
    long long phoneNo;
    Date lastDontationDate;

    Donor()
    {
        this->age = 0;
        this->id = 0;
        this->antigen = '+';
        this->phoneNo = 12345;
    }

    Donor(std::string name, unsigned int age, std::string type, char anti, long long phno)
    {
        this->name = name;
        this->age = age;
        this->type = type;
        this->antigen = anti;
        this->phoneNo = phno;

        this->id = rand() % 10000; // id not guarenteed to be non-colliding
    }

    Donor(std::string s)
    {
        this->name = s.substr(0, s.find(" "));
        s.erase(0, s.find(" ") + 1);

        this->age = std::stoi(s.substr(0, s.find(" ")));
        s.erase(0, s.find(" ") + 1);

        this->type = s.substr(0, s.find(" "));
        s.erase(0, s.find(" ") + 1);

        this->antigen = s.substr(0, s.find(" ")).c_str()[0];
        s.erase(0, s.find(" ") + 1);

        this->phoneNo = std::stol(s.substr(0, s.find(" ")));
        s.erase(0, s.find(" ") + 1);

        this->id = std::stoi(s.substr(0, s.find(" ")));
        s.erase(0, s.find(" ") + 1);

        this->lastDontationDate = Date(s.substr(0, s.find(" ")));
        s.erase(0, s.find(" ") + 1);
    }

    string Serialize()
    {
        string s = name + " " + to_string(age) + " " + type + " " + antigen + " " + to_string(phoneNo) + " " + to_string(id) + " " + string(lastDontationDate);
        return s;
    }
};
