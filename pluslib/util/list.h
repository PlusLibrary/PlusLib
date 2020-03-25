#pragma once

#include <stdlib.h>

template<class T>
class Element {
    public:
        Element(T* t) {
            this->data = t;
            this->next = NULL;
        }
        Element<T>* next;
        T* data;
};

template <class T>
class List {
    public:
        List() {
            this->elementCount = 0;
            this->dummy = new Element<T>(NULL);
            this->last = dummy;
        }

        ~List() {
            Element<T>* pointer = dummy;
            do {
                Element<T>* temp = pointer;
                pointer = pointer->next;
                delete(temp->data);
                delete(temp);
            } while (pointer);
        }

        void add(T* t) {
            Element<T>* pointer = dummy;
            last->next = new Element<T>(t);
            last = last->next;
            elementCount++;
        }

        int size() {
            return elementCount;
        }
        
        T* get(int index) {
            Element<T>* pointer = dummy->next;
            for (int i = 0; i < index; i++) {
                pointer = pointer->next;
            }
            return pointer->data;
        }

        void forEach(void (*callback) (T*)) {
            Element<T>* pointer = dummy;
            while (pointer->next) {
                pointer = pointer->next;
                callback(pointer->data);
            }
        }

    private:
        Element<T>* dummy;
        Element<T>* last;
        int elementCount;
};