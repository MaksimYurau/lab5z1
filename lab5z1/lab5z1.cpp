/*
Лабораторная работа №5.
Реализовать для своей программы, созданной в рамках 2 лабораторной работы, итераторы - 2 класса.
Один для обхода, например, положительных элементов коллекции, второй - отрицательных;
или один для обхода коллекции в одну сторону, второй в другую
(один для обхода дерева сверху вниз, второй слева направо).
Предусмотреть исключительные ситуации и их обработку
(например обращение к элементу коллекции, если она пустая).
Для обработки исключений использовать ранее реализованный класс CustomException.
Создать общий интерфейс для работы с итераторами.
*/

#include <iostream>
#include <string>
#include <vector>
// #include <iterator>

/*
    // namespace containers {

    // Класс-исключение для обработки ошибок
    class CustomException : public std::exception {
    public:
        CustomException(const std::string& message) : errorMessage(message) {}

        const char* what() const noexcept override {
           // return "Произошла ошибка.";
            return errorMessage.c_str();
        }

    private:
        std::string errorMessage;
    };
    */

    // namespace containers {
class CustomException : public std::exception {
public:
    CustomException(const std::string& message, double errorValue, int errorCode)
        : errorMessage(message), errorValue(errorValue), errorCode(errorCode) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

    double getErrorValue() const {
        return errorValue;
    }

    int getErrorCode() const {
        return errorCode;
    }

private:
    std::string errorMessage;
    double errorValue;
    int errorCode;
};

namespace containers {
    template <typename T>
    class DRList {
    private:
        // Вспомогательный класс узла списка
        class Node {
        public:
            Node(T value, Node* prev = nullptr, Node* next = nullptr)
                : value(value), prev(prev), next(next) {}

            T value;
            Node* prev;
            Node* next;
        };

        Node* head;
        Node* tail;

    public:
        // Конструктор
        DRList() : head(nullptr), tail(nullptr) {}

        // Деструктор
        ~DRList() {
            clear();
        }

        // Добавление элемента на заданную позицию
        void addElement(T value, int position) {
            if (position < 0) {
                throw CustomException("Недопустимая позиция", position, 1);
            }

            if (position == 0) {
                addToBeginning(value);
            }
            else if (position >= size()) {
                addToEnd(value);
            }
            else {
                Node* node = getNodeAtPosition(position);
                Node* newNode = new Node(value, node->prev, node);
                node->prev->next = newNode;
                node->prev = newNode;
            }
        }

        // Добавление элемента в начало списка
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

        // Добавление элемента в конец списка
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

        // Получение элемента по индексу
        T getElement(int index) const {
            Node* node = getNodeAtPosition(index);
            return node->value;
        }

        // Удаление элемента по индексу
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

        // Получение размера списка
        int size() const {
            int count = 0;
            Node* currentNode = head;
            while (currentNode != nullptr) {
                count++;
                currentNode = currentNode->next;
            }
            return count;
        }

        // Очистка списка
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

        // Вспомогательный метод для получения узла по позиции
        Node* getNodeAtPosition(int position) const {
            if (position < 0 || position >= size()) {
                // throw CustomException("Invalid position");
                throw CustomException("Недопустимая позиция", position, 1);
            }
            Node* currentNode = head;
            for (int i = 0; i < position; ++i) {
                currentNode = currentNode->next;
            }
            return currentNode;
        };

        // Вспомогательный класс итератора для DRList
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
                    throw CustomException("Итератор не является разыменовываемым", currentNode->value, 2);
                }
                return currentNode->value;
            }

            pointer operator->() const {
                if (currentNode == nullptr) {
                    throw CustomException("Итератор не является разыменовываемым", currentNode->value, 3);
                }
                return &(currentNode->value);
            }

            Iterator& operator++() {
                if (currentNode == nullptr) {
                    throw CustomException("Итератор не инкрементируется", currentNode->value, 4);
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

        // Вспомогательный класс итератора для положительных элементов DRList
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

        // Вспомогательный класс итератора для отрицательных элементов DRList
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

        // Методы begin() и end() для итерации по элементам списка
        Iterator begin() const {
            return Iterator(head);
        }

        Iterator end() const {
            return Iterator(nullptr);
        }

        // Методы begin() и end() для итерации по положительным элементам списка
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

        // Методы begin() и end() для итерации по отрицательным элементам списка
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

containers::DRList<int> foo(containers::DRList<int> x) {
    return x;
}

int main() {

    setlocale(0, "ru");

    // Создаём DRList с элементами типа int
    containers::DRList<int> intDRList;

    // Добавляем элемент в начало intDRList
    intDRList.addToBeginning(0);

    // Добавляем элемент после первого элемента intDRList
    intDRList.addElement(4, 1);

    // Добавляем элементы в конец intDRList
    intDRList.addToEnd(1);
    intDRList.addToEnd(-2);
    intDRList.addToEnd(3);
    intDRList.addToEnd(-4);

    // Выводим все элементы intDRList
    std::cout << "Все элементы intDRList: ";
    for (const auto& element : intDRList) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Получение размера intDRList
    std::cout << "Размер intDRList: " << intDRList.size() << std::endl;

    // Создание PositiveIterator positiveItIntDRListBegin
    containers::DRList<int>::PositiveIterator positiveItIntDRListBegin = intDRList.beginPositive();

    // Создание PositiveIterator positiveItIntDRListEnd
    containers::DRList<int>::PositiveIterator positiveItIntDRListEnd = intDRList.endPositive();

    // Вывод всех положительных элементов intDRList
    std::cout << "Все положительные элементы intDRList: ";
    while (positiveItIntDRListBegin != positiveItIntDRListEnd) {
        std::cout << *positiveItIntDRListBegin << " ";
        ++positiveItIntDRListBegin;
    }
    std::cout << std::endl;

    // Создание NegativeIterator negativeItIntDRListBegin
    containers::DRList<int>::NegativeIterator negativeItIntDRListBegin = intDRList.beginNegative();

    // Создание NegativeIterator negativeItIntDRListEnd
    containers::DRList<int>::NegativeIterator negativeItIntDRListEnd = intDRList.endNegative();

    // Вывод всех отрицательных элементов intDRList
    std::cout << "Все отрицательные элементы intDRList: ";
    while (negativeItIntDRListBegin != negativeItIntDRListEnd) {
        std::cout << *negativeItIntDRListBegin << " ";
        ++negativeItIntDRListBegin;
    }
    std::cout << std::endl;

    try
    {
        // Удаляем n-элемент из intDRList
        intDRList.removeElement(0);

        // Удаляем элемент из конца intDRList
        intDRList.removeElement(intDRList.size() - 1);
    }
    catch (const CustomException& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        std::cerr << "Значение, приведшее к ошибке: " << ex.getErrorValue() << std::endl;
        std::cerr << "Код ошибки: " << ex.getErrorCode() << std::endl;
    }

    // Выводим все элементы intDRList
    std::cout << "Все элементы intDRList: ";
    for (const auto& element : intDRList) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Получение размера intDRList
    std::cout << "Размер intDRList: " << intDRList.size() << std::endl;

    // Очистка intDRList
    intDRList.clear();
    std::cout << "Очистка intDRList..." << std::endl;

    // Получение размера intDRList
    std::cout << "Размер intDRList: " << intDRList.size() << std::endl;

    try
    {
        // Обращение к элементу intDRList, когда intDRList пуст
        intDRList.getElement(0);
    }
    catch (const CustomException& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        std::cerr << "Значение, приведшее к ошибке: " << ex.getErrorValue() << std::endl;
        std::cerr << "Код ошибки: " << ex.getErrorCode() << std::endl;
    }

    // Пустая строка, чтобы разделить intDRList и doubleDRList
    std::cout << std::endl;

    // Создаём DRList с элементами типа double
    containers::DRList<double> doubleDRList;

    // Добавляем элемент в начало doubleDRList
    doubleDRList.addToBeginning(0.1);

    // Добавляем элемент после первого элемента doubleDRList
    doubleDRList.addElement(1.1, 1);

    // Добавляем элементы в конец doubleDRList
    doubleDRList.addToEnd(1.2);
    doubleDRList.addToEnd(-2.3);
    doubleDRList.addToEnd(3.4);
    doubleDRList.addToEnd(-4.5);

    // Выводим все элементы doubleDRList
    std::cout << "Все элементы doubleDRList: ";
    for (const auto& element : doubleDRList) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Получение размера doubleDRList
    std::cout << "Размер doubleDRList: " << doubleDRList.size() << std::endl;

    // Создание PositiveIterator positiveItDoubleDRListBegin
    containers::DRList<double>::PositiveIterator positiveItDoubleDRListBegin = doubleDRList.beginPositive();

    // Создание PositiveIterator positiveItDoubleDRListEnd
    containers::DRList<double>::PositiveIterator positiveItDoubleDRListEnd = doubleDRList.endPositive();

    // Вывод всех положительных элементов doubleDRList
    std::cout << "Все положительные элементы doubleDRList: ";
    while (positiveItDoubleDRListBegin != positiveItDoubleDRListEnd) {
        std::cout << *positiveItDoubleDRListBegin << " ";
        ++positiveItDoubleDRListBegin;
    }
    std::cout << std::endl;

    // Создание NegativeIterator negativeItDoubleDRListBegin
    containers::DRList<double>::NegativeIterator negativeItDoubleDRListBegin = doubleDRList.beginNegative();

    // Создание NegativeIterator negativeItDoubleDRListEnd
    containers::DRList<double>::NegativeIterator negativeItDoubleDRListEnd = doubleDRList.endNegative();

    // Вывод всех отрицательных элементов doubleDRList
    std::cout << "Все отрицательные элементы doubleDRList: ";
    while (negativeItDoubleDRListBegin != negativeItDoubleDRListEnd) {
        std::cout << *negativeItDoubleDRListBegin << " ";
        ++negativeItDoubleDRListBegin;
    }
    std::cout << std::endl;

    try
    {
        // Удаляем n-элемент из doubleDRList
        doubleDRList.removeElement(1);

        // Удаляем элемент из конца doubleDRList
        doubleDRList.removeElement(doubleDRList.size() - 1);
    }
    catch (const CustomException& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        std::cerr << "Значение, приведшее к ошибке: " << ex.getErrorValue() << std::endl;
        std::cerr << "Код ошибки: " << ex.getErrorCode() << std::endl;
    }

    // Выводим все элементы doubleDRList
    std::cout << "Все элементы doubleDRList: ";
    for (const auto& element : doubleDRList) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Получение размера doubleDRList
    std::cout << "Размер doubleDRList: " << doubleDRList.size() << std::endl;

    // Очистка doubleDRList
    doubleDRList.clear();
    std::cout << "Очистка doubleDRList..." << std::endl;

    // Получение размера doubleDRList
    std::cout << "Размер doubleDRList: " << doubleDRList.size() << std::endl;

    try
    {
        // Обращение к элементу doubleDRList, когда doubleDRList пуст
        doubleDRList.getElement(1);
    }
    catch (const CustomException& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        std::cerr << "Значение, приведшее к ошибке: " << ex.getErrorValue() << std::endl;
        std::cerr << "Код ошибки: " << ex.getErrorCode() << std::endl;
    }

    /*
    // Создаём DRList с элементами типа string
    containers::DRList<std::string> stringDRList;

    // Добавляем элемент в начало stringDRList
    stringDRList.addToBeginning("Lorem");

    // Добавляем элемент после первого элемента stringDRList
    stringDRList.addElement("Ipsum", 1);

    // Добавляем элементы в конец stringDRList
    stringDRList.addToEnd("is");
    stringDRList.addToEnd("simply");
    stringDRList.addToEnd("dummy");
    stringDRList.addToEnd("text");

    // Выводим все элементы stringDRList
    std::cout << "Все элементы stringDRList: ";
    for (const auto& element : stringDRList) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Получение размера stringDRList
    std::cout << "Размер stringDRList: " << stringDRList.size() << std::endl;
    */

    /*
    // Создание PositiveIterator positiveItStringDRListBegin
    containers::DRList<std::string>::PositiveIterator positiveItStringDRListBegin = stringDRList.beginPositive();

    // Создание PositiveIterator positiveItStringDRListEnd
    containers::DRList<std::string>::PositiveIterator positiveItStringDRListEnd = stringDRList.endPositive();

    // Вывод всех положительных элементов stringDRList
    std::cout << "Все положительные элементы stringDRList: ";
    while (positiveItStringDRListBegin != positiveItStringDRListEnd) {
        std::cout << *positiveItStringDRListBegin << " ";
        ++positiveItStringDRListBegin;
    }
    std::cout << std::endl;

    // Создание NegativeIterator negativeItStringDRListBegin
    containers::DRList<std::string>::NegativeIterator negativeItStringDRListBegin = stringDRList.beginNegative();

    // Создание NegativeIterator negativeItStringDRListEnd
    containers::DRList<std::string>::NegativeIterator negativeItStringDRListEnd = stringDRList.endNegative();

    // Вывод всех отрицательных элементов stringDRList
    std::cout << "Все отрицательные элементы stringDRList: ";
    while (negativeItStringDRListBegin != negativeItStringDRListEnd) {
        std::cout << *negativeItStringDRListBegin << " ";
        ++negativeItStringDRListBegin;
    }
    std::cout << std::endl;
    */

    /*
    try
    {
        // Удаляем n-элемент из stringDRList
        stringDRList.removeElement(1);

        // Удаляем элемент из конца stringDRList
        stringDRList.removeElement(stringDRList.size() - 1);
    }
    catch (const CustomException& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        // std::cerr << "Значение, приведшее к ошибке: " << ex.getErrorValue() << std::endl;
        std::cerr << "Код ошибки: " << ex.getErrorCode() << std::endl;
    }

    // Выводим все элементы stringDRList
    std::cout << "Все элементы stringDRList: ";
    for (const auto& element : stringDRList) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Получение размера stringDRList
    std::cout << "Размер stringDRList: " << stringDRList.size() << std::endl;

    // Очистка stringDRList
    stringDRList.clear();
    std::cout << "Очистка stringDRList..." << std::endl;

    // Получение размера stringDRList
    std::cout << "Размер stringDRList: " << stringDRList.size() << std::endl;

    try
    {
        // Обращение к элементу stringDRList, когда stringDRList пуст
        stringDRList.getElement(1);
    }
    catch (const CustomException& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        // std::cerr << "Значение, приведшее к ошибке: " << ex.getErrorValue() << std::endl;
        std::cerr << "Код ошибки: " << ex.getErrorCode() << std::endl;
    }
    */

    // Пустая строка для разделения
    std::cout << std::endl;

    system("pause");
    return 0;
}
