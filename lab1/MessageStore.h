#pragma once
#include <optional>
#include "Message.h"

class MessageStore {
    Message *messages;
    int dim; // dimensione corrente array
    int n; // incremento memoria
    int num_msg;
public:
    MessageStore(int n);
    ~MessageStore();
    void add(Message &m);
    std::optional<Message> get(long id);
    bool remove(long id);
    std::tuple<int, int> stats();
    void compact();
};
