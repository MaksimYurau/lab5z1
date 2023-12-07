#pragma once

#include <iostream>
#include <fstream>

namespace containers {
    template <typename T>
    class DRList {
    public:

        // Конструктор по умолчанию
        DRList() : head(nullptr), size(0) {}

        // Конструктор от std::initializer_list<T>
        DRList(std::initializer_list<T> initList) : head(nullptr), size(0) {
            size_t i = 0;
            for (const T& element : initList) {
                addElement(element, i);
                i++;
            }
        }

        // Конструктор копирования
        DRList(const DRList<T>& other) : head(nullptr), size(0) {
            Node* otherCurrent = other.head;
            size_t i = 0;
            for (int j = 0; j < other.getSize(); j++) {
                addElement(otherCurrent->value, i);
                i++;
                otherCurrent = otherCurrent->next;
            }
        }

        // Копирующий оператор присваивания
        DRList<T>& operator=(const DRList<T>& other) {
            if (this == &other) {
                return *this;
            }

            clear();
            Node* otherCurrent = other.head;

            size_t i = 0;
            for (int j = 0; j < other.getSize(); j++) {
                addElement(otherCurrent->value, i);
                i++;
                otherCurrent = otherCurrent->next;
            }

            return *this;
        }

        // Конструктор перемещения
        DRList(DRList<T>&& other) noexcept : head(other.head), size(other.size) {
            other.head = nullptr;
            other.size = 0;
        }

        // Перемещающий оператор присваивания
        DRList<T>& operator=(DRList<T>&& other) noexcept {
            if (this == &other) {
                return *this;
            }

            clear();
            head = other.head;
            size = other.size;
            other.head = nullptr;
            other.size = 0;
            return *this;
        }

        // Операция индексирования
        T& operator[](int index) {
            if (index < 0 || index >= size) {
                throw std::out_of_range("Index out of range");
            }

            Node* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }

            return current->value;
        }

        // Метод, добавляющий элемент в произвольную позицию
        void addElement(const T& element, int position) {
            if (position < 0 || position > size) {
                throw std::out_of_range("Invalid position");
            }

            Node* newNode = new Node(element);

            if (position == 0) {  // Вставка в начало
                if (!head) {
                    head = newNode;
                    head->prev = head;
                    head->next = head;
                }
                else {
                    newNode->prev = head->prev;
                    newNode->next = head;
                    head->prev->next = newNode;
                    head->prev = newNode;
                    head = newNode;
                }
            }
            else if (position == size) {  // Вставка в конец
                newNode->prev = head->prev;
                newNode->next = head;
                head->prev->next = newNode;
                head->prev = newNode;
            }
            else {  // Вставка в произвольную позицию
                Node* current = head;
                for (int i = 0; i < position - 1; ++i) {
                    current = current->next;
                }

                newNode->prev = current;
                newNode->next = current->next;
                current->next->prev = newNode;
                current->next = newNode;
            }

            ++size;
        }

        // Метод для удаления элемента из конца (или начала, или произвольного элемента)
        void removeElement(int position = -1) {
            if (size == 0) {
                throw std::underflow_error("Container is empty");
            }

            if (size == 1) {
                delete head;
                head = nullptr;
            }
            else {
                if (position == -1) {  // Удаление из конца
                    Node* temp = head->prev;
                    temp->prev->next = head;
                    head->prev = temp->prev;
                    delete temp;
                }
                else if (position == 0) {  // Удаление из начала
                    Node* temp = head;
                    head = head->next;
                    head->prev = temp->prev;
                    temp->prev->next = head;
                    delete temp;
                }
                else {  // Удаление произвольного элемента
                    if (position < 0 || position >= size) {
                        throw std::out_of_range("Invalid position");
                    }

                    Node* current = head;
                    for (int i = 0; i < position; ++i) {
                        current = current->next;
                    }

                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                }
            }

            --size;
        }

        // Метод для получения размера списка
        int getSize() const {
            return size;
        }

        // Деструктор
        ~DRList() {
            clear();
        }

    private:
        struct Node {
            T value;
            Node* next;
            Node* prev;

            // Приватный конструктор
            Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
        };

        Node* head;
        int size;

        void clear() {
            if (!head) {
                return;
            }

            Node* current = head->next;
            while (current != head) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            delete head;
            head = nullptr;
            size = 0;
        }
    };
}
