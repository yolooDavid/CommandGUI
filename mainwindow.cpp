#include "mainwindow.h"
#include "command.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  m_command_label = new QLabel("Command:");
  m_command_text = new QLineEdit("");
  m_execute = new QPushButton("Execute");
  m_output_label = new QLabel("Output");
  m_output_text = new QTextEdit("");
  m_exit_status_label = new QLabel("Exit Status:");
  m_bar = new QFrame();
  m_bar->setFrameShape(QFrame::HLine);
  m_bar->setFrameShadow(QFrame::Sunken);
  m_exit_status = new QLabel("0");
  m_history_label = new QLabel("History");
  m_history_list = new QListWidget();

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

  m_centralWidget = new QWidget();
  m_centralWidget->setLayout(m_layout);
  setCentralWidget(m_centralWidget);

  setWindowTitle("CommandGUI");
  resize(600, 800);

  connect(m_execute, &QPushButton::released, this, &MainWindow::handleExecute);
  connect(m_command_text, &QLineEdit::returnPressed, this, &MainWindow::handleExecute);
}

void MainWindow::handleExecute() {
  Command command(m_command_text->text());
  command.execute();
  m_output_text->setText(command.get_result());
  m_exit_status->setText(command.get_return_code());
}
