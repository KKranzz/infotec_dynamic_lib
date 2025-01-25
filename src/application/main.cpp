#include "logger_client.h"

int main(int argc, char* argv[]) {
  // ���������� ��� ���������: ./logger_client [log_name] [INFO or WARNING or
  // ERROR]
  if (argc < 3) {
    std::cout << "Incorrect input data. Example: logger_client [log_name] "
                 "[INFO or WARNING or ERROR]\n";
  } else {
    auto [is_lvl_correct, lvl] = lvl_check(argv[2]);
    if (is_lvl_correct) {  // ���� ������� �������� ���������, �� ����������
                           // ������ ���������.
      Logger& logger =
          Logger::init(argv[1], lvl);  // ��� ������� � ������� �� ���������
      LoggerClient loggerClient(logger);

      std::thread reader(&LoggerClient::read_msg, &loggerClient);
      std::thread writer(&LoggerClient::processing_log, &loggerClient);

      reader.join();
      writer.join();
    } else {  // ���� ������� �����������
      std::cout << "Input lvl not exists. Example: logger_client [log_name] "
                   "[INFO or WARNING or ERROR]\n";
    }
  }

  return 0;
}