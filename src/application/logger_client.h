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
 * ����� LoggerClient.
 * ���� ����� ���������� ������ ���������� Logger � ���������������� ������.
 *
 * ���������� LoggerClient ��������� ������������������ ������ ������ Logger.
 *
 * read_msg -  �����, �������������� ������ �� stdin, ��������� ������������
 * ����������� ������ ��������, � �������\�� ������� ��������� � �������
 * msg_data_. �������� � ��������� ������. � �������� ��������� �������������
 * ������������ mutex � ���� queue_mutex_.
 *
 * ����� processing_log ������������ ������ � ������ �� �������, �������� ��
 * ������ ������.
 *
 * ����� processing_raw_str - ������������ �������� ������������� ������.
 * ������ ������: ������� ��������::����� ��������� ��� ����� ���������(���
 * UNMARCKED) ��� EXIT(������� ������ �� ���������). ������ 1: INFO::3-� ������
 * ������� �� 62% �������. ������ 2: ������������ ������� ���������. ������ 3:
 * EXIT
 *
 * ���� ������:
 * logger_ - ������ ������ ����������.
 * msg_data_ - ������� ���������. ����� ������ ������� �������� �������������.
 * exit_code - ���������� ������ �� ���������. ��� �� ��������� ����� ������
 * ��������� EXIT.
 *
 * ������� lvl_check ��������� ������, ���������� ���������� �� ������ ��������
 * � ����������� ��� ������ ��������. ���������� ���� std::pair<bool, MsgLvl>,
 * ��� bool ��������� ��� ������� ������������ ������ �������� � MsgLvl ��������
 * ���� �������.
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
