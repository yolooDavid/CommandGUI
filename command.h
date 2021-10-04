/**
 * @author Zhen Tang (student number: 251027684)
 * @date   Oct 3, 2021
 * @brief  A Command class used to encapsulate and abstractly represent
 *         the commands that this program is executing.
 */

#pragma once

#include <QString>

class Command {
public:
  Command(const QString command_text);
  ~Command();

  void execute();

  QString get_command_text() { return m_command_text; }
  void set_command_text(const QString value) { m_command_text = value; }
  QString get_result() { return m_result; }
  QString get_return_code() { return m_return_code; }

private:
  QString m_command_text;
  QString m_result;
  QString m_return_code;
};
