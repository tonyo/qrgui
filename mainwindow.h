#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui 
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    static const int MAX_INPUT_LEN = 300;


  public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    private slots:
      void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_passwordBox_toggled(bool checked);

  private:
    Ui::MainWindow* ui;

    void initElements();
    void initShotrcuts();
    void showMsgBoxError(const char* str);
};

#endif // MAINWINDOW_H
