#include <iostream>
#include <tuple>
#include "Message.h"
#include "DurationLogger.h"
#include "MessageStore.h"

void testMethods();
void testDefaultConstructor();
void testMyConstructor();
void testCopyConstructor();
void testMovementConstructor();
void testCopyOperator();
void testMovementOperator();
void questions();
void time();
void testMessageStore();
void testReallocation();

int main() {
    //testMethods();
    //questions();
    //time();

    //testMessageStore();
    //std::cout << "Numero istanze oggetti Messagge: " << Message::num_instances << std::endl;

    testReallocation();
    std::cout << "Numero istanze oggetti Messagge: " << Message::num_instances << std::endl;
    return 0;
}

void testMethods(){
    testDefaultConstructor();
    testMyConstructor();
    testCopyConstructor();
    testMovementConstructor();
    testCopyOperator();
    testMovementOperator();
}

void testDefaultConstructor() {
    std::cout << "=====testDefaultConstructor()=====" << std::endl;
    Message m;
    std::cout << "m: " << m << std::endl;
}

void testMyConstructor() {
    std::cout << "=====testMyConstructor()=====" << std::endl;
    Message m(10);
    std::cout << "m: " << m << std::endl;
}

void testCopyConstructor() {
    std::cout << "=====testCopyConstructor()=====" << std::endl;
    Message m1{10};
    Message m2{m1};
    std::cout << "m1: " << m1 << std::endl << "m2: " << m2 << std::endl;
}

void testMovementConstructor() {
    std::cout << "=====testMovementConstructor()=====" << std::endl;
    Message m1{10};
    Message m2 = std::move(m1);
    std::cout << "m1: " << m1 << std::endl << "m2: " << m2 << std::endl;
}

void testCopyOperator() {
    std::cout << "=====testCopyOperator()=====" << std::endl;
    Message m1(10);
    Message m2;
    m2 = m1;
    std::cout << m1 << std::endl << m2 << std::endl;
}

void testMovementOperator() {
    std::cout << "=====testMovementOperator()=====" << std::endl;
    Message m1(10);
    Message m2;
    m2 = std::move(m1);
    std::cout << m1 << std::endl << m2 << std::endl;
}

void questions() {
    std::cout << "=====questions()=====" << std::endl;

    // invoca costruttore vuoto in entrambi i casi
    Message buff1[10]; // crea oggetti nello stack
    Message *buff2 = new Message[10]; // crea oggetti nello heap
    delete[] buff2; // libera oggetti dallo heap
    // libera oggetti dallo stack automaticamente alla fine

    // se assegno un nuovo messaggio al primo elemento dell'array
    // 1) viene chiamato il costruttore di messaggio
    // 2) viene chiamato l'operatore di movimento
    // 3) la stringa destinazione viene deallocata e sostituita con quella nuova
    // 4) la stringa sorgente ora è nullprt
    // 5) al termine del programma tutti i messaggi sono distrutti
    buff1[0] = Message(100);

    // senza costruttore di default la compilazione fallisce
    // non posso creare un array di messaggi né nello stack né nello heap
    // mi vengono suggeriti metodi alternativi presenti nella classe
    // se rimuovo i tutti i costruttori il compilatore provvede a creare un costruttore di default
    // il compilatore fornisce un costruttore di default
    // solo se il programmatore non ha fornito NESSUN costruttore
    // La presenza di un costruttore scritto dal programmatore causa
    // la non generazione del costruttore di default da parte del compilatore

    // con costruttore di default privato la compilazione fallisce
    // non posso creare un array di messaggi né nello stack né nello heap
    // mi viene segnalato che il costruttore di default è privato

    // senza ridefinire gli operatori di movimento e copia l'esempio non funziona
    // se non sono stati definiti dal programmatore
    // 1) costruttori di copia
    // 2) costruttori di movimento
    // 3) operatori di assegnamento per copia
    // 4) distruttori
    // allora il compilatore dichiara il proprio operatore di assegnamento per movimento
    // senza operatore di movimento prova usa l'operatore di copia
}

void time() {
    DurationLogger dl("time()");
    std::cout << "=====time()=====" << std::endl;
    std::cout << "dimensione char: " << sizeof(char) << std::endl; // 1 char è 1 byte
    Message buff1[10];
    for(int i=0; i<10; i++){
        buff1[i] = std::move(Message(1024*1024));
    }
}

void testMessageStore() {
    std::cout << "=====testMessageStore()=====" << std::endl;
    std::cout << "1) Creo un oggetto MessageStore" << std::endl;
    MessageStore ms(2); // oggetto creato nello stack
    std::cout << "2) Creo oggetto Message da aggiungere" << std::endl;
    Message *m1 = new Message(5);
    std::cout << "3) Aggiungo un oggetto Message all'oggetto MessageStore" << std::endl;
    ms.add(*m1);
    std::cout << "4) Cancello oggetto Message aggiunto" << std::endl;
    delete m1;

    {
        std::cout << "5) Cerco oggetto Message nell'oggetto MessageStore" << std::endl;
        auto resOpt = ms.get(0); // ritorna una copia del messaggio nello stack
        if (resOpt) {
            std::cout << "Messaggio trovato: " << *resOpt << std::endl;
        } else {
            std::cout << "Messaggio non trovato!" << std::endl;
        }
    }

    std::cout << "6) Rimuovo oggetto Message dall'oggetto MessageStore" << std::endl;
    ms.remove(0);

    std::cout << "7) Analizzo lo stato del vettore interno a MessageStore" << std::endl;
    auto [ num_messages, num_spaces ] = ms.stats();
    std::cout << "Messaggi: " << num_messages << ", spazi: " << num_spaces << std::endl;

    std::cout << "8) Libero stack" << std::endl;
}

void testReallocation(){
    std::cout << "=====testReallocation()=====" << std::endl;

    MessageStore ms(100); // oggetto creato nello stack

    for(int i=0; i<100; i++){
        Message *m = new Message(1024*1024);
        ms.add(*m);
        delete m;
    }
    std::cout << "CARICAMENTO 100 MESSAGGI" << std::endl;
    auto [ num_messages, num_spaces ] = ms.stats();
    std::cout << "Messaggi: " << num_messages << ", spazi: " << num_spaces << std::endl;

    for(int i=0; i<100; i++){
        if(i%2 == 0){
            ms.remove(i);
        }
    }
    std::cout << "RIMOZIONE 50 MESSAGGI" << std::endl;
    auto statistics = ms.stats();
    std::cout << "Messaggi: " << std::get<0>(statistics) << ", spazi: " << std::get<1>(statistics) << std::endl;

    std::cout << "ORA COMPATTO I MESSAGGI" << std::endl;
    ms.compact();
}