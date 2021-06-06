#pragma once
#include <string>
#include <map>

class Count {
    static long count;
public:
    inline Count() { std::cout << "Count(): " << ++this->count << std::endl; };
    inline ~Count() { std::cout << "~Count(): " << --this->count << std::endl; };
};

class Directory1 : public Count{
private:
    static Directory1 *root;
    std::string name;
    Directory1 *father;
    std::map<std::string, Directory1*> children;
public:
    Directory1(std::string name, Directory1 *father);
    ~Directory1();
    std::string getName() const; // se non mettessi const potrei modificare le proprietà con this
    void setFather(Directory1 *father);

    static Directory1* getRoot();
    Directory1 *addDirectory(const std::string &name);
    Directory1 *getDir(const std::string &name);
    bool remove(const std::string &name);
    bool move(const std::string &name, Directory1 *target);
    bool copy(const std::string &name, Directory1 *target);
    void ls(int indent);
};

// *addDirectory(Directory1 *child)
// viene passata una copia dell'indirizzo (può essere nullptr)
// la funzione può modificare l'oggetto puntato da child
// *addDirectory(Directory1 &target)
// viene passata una copia dell'indirizzo (non può essere nullptr)
// la funzione può modificare l'oggetto puntato da child
