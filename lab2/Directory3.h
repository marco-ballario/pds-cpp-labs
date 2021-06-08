#pragma once
#include <memory>
#include <map>
#include "Base3.h"
#include "File3.h"
using namespace std;

class Directory3 : public Base3{
private:
    static std::shared_ptr<Directory3> root;
    std::weak_ptr<Directory3> self;
    std::weak_ptr<Directory3> parent;
    std::map<std::string, std::shared_ptr<Base3>> children;

    Directory3(std::string name){
        cout << "Creo " << name << endl;
        this->name = name;
    };

    static shared_ptr<Directory3> make(string name, weak_ptr<Directory3> parent){
        shared_ptr<Directory3> d = shared_ptr<Directory3>(new Directory3(name));
        d->self = d;
        d->parent = parent.lock() != nullptr ? parent : d;
        return d;
    }

public:

    ~Directory3(){
        std::cout << "Distruggo " << this->name << std::endl;
    }

    int mType() const override {
        return TDir3;
    }

    void ls(int indent) const override {
        std::cout << "[+] " << this->getName() << std::endl;
        for( const auto& child : this->children ) {
            for (int i=0; i<indent; i++)
                std::cout << " ";
            if(child.second->mType() == TDir3)
                child.second->ls(indent+indent);
            if(child.second->mType() == TFile3)
                child.second->ls(0);
        }
    };

    static std::shared_ptr<Directory3> getRoot(){
        if(root == nullptr) {
            root = make("/", shared_ptr<Directory3>(nullptr));
        }
        return root;
    };

    std::shared_ptr<Directory3> addDirectory(const std::string& name){
        shared_ptr<Directory3> d = make(name, self);
        children[name] = d;
        return d;
    };

    std::shared_ptr<File3> addFile(const std::string& name, uintmax_t size){
        shared_ptr<File3> f = make_shared<File3>(name, size);
        children[name] = f;
        return f;
    };

    std::shared_ptr<Base3> get(const std::string& name){
        if(name == "."){
            return this->self.lock();
        }
        if(name == ".."){
            return this->parent.lock();
        }
        if(children.count(name) != 0){
            return children[name];
        }
        return shared_ptr<Base3>(nullptr);
    };

    std::shared_ptr<Directory3> getDirectory(const std::string& name){
        shared_ptr<Base3> dir = this->get(name);
        if(dir == nullptr || dir->mType() != TDir3){
            return shared_ptr<Directory3>(nullptr);
        } else {
            return dynamic_pointer_cast<Directory3>(dir);
        }
    };

    std::shared_ptr<File3> getFile(const std::string& name){
        shared_ptr<Base3> file = this->get(name);
        if(file == nullptr || file->mType() != TFile3){
            return shared_ptr<File3>(nullptr);
        } else {
            return dynamic_pointer_cast<File3>(file);
        }
    };

    bool remove(const std::string& name){
        shared_ptr<Base3> target = this->get(name);
        if(target != nullptr) {
            this->children.erase(target->getName());
            return true;
        }
        return false;
    };
    /*
    bool move(const std::string& name, std::shared_ptr<Directory3> dest){

    };

    bool copy(const std::string& name, std::shared_ptr<Directory3> dest){

    };
    */

};





