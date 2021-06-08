#include <iostream>
#include <string>
#include <filesystem>
#include "Directory1.h"
#include "Directory2.h"
#include "Directory3.h"

namespace fs = std::filesystem;

Directory2 *Directory2::root = nullptr;
std::shared_ptr<Directory3> Directory3::root = nullptr;

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

void part1();
void simpleExample1();
void complexExample1();
void part2();
void simpleExample2();
void complexExample2();
void part3();

int main() {

    //part1();
    //part2();
    part3();

    return 0;
}

void part1(){
    //simpleExample1();
    complexExample1();
}

void part2(){
    //simpleExample2();
    complexExample2();
}

void part3(){
    shared_ptr<Directory3> root = Directory3::getRoot();
    auto alfa = root->addDirectory("alfa");
    root->addDirectory("beta")->addDirectory("beta1");
    root->getDirectory("beta")->addDirectory("beta2");
    alfa->getDirectory("..")->ls(4);

    cout<<"----"<<endl;

    root->remove("beta");
    root->ls(4);
}

void simpleExample1() {
    Directory1* root = Directory1::getRoot();
    auto alfa = root->addDirectory("alfa");
    root->addDirectory("beta")->addDirectory("beta1");
    root->getDir("beta")->addDirectory("beta2");
    alfa->getDir("..")->ls(4);
    root->remove("beta");
    root->ls(4);
    delete root;
}

void complexExample1() {
    Directory1* root = Directory1::getRoot();
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

    delete root;
}


void simpleExample2() {
    Directory2* root = Directory2::getRoot();
    auto alfa = root->addDirectory("alfa");
    root->addDirectory("beta")->addDirectory("beta1");
    root->getDirectory("beta")->addDirectory("beta2");
    alfa->getDirectory("..")->ls(4);
    root->remove("beta");
    alfa->addFile("gamma",1024,1024);
    alfa->addFile("epsilon",1024,1024);
    alfa->addFile("sigma",1024,1024);
    root->ls(4);
    delete root;
}

// TO DO (non così importante)
// manca la gestione di sottocartelle del filesystem reale
// per ora si considera un solo livello di directory_entry
void complexExample2() {

    Directory2* root = Directory2::getRoot();

    std::string path = "/home/marco-ballario/Scrivania/";
    for (const auto & entry : fs::recursive_directory_iterator(path)) {
        std::cout << entry.path().parent_path().filename() << " contiene " << entry.path().filename() << std::endl;
        if (entry.is_directory() == true) {
            root->addDirectory(entry.path().filename());
        } else {
            auto time = static_cast<uintmax_t>(last_write_time(entry.path()).time_since_epoch().count());
            root->addFile(entry.path().filename(), file_size(entry.path()), time);
        }
    }

    root->ls(4);
    delete root;
}