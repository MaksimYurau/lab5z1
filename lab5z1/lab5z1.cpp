// lab5z1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include "DRList.h"
#include <vector>

containers::DRList<int> foo(containers::DRList<int> x) {
    return x;
}

int main() {
    // Создаём DRList с элементами типа int
    containers::DRList<int> intList;

    // Добавляем элементы в начало
    intList.addElement(0, 0);

    // Добавляем элемент в произвольную позицию (после первого элемента)
    intList.addElement(4, 1);

    // Добавляем элементы в конец
    intList.addElement(8, 2);
    intList.addElement(7, 3);

    // Удаляем элемент из конца
    intList.removeElement();

    // Выводим элементы
    std::cout << "Int List: ";
    for (int i = 0; i < intList.getSize(); ++i) {
        std::cout << intList[i] << " ";
    }
    std::cout << std::endl;

    // Создаём DRList с элементами типа double
    containers::DRList<double> doubleList;

    // Добавляем элементы в конец
    doubleList.addElement(1.1, 0);
    doubleList.addElement(2.2, 1);
    doubleList.addElement(3.3, 2);

    // Выводим элементы
    std::cout << "Double List: ";
    for (int i = 0; i < doubleList.getSize(); ++i) {
        std::cout << doubleList[i] << " ";
    }
    std::cout << std::endl;

    // Создаём DRList с элементами типа string
    containers::DRList<std::string> stringList;

    // Добавляем элементы в конец
    stringList.addElement("Hello", 0);
    stringList.addElement("World", 1);

    // Выводим элементы
    std::cout << "std::string List: ";
    for (int i = 0; i < stringList.getSize(); ++i) {
        std::cout << stringList[i] << " ";
    }

    std::cout << std::endl << std::endl;

    // Создаём DRList с элементами типа int
    containers::DRList<int> intList2 = { 1, 3, 5, 7 };

    // Выводим элементы 
    std::cout << "Int List: ";
    for (int i = 0; i < intList2.getSize(); ++i) {
        std::cout << intList2[i] << " ";
    }
    std::cout << std::endl;

    // Создаём DRList с элементами типа double
    containers::DRList<double> doubleList2 = { 1, 2, 6, 8 };

    // Выводим элементы 
    std::cout << "Double List: ";
    for (int i = 0; i < doubleList2.getSize(); ++i) {
        std::cout << doubleList2[i] << " ";
    }
    std::cout << std::endl;

    // Создаём DRList с элементами типа std::string
    containers::DRList<std::string> stringList2 = { "Hello", "world" };

    // Выводим элементы 
    std::cout << "std::string List: ";
    for (int i = 0; i < stringList2.getSize(); ++i) {
        std::cout << stringList2[i] << " ";
    }
    std::cout << std::endl << std::endl;

    // Конструктор копирования (intList -> intListCopy)
    containers::DRList<int> intListCopy{ intList };
    std::cout << std::endl;
    std::cout << "Copy constructor (int): ";
    for (int i = 0; i < intListCopy.getSize(); ++i)
    {
        std::cout << intListCopy[i] << " ";
    }

    std::cout << std::endl << std::endl;

    // Конструктор перемещения (intListMoveTest -> intListMove)
    containers::DRList<int> intListMoveTest{ 1, 9, 6, 8 };

    containers::DRList<int> intListMoveTest1;

    intListMoveTest1 = foo(intListMoveTest);

    std::cout << std::endl;

    system("pause");
    return 0;
}
