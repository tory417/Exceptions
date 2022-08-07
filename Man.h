#include <iostream>
using namespace std;
#pragma once
class Man {
    string name;
public:
    Man(string name) {
        this->name = name;
    }
    friend ostream& operator<<(ostream& out, Man& man) {
        out << man.name;
        return out;
    }
};

