/*
Лабораторная работа №5.
Паттерны проектирования.
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
#include "DRList.h"
#include <vector>

containers::DRList<int> foo(containers::DRList<int> x) {
    return x;
}

int main() {

    setlocale(0, "ru");

    // Создаём DRList с элементами типа int
    containers::DRList<int> intDRList;

    // Добавляем элемент в начало intDRList
    intDRList.addToBeginning(1);

    // Добавляем элемент после первого элемента intDRList
    intDRList.addElement(4, 1);

    // Добавляем элементы в конец intDRList
    intDRList.addToEnd(1);
    intDRList.addToEnd(-2);
    intDRList.addToEnd(3);
    intDRList.addToEnd(-4);

    // Создание Iterator ItIntDRListBegin
    containers::DRList<int>::Iterator ItIntDRListBegin = intDRList.beginPositive();
    // Создание Iterator ItIntDRListEnd
    containers::DRList<int>::Iterator ItIntDRListEnd = intDRList.endPositive();

    // Выводим все элементы intDRList
    std::cout << "Все элементы intDRList: ";
    while (ItIntDRListBegin != ItIntDRListEnd) {
        std::cout << *ItIntDRListBegin << " ";
        ++ItIntDRListBegin;
    }
    std::cout << std::endl;

    // Получение размера intDRList
    std::cout << "Размер intDRList: " << intDRList.getSize() << std::endl;

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
        intDRList.removeElement(intDRList.getSize() - 1);
    }
    catch (const CustomException& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        std::cerr << "Значение, приведшее к ошибке: " << ex.getErrorValue() << std::endl;
        std::cerr << "Код ошибки: " << ex.getErrorCode() << std::endl;
    }

    // Выводим все элементы intDRList
    std::cout << "Все элементы intDRList: ";
    while (ItIntDRListBegin != ItIntDRListEnd) {
        std::cout << *ItIntDRListBegin << " ";
        ++ItIntDRListBegin;
    }
    std::cout << std::endl;

    // Получение размера intDRList
    std::cout << "Размер intDRList: " << intDRList.getSize() << std::endl;

    // Очистка intDRList
    intDRList.clear();
    std::cout << "Очистка intDRList..." << std::endl;

    // Получение размера intDRList
    std::cout << "Размер intDRList: " << intDRList.getSize() << std::endl;

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

    // Создание Iterator ItDoubleDRListBegin
    containers::DRList<double>::Iterator ItDoubleDRListBegin = doubleDRList.beginPositive();
    // Создание Iterator ItDoubleDRListEnd
    containers::DRList<double>::Iterator ItDoubleDRListEnd = doubleDRList.endPositive();

    // Выводим все элементы doubleDRList
    std::cout << "Все элементы doubleDRList: ";
    while (ItDoubleDRListBegin != ItDoubleDRListEnd) {
        std::cout << *ItDoubleDRListBegin << " ";
        ++ItDoubleDRListBegin;
    }
    std::cout << std::endl;

    // Получение размера doubleDRList
    std::cout << "Размер doubleDRList: " << doubleDRList.getSize() << std::endl;

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
        doubleDRList.removeElement(doubleDRList.getSize() - 1);
    }
    catch (const CustomException& ex)
    {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        std::cerr << "Значение, приведшее к ошибке: " << ex.getErrorValue() << std::endl;
        std::cerr << "Код ошибки: " << ex.getErrorCode() << std::endl;
    }

    // Выводим все элементы doubleDRList
    std::cout << "Все элементы doubleDRList: ";
    while (ItDoubleDRListBegin != ItDoubleDRListEnd) {
        std::cout << *ItDoubleDRListBegin << " ";
        ++ItDoubleDRListBegin;
    }
    std::cout << std::endl;

    // Получение размера doubleDRList
    std::cout << "Размер doubleDRList: " << doubleDRList.getSize() << std::endl;

    // Очистка doubleDRList
    doubleDRList.clear();
    std::cout << "Очистка doubleDRList..." << std::endl;

    // Получение размера doubleDRList
    std::cout << "Размер doubleDRList: " << doubleDRList.getSize() << std::endl;

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
    // Создаём DRList с элементами типа std::string
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

    // Создание Iterator ItStringDRListBegin
    containers::DRList<std::string>::Iterator ItStringDRListBegin = stringDRList.beginPositive();

    // Создание Iterator ItStringDRListEnd
    containers::DRList<std::string>::Iterator ItStringDRListEnd = stringDRList.endPositive();

    // Выводим все элементы stringDRList
    std::cout << "Все элементы stringDRList: ";
    while (ItStringDRListBegin != ItStringDRListEnd) {
        std::cout << *ItStringDRListBegin << " ";
        ++ItStringDRListBegin;
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
    while (ItStringDRListBegin != ItStringDRListEnd) {
        std::cout << *ItStringDRListBegin << " ";
        ++ItStringDRListBegin;
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

    // Создаём DRList с элементами типа int
    containers::DRList<int> intDRList2 = { 1, 3, 5, 7 };

    // Создание Iterator ItIntDRList2Begin
    containers::DRList<int>::Iterator ItIntDRList2Begin = intDRList2.beginPositive();
    // Создание Iterator ItIntDRList2End
    containers::DRList<int>::Iterator ItIntDRList2End = intDRList2.endPositive();

    // Выводим все элементы intDRList2
    std::cout << "Все элементы intDRList2: ";
    while (ItIntDRList2Begin != ItIntDRList2End) {
        std::cout << *ItIntDRList2Begin << " ";
        ++ItIntDRList2Begin;
    }
    std::cout << std::endl;

    // Создаём DRList с элементами типа double
    containers::DRList<double> doubleDRList2 = { 1.1, 2.2, 6.6, 8.8 };

    // Создание Iterator ItDoubleDRList2Begin
    containers::DRList<double>::Iterator ItDoubleDRList2Begin = doubleDRList2.beginPositive();
    // Создание Iterator ItDoubleDRList2End
    containers::DRList<double>::Iterator ItDoubleDRList2End = doubleDRList2.endPositive();

    // Выводим все элементы doubleDRList2
    std::cout << "Все элементы doubleDRList2: ";
    while (ItDoubleDRList2Begin != ItDoubleDRList2End) {
        std::cout << *ItDoubleDRList2Begin << " ";
        ++ItDoubleDRList2Begin;
    }
    std::cout << std::endl;

    // Конструктор копирования (intDRList2 -> intDRListCopy)
    containers::DRList<int> intDRListCopy{ intDRList2 };

    // Создание Iterator ItIntDRListCopyBegin
    containers::DRList<int>::Iterator ItIntDRListCopyBegin = intDRListCopy.beginPositive();

    // Создание Iterator ItIntDRListCopyEnd
    containers::DRList<int>::Iterator ItIntDRListCopyEnd = intDRListCopy.endPositive();

    std::cout << std::endl;
    std::cout << "Конструктор копирования (int): ";
    while (ItIntDRListCopyBegin != ItIntDRListCopyEnd) {
        std::cout << *ItIntDRListCopyBegin << " ";
        ++ItIntDRListCopyBegin;
    }

    // Конструктор копирования (doubleDRList2 -> doubleDRListCopy)
    containers::DRList<double> doubleDRListCopy{ doubleDRList2 };

    // Создание Iterator ItDoubleDRListCopyBegin
    containers::DRList<double>::Iterator ItDoubleDRListCopyBegin = doubleDRListCopy.beginPositive();

    // Создание Iterator ItDoubleDRListCopyEnd
    containers::DRList<double>::Iterator ItDoubleDRListCopyEnd = doubleDRListCopy.endPositive();

    std::cout << std::endl;
    std::cout << "Конструктор копирования (double): ";
    while (ItDoubleDRListCopyBegin != ItDoubleDRListCopyEnd) {
        std::cout << *ItDoubleDRListCopyBegin << " ";
        ++ItDoubleDRListCopyBegin;
    }

    /*
    // Конструктор перемещения (intDRListMoveTest -> intDRListMoveTest1)
    containers::DRList<int> intDRListMoveTest{1, 9, 6, 8};

    containers::DRList<int> intDRListMoveTest1;

    intDRListMoveTest1 = foo(intDRListMoveTest);
    */

    /*
    // Конструктор перемещения (doubleDRListMoveTest -> doubleDRListMoveTest1)
    containers::DRList<int> doubleDRListMoveTest{1.1, 9.9, 6.6, 8.8};

    containers::DRList<int> doubleDRListMoveTest1;

    doubleDRListMoveTest1 = foo(doubleDRListMoveTest);
    */

    std::cout << std::endl << std::endl;

    system("pause");
    return 0;
}
