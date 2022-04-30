// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>

template<typename T>
class TPQueue {
 private:
    struct ITEM {
        T value;
        ITEM* next;
        ITEM* prev;
    };
    ITEM* head, * tail, * current;
    TPQueue::ITEM* create(const T& value) {
        ITEM* item = new ITEM;
        item->value = value;
        item->next = nullptr;
        item->prev = nullptr;
        return item;
    }
    T rmHead() {
        if (head) {
            ITEM* temp = head->next;
            if (temp)
                temp->prev = nullptr;
            T value = head->value;
            delete head;
            head = temp;
            return value;
        } else {
            throw std::string("Empty!");
        }
    }
 
 public:
    TPQueue() : head(nullptr), tail(nullptr), current(nullptr) {}
    ~TPQueue() {
        while (head)
            rmHead();
    }
    bool isEmpty() const {
        return !head;
    }
    void push(const T& value) {
        ITEM* temp = create(value);
        if (isEmpty()) {
            head = tail = temp;
        } else {
            current = tail;
            while (current && current->value.prior < value.prior) {
                current = current->prev;
            }
            if (!current) { // вставка перед
                head->prev = temp;
                temp->next = head;
                head = temp;
            } else { // вставка после
                ITEM* tmp_next = current->next;
                current->next = temp;
                temp->prev = current;
                if (tmp_next) {
                    temp->next = tmp_next;
                    tmp_next->prev = temp;
                } else {
                    tail = temp;
                }
            }
        }
    }
    T pop() {
        return rmHead();
    }
};

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
