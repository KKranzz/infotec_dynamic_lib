#include "lib_logger.h"

Logger::Logger(const std::string& journal_name, const MsgLvl& msg_lvl)
    : journal_name_(journal_name), default_msg_lvl_(new MsgLvl(msg_lvl)) {}

Logger& Logger::init(const std::string& journal_name, const MsgLvl& msg_lvl) {
  if (init_root_ != nullptr) {
    std::cout << "Journal logger already init!\n";
  } else {
    init_root_ = new Logger(journal_name, msg_lvl);
  }

  return *init_root_;
}

void Logger::change_lvl(const MsgLvl& msg_lvl) { *default_msg_lvl_ = msg_lvl; }

std::string Logger::get_time() const {
  // Получаем текущее время
  auto now = std::chrono::system_clock::now();
 // Преобразуем в time_t
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
   // Преобразуем в локальное время
  std::tm* now_tm = std::localtime(&now_c);
   // Создаем строковый поток для форматирования времени
  std::ostringstream oss;
   // Форматируем дату и время
  oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");

  return oss.str();
}

Logger::~Logger() { delete default_msg_lvl_; }

void Logger::log(const Message& msg) const {
  std::ofstream file(this->journal_name_, std::ios::app);

  if (!file.is_open()) {
    std::cout << "No such journal log\n";
  } else if (msg.msglvl_ >= *this->default_msg_lvl_) {
    std::string time = get_time();
    std::string lvl;
    switch (msg.msglvl_) {
      case MsgLvl::INFO:
        lvl = "INFO";
        break;
      case MsgLvl::WARNING:
        lvl = "WARNING";
        break;
      case MsgLvl::ERROR:
        lvl = "ERROR";
        break;
      case MsgLvl::UNMARCKED:
        lvl = "UNMARCKED";
        break;
      default:
        break;
    }
    std::string res = time + " - " + lvl + " - " + msg.text_ + "\n";
    file.write(res.c_str(), res.size());
  }

  file.flush();
  file.close();
}

MsgLvl Logger::get_default_lvl() const { return *this->default_msg_lvl_; }
