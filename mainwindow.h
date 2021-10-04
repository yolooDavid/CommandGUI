/**
 * @author Zhen Tang (student number: 251027684)
 * @date   Oct 3, 2021
 * @brief  The graphical interface for the main window.
 */

#pragma once

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

#include "command.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

// Forbid copy
private:
  MainWindow(const MainWindow &);

private slots:
  void handleExecute();
  void handleHistorySwitched();

private:
  std::vector<Command> m_commands;

  // Widgets
  QLabel *m_command_label;
  QLineEdit *m_command_text;
  QPushButton *m_execute;
  QLabel *m_output_label;
  QTextEdit *m_output_text;
  QLabel *m_exit_status_label;
  QLabel *m_exit_status;
  QFrame *m_bar;
  QLabel *m_history_label;
  QListWidget *m_history_list;
  QGridLayout *m_layout;
  QWidget *m_centralWidget;
};
