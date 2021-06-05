#include "Message.h"

long Message::num = 0;
long Message::num_instances = 0;

char* Message::mkMessage(int n) {
    if constexpr(debug) std::cout << "Message::mkMessage(int n)";
    std::string vowels = "aeiou";
    std::string consonants = "bcdfghlmnpqrstvz";
    char* m = new char[n+1];
    if constexpr(debug) std::cout << " -> new "<< (void *)m << std::endl;
    for(int i=0; i<n; i++){
        m[i]= i%2 ? vowels[rand()%vowels.size()] : consonants[rand()%consonants.size()];
    }
    m[n] = 0 ;
    return m;
}

Message::Message() {
    if constexpr(debug) std::cout << "Message::Message()" << std::endl;
    this->id = -1;
    this->data = mkMessage(0);
    this->size = 0;
    this->num_instances++;
}

Message::Message(int n) {
    if constexpr(debug) std::cout << "Message::Message(int n)" << std::endl;
    this->id = num++;
    this->data = mkMessage(n);
    this->size = n;
    this->num_instances++;
}

Message::Message(const Message& source){
    if constexpr(debug) std::cout << "Message::Message(const Message& source)";
    this->id = source.id;
    this->size = source.size;
    this->data = new char[size];
    if constexpr(debug) std::cout << " -> new "<< (void *)this->data << std::endl;
    std::copy(source.data, source.data+this->size, this->data);
    this->num_instances++;
}

Message::Message(Message&& source) {
    if constexpr(debug) std::cout << "Message::Message(Message&& source)" << std::endl;
    this->id = source.id;
    this->size = source.size;
    this->data = source.data;
    source.data = nullptr;
    this->num_instances++;
}

Message::~Message() {
    if constexpr(debug) std::cout << "Message::~Message() -> delete "<< (void *)data << std::endl;
    delete[] data;
    this->num_instances--;
}

Message& Message::operator=(const Message& source) {
    if constexpr(debug) std::cout << "Message::copy";
    if(this!=&source) {
        if constexpr(debug) std::cout << " -> delete " << (void *)this->data;
        delete [] this->data;
        this->data = nullptr;
        this->id = source.id;
        this->size = source.size;
        this->data = new char[size];
        if constexpr(debug) std::cout << " -> new " << (void *)this->data << std::endl;
        std::copy(source.data, source.data+size, this->data);
    }
    return  *this;
}

Message& Message::operator=(Message&& source) {
    if constexpr(debug) std::cout << "Message::movement";
    if(this!=&source) {
        if constexpr(debug) std::cout << " -> delete " << (void *)this->data << std::endl;
        delete[] this->data;
        this->id = source.id;
        this->size = source.size;
        this->data = source.data;
        source.data = nullptr;
    }
    return  *this;
}

long Message::getId() const {
    return this->id;
};

char* Message::getData() const {
    return this->data;
};

int Message::getSize() const {
    return this->size;
};

std::ostream& operator<<(std::ostream& out, const Message& m){
    // accedere alle parti contenute nell’oggetto Message e
    // stamparle utilizzando out << ... ;
    // Questa funzione DEVE restituire l’oggetto out
    out << "[id:" << m.getId() <<"][size:" << m.getSize()
        << "][data address:" << (void *)m.getData()
        << "][data:" << (m.getData()!=nullptr ? m.getData() : "") << "]";
    return out;
}