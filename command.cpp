/**
 * @author Zhen Tang (student number: 251027684)
 * @date   Oct 3, 2021
 * @brief  A Command class used to encapsulate and abstractly represent
 *         the commands that this program is executing.
 */

#include "command.h"

#include <boost/process.hpp>

using namespace boost::process;

/**
 * @name   Command::Command
 * @brief  Initializes the Command object with the provided command text.
 * @param  command_text: the command text to be executed
 */
Command::Command(const QString command_text)
  : m_command_text(command_text),
    m_result(""),
    m_return_code("0") {
}

/**
 * @name   Command::~Command
 * @brief  Destructs the Command object.
 */
Command::~Command() {
}

/**
 * @name   Command::execute
 * @brief  Executes the provided command text and captures the output and the return code.
 */
void Command::execute() {
  try {
    // Input pipe stream
    ipstream ps;
    // Redirect standard output and error to ps
    child c(m_command_text.toStdString(), (std_out & std_err) > ps);

    // Transfer all the contents (lines) from ps to ss
    std::stringstream ss;
    ss << ps.rdbuf();

    // Wait for the child process to exit
    c.wait();

    m_result = QString::fromStdString(ss.str());
    m_return_code = QString::number(c.exit_code());

  } catch(process_error) {
    // If the user tries to execute a command that doesn't exist,
    // catch this exception and set the result output text to indicate the error and set the return code to -1
    m_result = "command not found";
    m_return_code = "-1";
  }
}
