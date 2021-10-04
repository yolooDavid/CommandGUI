/**
 * @author Zhen Tang (student number: 251027684)
 * @date   Oct 3, 2021
 * @brief  The graphical interface for the main window.
 */

#include "mainwindow.h"

#include <QFont>
#include <QFontDatabase>

/**
 * @name   MainWindow::MainWindow
 * @brief  Initializes the MainWindow and its widgets
 * @param  parent: the optional parent QWidget of this MainWindow
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  m_command_label = new QLabel("Command:");
  m_command_text = new QLineEdit("");
  m_execute = new QPushButton("Execute");
  m_output_label = new QLabel("Output");
  m_output_text = new QTextEdit("");
  m_exit_status_label = new QLabel("Exit Status:");
  m_bar = new QFrame();
  m_exit_status = new QLabel("0");
  m_history_label = new QLabel("History");
  m_history_list = new QListWidget();

  // Equalize the width of all characters
  const QFont fixed_font = QFontDatabase::systemFont(QFontDatabase::FixedFont);

  m_command_text->setFont(fixed_font);
  m_output_text->setFont(fixed_font);
  m_output_text->setReadOnly(true);
  m_bar->setFrameShape(QFrame::HLine);  // Add a horizontal bar
  m_bar->setFrameShadow(QFrame::Sunken);
  m_history_list->setFont(fixed_font);

  // Automatically layout the widgets
  m_layout = new QGridLayout();
  m_layout->addWidget(m_command_label, 0, 0);
  m_layout->addWidget(m_command_text, 0, 1);
  m_layout->addWidget(m_execute, 0, 2);
  m_layout->addWidget(m_output_label, 1, 0, 1, 3);
  m_layout->addWidget(m_output_text, 2, 0, 1, 3);
  m_layout->addWidget(m_exit_status_label, 3, 0);
  m_layout->addWidget(m_exit_status, 3, 1);
  m_layout->addWidget(m_bar, 4, 0, 1, 3);
  m_layout->addWidget(m_history_label, 5, 0);
  m_layout->addWidget(m_history_list, 6, 0, 1, 3);

  // QMainWindow already has a layout.
  // To set a custom layout, we need to assign the layout to a widget,
  // and set the widget as the central widget of the window.
  m_centralWidget = new QWidget();
  m_centralWidget->setLayout(m_layout);
  setCentralWidget(m_centralWidget);

  setWindowTitle("CommandGUI");
  resize(600, 800);

  // Execute command when execute button is clicked
  connect(m_execute, &QPushButton::released, this, &MainWindow::handleExecute);
  // Execute command when return is pressed
  connect(m_command_text, &QLineEdit::returnPressed, this, &MainWindow::handleExecute);
  // Update command result when a different item is selected in the history list
  connect(m_history_list, &QListWidget::currentRowChanged, this, &MainWindow::handleHistorySwitched);
}

/**
 * @name   MainWindow::handleExecute
 * @brief  Retrieves the command text from the GUI, executes it,
 *         and adds the command along with its result to the history list.
 */
void MainWindow::handleExecute() {
  Command command(m_command_text->text());
  command.execute();

  // Generate a string to be displayed in the history list
  const QString next_index = QString::number(m_commands.size() + 1);
  const QString history_item_string = QString("%1. %2 (%3)").arg(next_index, command.get_command_text(), command.get_return_code());

  m_commands.push_back(command);
  m_history_list->addItem(history_item_string);

  // Select the last item in the history list, also trigger currentRowChanged
  m_history_list->setCurrentRow(m_commands.size() - 1);
}

/**
 * @name   MainWindow::handleHistorySwitched
 * @brief  Updates the command text, the result, and the return code
 *         based on the currently selected command in the history list.
 */
void MainWindow::handleHistorySwitched() {
  const int row = m_history_list->currentRow();
  m_command_text->setText(m_commands[row].get_command_text());
  m_output_text->setText(m_commands[row].get_result());
  m_exit_status->setText(m_commands[row].get_return_code());
}
