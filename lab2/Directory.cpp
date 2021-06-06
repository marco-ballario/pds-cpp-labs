#include <iostream>
#include "Directory.h"

long Count::count = 0;
Directory *Directory::root = nullptr;

Directory::Directory(std::string name, Directory *father) {
    std::cout << "Creo: " << name << ", indirizzo: " << (void *)this << ", padre: " << (void *)father << std::endl;
    this->name = name;
    this->father = father;
    this->children.clear();
}

Directory::Directory(const Directory &source) {

}

Directory::Directory(Directory &&source) {

}

Directory::~Directory() {
    std::cout << "Distruggo: " << this->getName() << ", indirizzo: " << (void *)this << ", padre: " << (void *)father << std::endl;
    for( const auto& child : this->children ) {
        delete child.second;
    }
}
/*
Directory &Directory::operator=(const Directory &source) {
    return <#initializer#>;
}

Directory &Directory::operator=(Directory &&source) {
    return <#initializer#>;
}
*/
std::string Directory::getName() const {
    return this->name;
}

Directory *Directory::getRoot() {
    if (root == nullptr)
        root = new Directory("/", nullptr);
    return root;
}

Directory *Directory::addDirectory(const std::string &name) {
    if (this->children.count(name) != 0)
        return this->children[name];
    this->children[name] = new Directory(name, this);
    return this->children[name];
}

Directory *Directory::getDir(const std::string &name) {
    if(name.compare("..") == 0)
        return this->father;
    return this->children[name];
}

bool Directory::remove(const std::string &name) {
    if (this->children.count(name) != 0) {
        delete this->children[name];
        this->children.erase(name);
        return true;
    } else {
        return false;
    }
}

bool Directory::move(const std::string &name, Directory *target) {
    if (this->children.count(name) == 0)
        return false;
    if (target->children.count(name) != 0)
        return false;
    target->children[name] = this->children[name];
    target->children[name]->setFather(target);
    this->children.erase(name);
    return true;
}

bool Directory::copy(const std::string &name, Directory *target) {
    if (this->children.count(name) == 0)
        return false;
    if (target->children.count(name) != 0)
        return false;
    target->addDirectory(name);
    return true;
}

void Directory::ls(int indent) {
    std::cout << "[+] " << this->getName() << std::endl;
    for( const auto& child : this->children ) {
        for (int i=0; i<indent; i++)
            std::cout << " ";
        child.second->ls(indent+indent);
    }
}

void Directory::setFather(Directory *f) {
    this->father = f;
}


