#pragma once

#include <iostream>
#include <fstream>
#include "CustomException.h"

namespace containers {
    template <typename T>
    class DRList {

    private:
        // ��������������� ����� ���� ������
        class Node {
        public:
            Node(T value, Node* prev = nullptr, Node* next = nullptr)
                : value(value), prev(prev), next(next) {}
            T value;
            Node* next;
            Node* prev;

            // ��������� �����������
            Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
        };

        Node* head;
        Node* tail;
        int size;

        /*
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
        */

    public:

        // ����������� �� ���������
        DRList() : head(nullptr), size(0) {}

        // ����������� �� std::initializer_list<T>
        DRList(std::initializer_list<T> initList) : head(nullptr), size(0) {
            size_t i = 0;
            for (const T& element : initList) {
                addElement(element, i);
                i++;
            }
        }

        // ����������� �����������
        DRList(const DRList<T>& other) : head(nullptr), size(0) {
            Node* otherCurrent = other.head;
            size_t i = 0;
            for (int j = 0; j < other.getSize(); j++) {
                addElement(otherCurrent->value, i);
                i++;
                otherCurrent = otherCurrent->next;
            }
        }

        // ���������� �������� ������������
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

        // ����������� �����������
        DRList(DRList<T>&& other) noexcept : head(other.head), size(other.size) {
            other.head = nullptr;
            other.size = 0;
        }

        // ����������
        ~DRList() {
            clear();
        }

        // ������������ �������� ������������
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

        // �������� ��������������
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

        // ��������������� ����� ��� ��������� ���� �� �������
        Node* getNodeAtPosition(int position) const {
            if (position < 0 || position >= getSize()) {
                // throw CustomException("Invalid position");
                throw CustomException("������������ �������", position, 1);
            }
            Node* currentNode = head;
            for (int i = 0; i < position; ++i) {
                currentNode = currentNode->next;
            }
            return currentNode;
        };

        // ���������� �������� �� �������� �������
        void addElement(T value, int position) {
            if (position < 0) {
                throw CustomException("������������ �������", position, 1);
            }

            if (position == 0) {
                addToBeginning(value);
            }
            else if (position >= getSize()) {
                addToEnd(value);
            }
            else {
                Node* node = getNodeAtPosition(position);
                Node* newNode = new Node(value, node->prev, node);
                node->prev->next = newNode;
                node->prev = newNode;
            }
        }

        // ���������� �������� � ������ ������
        void addToBeginning(T value) {
            Node* newNode = new Node(value, nullptr, head);
            if (head != nullptr) {
                head->prev = newNode;
            }
            else {
                tail = newNode;
            }
            head = newNode;
        }

        // ���������� �������� � ����� ������
        void addToEnd(T value) {
            Node* newNode = new Node(value, tail, nullptr);
            if (tail != nullptr) {
                tail->next = newNode;
            }
            else {
                head = newNode;
            }
            tail = newNode;
        }

        // ��������� �������� �� �������
        T getElement(int index) const {
            Node* node = getNodeAtPosition(index);
            return node->value;
        }

        // �������� �������� �� �������
        void removeElement(int index) {
            Node* node = getNodeAtPosition(index);
            if (node->prev != nullptr) {
                node->prev->next = node->next;
            }
            else {
                head = node->next;
            }
            if (node->next != nullptr) {
                node->next->prev = node->prev;
            }
            else {
                tail = node->prev;
            }
            delete node;
        }

        // ��������� ������� ������
        int getSize() const {
            int count = 0;
            Node* currentNode = head;
            while (currentNode != nullptr) {
                count++;
                currentNode = currentNode->next;
            }
            return count;
        }

        // ������� ������
        void clear() {
            Node* currentNode = head;
            while (currentNode != nullptr) {
                Node* nextNode = currentNode->next;
                delete currentNode;
                currentNode = nextNode;
            }
            head = nullptr;
            tail = nullptr;
        }

        // ��������������� ����� ��������� ��� DRList
        class Iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            Iterator(Node* node) : currentNode(node) {}

            reference operator*() const {
                if (currentNode == nullptr) {
                    throw CustomException("�������� �� �������� ����������������", currentNode->value, 2);
                }
                return currentNode->value;
            }

            pointer operator->() const {
                if (currentNode == nullptr) {
                    throw CustomException("�������� �� �������� ����������������", currentNode->value, 3);
                }
                return &(currentNode->value);
            }

            Iterator& operator++() {
                if (currentNode == nullptr) {
                    throw CustomException("�������� �� ����������������", currentNode->value, 4);
                }
                currentNode = currentNode->next;
                return *this;
            }

            Iterator operator++(int) {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const Iterator& other) const {
                return currentNode == other.currentNode;
            }

            bool operator!=(const Iterator& other) const {
                return !(*this == other);
            }

        protected:
            Node* currentNode;
        };

        // ��������������� ����� ��������� ��� ������������� ��������� DRList
        class PositiveIterator : public Iterator {
        public:
            PositiveIterator(Node* node) : Iterator(node) {}

            PositiveIterator& operator++() {
                do {
                    Iterator::operator++();
                } while (Iterator::currentNode != nullptr && Iterator::currentNode->value < 0);
                return *this;
            }

            PositiveIterator operator++(int) {
                PositiveIterator temp = *this;
                ++(*this);
                return temp;
            }
        };

        // ��������������� ����� ��������� ��� ������������� ��������� DRList
        class NegativeIterator : public Iterator {
        public:
            NegativeIterator(Node* node) : Iterator(node) {}

            NegativeIterator& operator++() {
                do {
                    Iterator::operator++();
                } while (Iterator::currentNode != nullptr && Iterator::currentNode->value >= 0);
                return *this;
            }

            NegativeIterator operator++(int) {
                NegativeIterator temp = *this;
                ++(*this);
                return temp;
            }
        };

        // ������ begin() � end() ��� �������� �� ��������� ������
        Iterator begin() const {
            return Iterator(head);
        }

        Iterator end() const {
            return Iterator(nullptr);
        }

        // ������ begin() � end() ��� �������� �� ������������� ��������� ������
        PositiveIterator beginPositive() const {
            Node* currentNode = head;
            while (currentNode != nullptr && currentNode->value <= 0) {
                currentNode = currentNode->next;
            }
            return PositiveIterator(currentNode);
        }

        PositiveIterator endPositive() const {
            return PositiveIterator(nullptr);
        }

        // ������ begin() � end() ��� �������� �� ������������� ��������� ������
        NegativeIterator beginNegative() const {
            Node* currentNode = head;
            while (currentNode != nullptr && currentNode->value >= 0) {
                currentNode = currentNode->next;
            }
            return NegativeIterator(currentNode);
        }

        NegativeIterator endNegative() const {
            return NegativeIterator(nullptr);
        }
    };
}
