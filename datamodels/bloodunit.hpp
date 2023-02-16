#pragma once

#include <string>
#include "../datastructures/date.hpp"

using namespace std;

// info about type and antigen are contained in the context
// (which collection bloodunit was included in)
class BloodUnit
{
public:
    unsigned int donorId;
    Date donationDate;

    BloodUnit() {}

    BloodUnit(std::string s)
    {
        this->donorId = std::stoi(s.substr(0, s.find(" ")));
        s.erase(0, s.find(" ") + 1);

        this->donationDate = Date(s.substr(0, s.find(" ")));
        s.erase(0, s.find(" ") + 1);
    }

    string Serialize()
    {
        string s = std::to_string(donorId) + " " + string(donationDate);
        return s;
    }
};
