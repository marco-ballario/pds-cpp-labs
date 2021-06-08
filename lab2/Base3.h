#pragma once
#include <iostream>

enum MType3 {
    TDir3=0, TFile3=1
};

class Base3 {
protected:
    std::string name;
public:
    std::string getName() const { return this->name; };
    virtual int mType() const = 0;
    virtual void ls(int indent) const = 0;
};
