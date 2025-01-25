#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#ifndef LIB_LOG_H
#define LIB_LOG_H

/*
 *  В перечислении представлены четыре уровня важности.
 *  INFO - самый низкий уровень
 *  WARNING - средний уровень
 *  ERROR - самый высокий
 *  UNMARCKED - для ситуаций когда уровень не указан пользователем
 *  Архитектура приложения построена таким образом, что немаркированные
 * сообщения всегда попадают в журнал.
 */
enum class MsgLvl { INFO, WARNING, ERROR, UNMARCKED };

/*
 * Структура сообщения представляет собой текст(text_) и уровень
 * важности(msglvl_).
 */

struct Message {
  std::string text_;
  MsgLvl msglvl_;
};

/*
 * Класс библиотеки Logger.
 * Класс реализован по паттерну одиночки(Singleton).
 *
 * Метод init, создающий единственные экземпляр класса. Принимает имя журнала и
 * уровень по умолчанию. Этот метод отвечает за "Библиотека при инициализации
 * должна принимать следующие параметры: a. Имя файла журнала. b. Уровень
 * важности сообщения по умолчанию. Сообщения с уровнем ниже заданного не должны
 * записываться в журнал. Уровень рекомендуется задавать с помощью перечисления
 * с понятными именами. Достаточно трех уровней важности." из ТЗ.
 *
 * Метод log отвечает за запись сообщения в журнал (принимает сообщение).
 *
 * Метод change_lvl позволяет изменить уровень по умолчанию (принимает уровень).
 *
 * Метод get_default_lvl возвращает текущий уровень по умолчанию. Нужен для
 * сравнения с поступающими уровнями важности от пользователя и принятием
 * решения о записи\не записи в журнал.
 *
 * Конструктор Logger. Принимает имя журнала и уровень по умолчанию. Является
 * приватным для соотвествия синглтон паттерну.
 *
 * Деструктор Logger. Освобождает память для поля default_msg_lvl_.
 *
 * Метод get_time. Возращает строку с текущим временем. Используется в log для
 * формирования строки журнала.
 *
 * В классе присутствует защита от копирования поэтому удален оператор
 * присваения и соотвествующий конструктор.
 *
 * init_root_ - хранит единственный экземпляр класса.
 *
 * journal_name_ - имя журнала.
 *
 * default_msg_lvl_ - уровень по умолчанию.
 *
 */
class Logger {
 public:
  static Logger& init(const std::string& journal_name, const MsgLvl& msg_lvl);
  void log(const Message& msg) const;
  void change_lvl(const MsgLvl& msg_lvl);
  MsgLvl get_default_lvl() const;

 private:
  Logger(const std::string& journal_name, const MsgLvl& msg_lvl);
  ~Logger();
  std::string get_time() const;

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  inline static Logger* init_root_ = nullptr;
  std::string journal_name_;
  MsgLvl* default_msg_lvl_ = nullptr;
};

#endif