#include <chrono>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "../lib/lib_logger.h"

#ifndef APP_H
#define APP_H

/*
 *
 * Класс LoggerClient.
 * Этот класс организует работу библиотеки Logger в потокобезопасном режиме.
 *
 * Констуктор LoggerClient принимает инициализированный объект класса Logger.
 *
 * read_msg -  метод, осуществляющий чтение из stdin, проверяет соответствие
 * допустимому уровню важности, и заносит\не заносит сообщение в очередь
 * msg_data_. Работает в отдельном потоке. В качестве механизма синхронизации
 * используется mutex в поле queue_mutex_.
 *
 * Метод processing_log осуществялет запись в журнал из очереди, работает во
 * втором потоке.
 *
 * Метод processing_raw_str - обрабатывает поданную пользователем строку.
 * Формат строки: Уровень важности::текст сообщения или текст сообщения(для
 * UNMARCKED) или EXIT(условие выхода из программы). Пример 1: INFO::3-й корпус
 * состоит из 62% металла. Пример 2: Неотмеченное уровнем сообщение. Пример 3:
 * EXIT
 *
 * поля класса:
 * logger_ - объект класса библиотеки.
 * msg_data_ - очередь сообщений. Общий ресурс потоков требущий синхронизации.
 * exit_code - переменная выхода из программы. Для ее активации нужно ввести
 * сообщение EXIT.
 *
 * Функция lvl_check переводит строку, содержащую информацию об уровне важности
 * в структурный вид уровня важности. Возвращает пару std::pair<bool, MsgLvl>,
 * где bool указывает что найдено соответствие уровню важности а MsgLvl является
 * этим уровнем.
 *
 */

class LoggerClient {
 public:
  LoggerClient(const Logger& logger);
  void read_msg();
  void processing_log();

 private:
  Message processing_raw_str();

  const Logger* logger_ = nullptr;
  std::queue<Message> msg_data_;
  std::mutex queue_mutex_;
  bool exit_code = 0;
};

std::pair<bool, MsgLvl> lvl_check(const std::string& lvl_str);

#endif  // !APP_H
