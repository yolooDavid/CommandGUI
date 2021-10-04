#pragma once

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

private slots:
  void handleExecute();

private:
  QWidget *m_centralWidget;
  QGridLayout *m_layout;
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
};
