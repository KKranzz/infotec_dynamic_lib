#include "logger_client.h"

int main(int argc, char* argv[]) {
  // Необходимо три агрумента: ./logger_client [log_name] [INFO or WARNING or
  // ERROR]
  if (argc < 3) {
    std::cout << "Incorrect input data. Example: logger_client [log_name] "
                 "[INFO or WARNING or ERROR]\n";
  } else {
    auto [is_lvl_correct, lvl] = lvl_check(argv[2]);
    if (is_lvl_correct) {  // Если уровень важности корректен, то начинается
                           // работа программы.
      Logger& logger =
          Logger::init(argv[1], lvl);  // имя журнала и уровень по умолчанию
      LoggerClient loggerClient(logger);

      std::thread reader(&LoggerClient::read_msg, &loggerClient);
      std::thread writer(&LoggerClient::processing_log, &loggerClient);

      reader.join();
      writer.join();
    } else {  // Если уровень некорректен
      std::cout << "Input lvl not exists. Example: logger_client [log_name] "
                   "[INFO or WARNING or ERROR]\n";
    }
  }

  return 0;
}