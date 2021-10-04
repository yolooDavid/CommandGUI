#include "command.h"

#include <boost/process.hpp>
#include <iostream>

using namespace boost::process;

Command::Command(QString command_text)
  : m_command_text(command_text) {
}

Command::~Command() {
}

void Command::execute() {
  ipstream ps;
  child c(m_command_text.toStdString(), (std_out & std_err) > ps);

  std::stringstream ss;
  ss << ps.rdbuf();
  c.wait();

  m_result = QString::fromStdString(ss.str());
  m_return_code = QString::number(c.exit_code());
}
