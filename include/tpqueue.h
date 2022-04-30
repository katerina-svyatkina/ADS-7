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
    TPQueue(const T& value) {
        head = tail = create(value);
        current = nullptr;
    }
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
            while (current->prev && current->value.prior < value.prior) {
                current = current->prev;
            }
            ITEM* tmp_prev = current->prev;
            current->prev = temp;
            temp->next = current;
            if (tmp_prev) {
                temp->prev = tmp_prev;
                tmp_prev->next = temp;
            } else {
                head = temp;
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
