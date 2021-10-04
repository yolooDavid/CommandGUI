#include "command.h"

#include <boost/process.hpp>

using namespace boost::process;

Command::Command(const QString command_text)
  : m_command_text(command_text) {
}

Command::~Command() {
}

void Command::execute() {
  try {
    ipstream ps;
    child c(m_command_text.toStdString(), (std_out & std_err) > ps);

    std::stringstream ss;
    ss << ps.rdbuf();
    c.wait();

    m_result = QString::fromStdString(ss.str());
    m_return_code = QString::number(c.exit_code());
  } catch(process_error) {
    m_result = "command not found";
    m_return_code = "-1";
  }
}
