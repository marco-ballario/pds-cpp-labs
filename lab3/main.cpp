#include <iostream>
#include <memory>
#include <list>

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
    void doMyThing(){ std::cout << "YEET!" << std::endl; }
};

class TipoGenerico {
    uint count;
public:
    TipoGenerico(): count(0){};
    uint getCount() { return count; };
    void incCount() { count++; };
    void decCount() { count--; };
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
        ref = sp.ref;
        counter = sp.counter;
        counter->incCount();
    };
    ~my_shared(){
        if(ref != nullptr && counter != nullptr) {
            counter->decCount();
            if (this->use_count() == 0) {
                delete counter;
                delete ref;
            }
        }
    };
    T* operator->(){
        return ref;
    }
    T& operator*(){
        return *ref;
    }
    my_shared<T> &operator=(const my_shared<T> &other){
        std::cout << "copy = operator" << std::endl;
        if(this != &other) {
            if (ref != other.ref) {
                counter->decCount();
                if (this->use_count() == 0) {
                    delete ref;
                    delete counter;
                }
                ref = other.ref;
                counter = other.counter;
                counter->incCount();
            }
        }
        return *this;
    }
    my_shared<T> &operator=(my_shared<T> &&other){
        std::cout << "movement = operator" << std::endl;
        if(this != &other) {
            if (ref != other.ref) {
                counter->decCount();
                if (this->use_count() == 0) {
                    delete ref;
                    delete counter;
                }
                ref = other.ref;
                counter = other.counter;
                other.counter = nullptr;
                other.ref = nullptr;
            }
        }
        return *this;
    }
    uint use_count(){
        return counter == nullptr ? 0 : counter->getCount();
    }
};

// ES 3

class Process {
    std::string name;
    int pid, ppid, time;
    std::list<std::string> opened_files;
    std::list<std::string> mapped_files;

    Process(std::string name) {
        this->name = name;
        this->pid = pid;
        this->ppid = ppid;
        this->time = time;
    }
public:
    static void makeProcess(std::string name, std::weak_ptr<Process> ) {

    }


};

void es1();
void es2();
void es3();

int main() {
    std::cout << "ES 1" << std::endl;
    es1();
    std::cout << "ES 2" << std::endl;
    es2();
    std::cout << "ES 3" << std::endl;
    es3();
    return 0;
}

void es1(){
    Tracked1 t1;
    Tracked2 t2;
}

void es2(){

    // test constructors and operators
    my_shared<MyClass> msp1 = my_shared<MyClass>(new MyClass());
    my_shared<MyClass> msp2 = my_shared<MyClass>(msp1);
    std::cout << msp2.use_count() << std::endl;
    msp1->doMyThing();
    (*msp2).doMyThing();

    // test copy = operator
    my_shared<MyClass> msp3 = my_shared<MyClass>(new MyClass());
    my_shared<MyClass> msp4 = my_shared<MyClass>(new MyClass());
    std::cout << msp3.use_count() << std::endl;
    std::cout << msp4.use_count() << std::endl;
    msp3 = msp4;
    std::cout << msp3.use_count() << std::endl;
    std::cout << msp4.use_count() << std::endl;

    // test = movement operator
    my_shared<MyClass> msp5 = my_shared<MyClass>(new MyClass());
    my_shared<MyClass> msp6 = my_shared<MyClass>(new MyClass());
    my_shared<MyClass> msp7 = my_shared<MyClass>(msp6);
    std::cout << msp5.use_count() << std::endl;
    std::cout << msp6.use_count() << std::endl;
    std::cout << msp7.use_count() << std::endl;
    msp5 = std::move(msp6);
    std::cout << msp5.use_count() << std::endl;
    std::cout << msp6.use_count() << std::endl;
    std::cout << msp7.use_count() << std::endl;

    /* BAD CODE *//*
    MyClass *mc = new MyClass();
    std::shared_ptr<MyClass> sp1 = std::shared_ptr<MyClass>(mc);
    std::shared_ptr<MyClass> sp2 = std::shared_ptr<MyClass>(mc);
    std::cout << sp1.use_count() << std::endl;
    std::cout << sp2.use_count() << std::endl;*/

    /* TEST COPY ASSIGNMENT OPERATOR *//*
    std::shared_ptr<MyClass> sp1 = std::shared_ptr<MyClass>(new MyClass());
    std::shared_ptr<MyClass> sp2 = std::shared_ptr<MyClass>(new MyClass());
    std::cout << sp1.use_count() << std::endl;
    std::cout << sp2.use_count() << std::endl;
    sp1 = sp2;
    std::cout << sp1.use_count() << std::endl;
    std::cout << sp2.use_count() << std::endl;*/

    /* TEST MOVEMENT ASSIGNMENT OPERATOR *//*
    std::shared_ptr<MyClass> sp3 = std::shared_ptr<MyClass>(new MyClass());
    std::shared_ptr<MyClass> sp4 = std::shared_ptr<MyClass>(new MyClass());
    std::shared_ptr<MyClass> sp5 = std::shared_ptr<MyClass>(sp4);
    std::cout << sp3.use_count() << std::endl;
    std::cout << sp4.use_count() << std::endl;
    std::cout << sp5.use_count() << std::endl;
    sp3 = std::move(sp4);
    std::cout << sp3.use_count() << std::endl;
    std::cout << sp4.use_count() << std::endl;
    std::cout << sp5.use_count() << std::endl;*/

}

void es3() {
    std::list<Process*> lp;
    Process *p1 = new Process("p1",42,0,999);
    Process *p2 = new Process("p2",420,42,999);
    lp.push_back(p1);
    lp.push_back(p2);


}
