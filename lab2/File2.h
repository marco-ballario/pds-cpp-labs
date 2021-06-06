#pragma once
#include <cstdint>
#include <iostream>

class File2 : public Base2{
    uintmax_t size, date;
public:
    File2(std::string myname, uintmax_t mysize, uintmax_t mydate) : size(mysize), date(mydate){
        this->name = myname;
    };
    ~File2() {
        std::cout << "Distruggo: " << this->getName() << ", indirizzo: " << (void *)this << std::endl;
    }

    uintmax_t getSize() const { return this->size; };
    uintmax_t getDate() const { return this->date; };

    int mType() const override {
        return TFile;
    };
    void ls(int indent) const override {
        for(int i=0; i<indent; i++)
            std::cout << " ";
        std::cout << this->getName() << " " << this->getSize() << std::endl;
    };
};
