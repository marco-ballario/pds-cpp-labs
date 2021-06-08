#pragma once
#include <cstdint>
#include <iostream>

class File3 : public Base3{
    uintmax_t size;
public:
    File3(std::string myname, uintmax_t mysize) : size(mysize) {
        std::cout << "Creo: " << this->getName() << std::endl;
        this->name = myname;
    };

    ~File3() {
        std::cout << "Distruggo: " << this->getName() << std::endl;
    };

    uintmax_t getSize() const { return this->size; };

    int mType() const override {
        return TFile3;
    };
    void ls(int indent) const override {
        for(int i=0; i<indent; i++)
            std::cout << " ";
        std::cout << this->getName() << " " << this->getSize() << std::endl;
    };
};
