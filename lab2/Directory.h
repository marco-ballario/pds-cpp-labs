#pragma once
#include <string>
#include <unordered_map>

class Directory {
private:
    static Directory *root;
    std::string name;
    Directory *father;
    std::unordered_map<std::string, Directory*> children;
public:
    Directory(std::string name, Directory *father);
    Directory(const Directory& source); // costruttore di copia
    Directory(Directory&& source); // costruttore di movimento
    ~Directory();
    //Directory& operator=(const Directory& source); // copia
    //Directory& operator=(Directory&& source); // movimento
    std::string getName() const; // se non mettessi const potrei modificare le proprietà con this

    static Directory* getRoot();
    Directory *addDirectory(const std::string &name);
    Directory *getDir(const std::string &name);
    bool remove(const std::string &name);
    bool move(const std::string &name, Directory *target);
    bool copy(const std::string &name, Directory *target);
    void ls(int indent);
};
