#pragma once
#include <iostream>
#include <string>

class Message {
private:
    static constexpr const bool debug = true;
    static long num;
    long id;
    char *data;
    int size;
    char* mkMessage(int n); // metodo privato
public:
    static long num_instances;
    //implementare qui quanto necessario per il suo funzionamento
    Message();
    Message(int n);
    Message(const Message& source); // costruttore di copia
    Message(Message&& source); // costruttore di movimento
    ~Message();
    Message& operator=(const Message& source); // copia
    Message& operator=(Message&& source); // movimento
    // se non mettessi const potrei modificare le proprietà con this
    long getId() const;
    char* getData() const;
    int getSize() const;
};

std::ostream& operator<<(std::ostream& out, const Message& m);
