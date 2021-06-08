#pragma once
#include <map>
#include "Base2.h"
#include "File2.h"

class Directory2 : public Base2{
    static Directory2 *root;
    Directory2 *father;
    std::map<std::string, Base2*> children;
public:
    Directory2(std::string name, Directory2 *father);
    ~Directory2();
    void setFather(Directory2 *father);

    int mType() const override {
        return TDir2;
    }
    void ls(int indent) const override {
        std::cout << "[+] " << this->getName() << std::endl;
        for( const auto& child : this->children ) {
            for (int i=0; i<indent; i++)
                std::cout << " ";
            if(child.second->mType() == TDir2)
                child.second->ls(indent+indent);
            if(child.second->mType() == TFile2)
                child.second->ls(0);
        }
    };

    static Directory2* getRoot();
    Directory2* addDirectory(const std::string &name);
    File2* addFile(const std::string &name, uintmax_t size, uintmax_t date);
    Base2* get(const std::string &name);
    Directory2* getDirectory(const std::string &name);
    File2* getFile(const std::string &name);
    bool remove(const std::string &name);
    bool move(const std::string &name, Directory2 *target);
};