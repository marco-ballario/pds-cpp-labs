#include <optional>
#include <tuple>
#include "MessageStore.h"

MessageStore::MessageStore(int n) {
    this->dim = n;
    this->n = 10;
    this->num_msg = 0;
    this->messages = new Message[dim];
}

MessageStore::~MessageStore(){
    delete[] this->messages;
}

// inserisce un nuovo messaggio o sovrascrive quello precedente
// se ce n’è uno presente con lo stesso id
void MessageStore::add(Message &m){
    if (m.getId() !=-1) {
        for(int i=0; i<this->dim; i++){
            // messaggio non ancora presente viene inserito in coda
            if(this->messages[i].getId() == -1) {
                this->messages[i] = std::move(m);
                this->num_msg++;
                break;
            }
            // messaggio già presente viene sovrascritto
            if(this->messages[i].getId() == m.getId()) {
                this->messages[i] = std::move(m);
                break;
            }
        }
    }
}

// restituisce un messaggio se presente
std::optional<Message> MessageStore::get(long id){
    for(int i=0; i<this->dim; i++)
        if(this->messages[i].getId() == id)
            return this->messages[i];
    return std::nullopt; // oppure {}
}

// cancella un messaggio se presente
bool MessageStore::remove(long id) {
    for (int i=0; i<this->dim; i++) {
        if (this->messages[i].getId() == id) {
            Message *m = new Message();
            this->messages[i] = std::move(*m);
            delete m;
            this->num_msg--;
            return true;
        }
    }
    return false;
}


// restituisce il numero di messaggi validi e di elementi vuoti
// ancora disponibili
std::tuple<int, int> MessageStore::stats() {
    return std::tuple<int, int>{this->num_msg, this->dim - this->num_msg};
}

// compatta l’array (elimina le celle vuole e riporta l’array
// alla dimensione multiplo di n minima in grado di contenere
// tutte le celle
void MessageStore::compact() {

    Message *newVet;
    if(this->num_msg == this->dim){
        newVet = new Message[this->dim + this->n];
    }else{
        newVet = new Message[this->dim];
    }

    int n = 0;
    for(int i=0; i<this->dim; i++){
        if(this->messages[i].getId() != -1){
            newVet[n] = std::move(this->messages[i]);
        }
    }
    delete[] this->messages;
    this->messages = std::move(newVet);
}
