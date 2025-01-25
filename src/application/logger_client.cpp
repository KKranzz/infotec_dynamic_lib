#include "logger_client.h"

LoggerClient::LoggerClient(const Logger& logger) : logger_(&logger) {}

void LoggerClient::read_msg() {
  while (this->exit_code == 0) {
    Message msg = this->processing_raw_str();
    if (msg.msglvl_ >= this->logger_->get_default_lvl() &&
        this->exit_code == 0) {
      std::lock_guard<std::mutex> lock(queue_mutex_);
      msg_data_.push(msg);
      std::this_thread::sleep_for(
          std::chrono::milliseconds(100));  // эмуляция задержки
    }
  }
}

void LoggerClient::processing_log() {
  while (this->exit_code == 0) {
    Message msg;
    {
      std::lock_guard<std::mutex> lock(queue_mutex_);
      if (!msg_data_.empty()) {
        msg = msg_data_.front();
        msg_data_.pop();
      } else {
        continue;
      }
    }
    logger_->log(msg);
    std::this_thread::sleep_for(
        std::chrono::milliseconds(100));  // эмуляция задержки
  }
}

std::pair<bool, MsgLvl> lvl_check(const std::string& lvl_str) {
  std::pair<bool, MsgLvl> check_data = {false, MsgLvl::INFO};
  auto [is_find_lvl, lvl] = check_data;

  if (lvl_str == "INFO") {
    is_find_lvl = true;
    lvl = MsgLvl::INFO;
  } else if (lvl_str == "WARNING") {
    is_find_lvl = true;
    lvl = MsgLvl::WARNING;
  } else if (lvl_str == "ERROR") {
    is_find_lvl = true;
    lvl = MsgLvl::ERROR;
  } else {
    is_find_lvl = false;
  }

  return std::make_pair(is_find_lvl, lvl);
}

Message LoggerClient::processing_raw_str() {
  Message processed_msg;
  std::string raw;
  std::getline(std::cin, raw);

  if (raw == "EXIT") {
    this->exit_code = true;
  } else {
    size_t pos_delim = raw.find("::");
    if (pos_delim != std::string::npos) {
      std::string lvl_str = raw.substr(0, pos_delim);
      auto [is_lvl_correct, lvl] = lvl_check(lvl_str);

      if (is_lvl_correct) {
        processed_msg.text_ = raw.substr(pos_delim + 2);
        processed_msg.msglvl_ = lvl;
      } else {
        processed_msg.text_ = raw;
        processed_msg.msglvl_ = MsgLvl::UNMARCKED;
      }

    } else {
      processed_msg.text_ = raw;
      processed_msg.msglvl_ = MsgLvl::UNMARCKED;
    }
  }

  return processed_msg;
}