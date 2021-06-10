#include <iostream>

// ES 1

template <class T>
class Tracker {
    friend T;
    static u_int count;
    Tracker(){ std::cout << ++count << std::endl; };
public:
    ~Tracker(){ std::cout << --count << std::endl; };
};

template <class T>
u_int Tracker<T>::count = 0;

class Tracked1 : public Tracker<Tracked1> {

};
class Tracked2 : public Tracker<Tracked2> {

};

// ES 2

class MyClass {
public:
    MyClass(){ std::cout << "MyClass" << std::endl; };
    ~MyClass(){ std::cout << "~MyClass" << std::endl; };
};

class TipoGenerico {
    uint count;
public:
    TipoGenerico(): count(0){};
    uint getCount() { return count; };
    void incCount() { count++; };
};

template <class T>
class my_shared {
    T *ref;
    TipoGenerico* counter;
public:
    my_shared(T *p){
        ref = p;
        counter = new TipoGenerico();
        counter->incCount();
    }
    my_shared(const my_shared<T> &sp){

    };
    ~my_shared(){
        if(this->use_count() == 1){
            this->counter = 0;
            delete counter;
            delete ref;
        }
    };
    T* operator->(){
        return *ref;
    }
    T& operator*(){
        return ref;
    }
    my_shared<T> &operator=(const my_shared<T> &other){
        ref = *other;
        counter = other.getCounter();
    }
    my_shared<T> &operator=(my_shared<T> &&other){

    }
    uint use_count(){
        return counter->getCount();
    }
    TipoGenerico* getCounter(){
        return counter;
    }

};

void es1();
void es2();

int main() {
    std::cout << "ES 1" << std::endl;
    es1();
    std::cout << "ES 2" << std::endl;
    es2();


    return 0;
}

void es1(){
    Tracked1 t1;
    Tracked2 t2;
}

void es2(){
    my_shared<MyClass> ms1 = my_shared<MyClass>(new MyClass());
    //my_shared<MyClass> ms2 = my_shared<MyClass>(ms1);

}
