#include <iostream>
#include "Directory2.h"

Directory2::Directory2(std::string name, Directory2 *father) {
    std::cout << "Creo: " << name << ", indirizzo: " << (void *)this << ", padre: " << (void *)father << std::endl;
    this->name = name;
    this->father = father;
    this->children.clear();
}

Directory2::~Directory2() {
    std::cout << "Distruggo: " << this->getName() << ", indirizzo: " << (void *)this << ", padre: " << (void *)father << std::endl;
    for( const auto& child : this->children ) {
        if (child.second->mType() == TDir2)
            delete dynamic_cast<Directory2*>(child.second);
        else if (child.second->mType() == TFile2)
            delete dynamic_cast<File2*>(child.second);
    }
}

Directory2* Directory2::getRoot() {
    if (root == nullptr)
        root = new Directory2("/", nullptr);
    return root;
}

Directory2* Directory2::addDirectory(const std::string &name) {
    if (this->children.count(name) != 0){
        if (this->children[name]->mType() == TDir2)
            return dynamic_cast<Directory2*>(this->children[name]);
        if (this->children[name]->mType() == TFile2)
            return nullptr;
    }
    this->children[name] = new Directory2(name, this);
    return dynamic_cast<Directory2*>(this->children[name]);

}

File2* Directory2::addFile(const std::string &name, uintmax_t size, uintmax_t date) {
    if (this->children.count(name) != 0)
        return nullptr;
    this->children[name] = new File2(name, size, date);
    return dynamic_cast<File2*>(this->children[name]);
}

Base2* Directory2::get(const std::string &name){
    if(name.compare("..") == 0)
        return this->father;
    return this->children[name];
}

Directory2* Directory2::getDirectory(const std::string &name) {
    if(name.compare("..") == 0)
        return dynamic_cast<Directory2*>(this->father);
    return dynamic_cast<Directory2*>(this->children[name]);
}

File2* Directory2::getFile(const std::string &name) {
    return dynamic_cast<File2*>(this->children[name]);
}

bool Directory2::remove(const std::string &name) {
    if (this->children.count(name) != 0) {
        delete this->children[name];
        this->children.erase(name);
        return true;
    } else {
        return false;
    }
}

bool Directory2::move(const std::string &name, Directory2 *target) {
    if (this->children.count(name) == 0)
        return false;
    if (target->children.count(name) != 0)
        return false;
    target->children[name] = this->children[name];
    dynamic_cast<Directory2*>(target->children[name])->setFather(target);
    this->children.erase(name);
    return true;
}

void Directory2::setFather(Directory2 *f) {
    this->father = f;
}
