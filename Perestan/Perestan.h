/** @file
 * @author Большухин А.Д.
 * @version 1.0
 * @date 12.06.2019
 * @copyright ИБСТ ПГУ
 * @warning Лабораторная работа.
 * @brief Заголовочный файл для модуля Perestan
 */
#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
/** @brief Шифрование методом перестановки.
 * @details Ключ устанавливается в конструкторе.
 * Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
 * @warning Реализация только для английского языка.
 */
class Perestan{
private:
    int k;///< Ключ
    std::string getValidOpenText(const std::string & s);///< Метод проверки текста.
    std::string getValidCipherText(const std::string & s);///< Метод проверки зашифрованного текста.
public:
/** @brief Конструктор без параметра.
 * @details Конструктор запрещён.
 */
    Perestan()=delete;
/** @brief Конструктор для установки ключа.
 * @param [in] k - ключ, целое, положительное число.
 * @throw cipher_error, если ключ меньше или равен 1.
 */
    Perestan(const int k);
/**
 * @brief Метод для шифрования текста методом перестановки. 
 * @details Запись в таблицу происходит слева направо, сверху вниз. Считывание из таблицы сверху вниз, справа налево
 * @param [in] t Текст. Не должен быть пустой строкой. Текст не должен быть меньше или равен длине ключа.
 * @return Зашифрованный текст. 
 * @throw cipher_error, если строка пустая или меньше или равна длине ключа.
 */
    std::string  encrypt(const std::string& t);
/**
 * @brief Метод для расшифровки зашифрованного текста по известному ключу.
 * @param [in] z Зашифрованный текст. Должен содержать только символы английского алфавита в верхнем регистре. Строка не должна быть пустой.
 * @return Расшифрованный текст.
 * @throw cipher_error, если строка пустая или встречена не английская буква в верхнем регистре.
 */
    std::string  decrypt(const std::string& z); 
};

class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};