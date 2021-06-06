#include <iostream>
#include "Directory1.h"

long Count::count = 0;
Directory1 *Directory1::root = nullptr;

Directory1::Directory1(std::string name, Directory1 *father) {
    std::cout << "Creo: " << name << ", indirizzo: " << (void *)this << ", padre: " << (void *)father << std::endl;
    this->name = name;
    this->father = father;
    this->children.clear();
}

Directory1::~Directory1() {
    std::cout << "Distruggo: " << this->getName() << ", indirizzo: " << (void *)this << ", padre: " << (void *)father << std::endl;
    for( const auto& child : this->children ) {
        delete child.second;
    }
}

std::string Directory1::getName() const {
    return this->name;
}

Directory1 *Directory1::getRoot() {
    if (root == nullptr)
        root = new Directory1("/", nullptr);
    return root;
}

Directory1 *Directory1::addDirectory(const std::string &name) {
    if (this->children.count(name) != 0)
        return this->children[name];
    this->children[name] = new Directory1(name, this);
    return this->children[name];
}

Directory1 *Directory1::getDir(const std::string &name) {
    if(name.compare("..") == 0)
        return this->father;
    return this->children[name];
}

bool Directory1::remove(const std::string &name) {
    if (this->children.count(name) != 0) {
        delete this->children[name];
        this->children.erase(name);
        return true;
    } else {
        return false;
    }
}

bool Directory1::move(const std::string &name, Directory1 *target) {
    if (this->children.count(name) == 0)
        return false;
    if (target->children.count(name) != 0)
        return false;
    target->children[name] = this->children[name];
    target->children[name]->setFather(target);
    this->children.erase(name);
    return true;
}

bool Directory1::copy(const std::string &name, Directory1 *target) {
    if (this->children.count(name) == 0)
        return false;
    if (target->children.count(name) != 0)
        return false;
    target->addDirectory(name);
    return true;
}

void Directory1::ls(int indent) {
    std::cout << "[+] " << this->getName() << std::endl;
    for( const auto& child : this->children ) {
        for (int i=0; i<indent; i++)
            std::cout << " ";
        child.second->ls(indent+indent);
    }
}

void Directory1::setFather(Directory1 *f) {
    this->father = f;
}
