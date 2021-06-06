#pragma once
#include <string>
#include <map>

class Count {
    static long count;
public:
    inline Count() { std::cout << "Count(): " << ++this->count << std::endl; };
    inline ~Count() { std::cout << "~Count(): " << --this->count << std::endl; };
};

class Directory : public Count{
private:
    static Directory *root;
    std::string name;
    Directory *father;
    std::map<std::string, Directory*> children;
public:
    Directory(std::string name, Directory *father);
    Directory(const Directory& source); // costruttore di copia
    Directory(Directory&& source); // costruttore di movimento
    ~Directory();
    //Directory& operator=(const Directory& source); // copia
    //Directory& operator=(Directory&& source); // movimento
    std::string getName() const; // se non mettessi const potrei modificare le proprietà con this
    void setFather(Directory *father);

    static Directory* getRoot();
    Directory *addDirectory(const std::string &name);
    Directory *getDir(const std::string &name);
    bool remove(const std::string &name);
    bool move(const std::string &name, Directory *target);
    bool copy(const std::string &name, Directory *target);
    void ls(int indent);
};

// *addDirectory(Directory *child)
// viene passata una copia dell'indirizzo (può essere nullptr)
// la funzione può modificare l'oggetto puntato da child
// *addDirectory(Directory &target)
// viene passata una copia dell'indirizzo (non può essere nullptr)
// la funzione può modificare l'oggetto puntato da child