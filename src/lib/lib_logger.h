#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#ifndef LIB_LOG_H
#define LIB_LOG_H

/*
 *  � ������������ ������������ ������ ������ ��������.
 *  INFO - ����� ������ �������
 *  WARNING - ������� �������
 *  ERROR - ����� �������
 *  UNMARCKED - ��� �������� ����� ������� �� ������ �������������
 *  ����������� ���������� ��������� ����� �������, ��� ���������������
 * ��������� ������ �������� � ������.
 */
enum class MsgLvl { INFO, WARNING, ERROR, UNMARCKED };

/*
 * ��������� ��������� ������������ ����� �����(text_) � �������
 * ��������(msglvl_).
 */

struct Message {
  std::string text_;
  MsgLvl msglvl_;
};

/*
 * ����� ���������� Logger.
 * ����� ���������� �� �������� ��������(Singleton).
 *
 * ����� init, ��������� ������������ ��������� ������. ��������� ��� ������� �
 * ������� �� ���������. ���� ����� �������� �� "���������� ��� �������������
 * ������ ��������� ��������� ���������: a. ��� ����� �������. b. �������
 * �������� ��������� �� ���������. ��������� � ������� ���� ��������� �� ������
 * ������������ � ������. ������� ������������� �������� � ������� ������������
 * � ��������� �������. ���������� ���� ������� ��������." �� ��.
 *
 * ����� log �������� �� ������ ��������� � ������ (��������� ���������).
 *
 * ����� change_lvl ��������� �������� ������� �� ��������� (��������� �������).
 *
 * ����� get_default_lvl ���������� ������� ������� �� ���������. ����� ���
 * ��������� � ������������ �������� �������� �� ������������ � ���������
 * ������� � ������\�� ������ � ������.
 *
 * ����������� Logger. ��������� ��� ������� � ������� �� ���������. ��������
 * ��������� ��� ����������� �������� ��������.
 *
 * ���������� Logger. ����������� ������ ��� ���� default_msg_lvl_.
 *
 * ����� get_time. ��������� ������ � ������� ��������. ������������ � log ���
 * ������������ ������ �������.
 *
 * � ������ ������������ ������ �� ����������� ������� ������ ��������
 * ���������� � �������������� �����������.
 *
 * init_root_ - ������ ������������ ��������� ������.
 *
 * journal_name_ - ��� �������.
 *
 * default_msg_lvl_ - ������� �� ���������.
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