#include <iostream>
#include "Directory.h"

// ESEMPIO EREDITARIETÀ
/*
class Alfa {
public:
    inline Alfa(){ std::cout << "Alfa()" << std::endl; };
    inline ~Alfa(){ std::cout << "~Alfa()" << std::endl; };
};

class Beta : public Alfa{
public:
    inline Beta() { std::cout << "Beta()" << std::endl; };
    inline ~Beta() { std::cout << "~Beta()" << std::endl; };
};
*/

void simpleExample();
void complexExample();

int main() {

    //simpleExample();
    complexExample();


    return 0;
}

void simpleExample() {
    Directory* root = Directory::getRoot();
    auto alfa = root->addDirectory("alfa");
    root->addDirectory("beta")->addDirectory("beta1");
    root->getDir("beta")->addDirectory("beta2");
    alfa->getDir("..")->ls(4);
    root->remove("beta");
    root->ls(4);
    delete root;
}

void complexExample() {
    Directory* root = Directory::getRoot();
    auto alfa = root->addDirectory("alfa");
    root->addDirectory("beta")->addDirectory("beta1");
    root->getDir("beta")->addDirectory("beta2");
    root->ls(4);

    // copy
    std::cout << "COPY" <<std::endl;
    root->getDir("beta")->copy("beta1", root->getDir("alfa"));
    root->ls(4);

    // move
    std::cout << "MOVE" <<std::endl;
    root->getDir("beta")->move("beta2", root->getDir("alfa"));
    root->ls(4);
}