#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <snd_facility.h>
#include <ntw_facility.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void initializeVariables();
    Snd_facility *audio;
    Ntw_facility *network;

signals:
    void start_recording_sig();
    void stop_recording_sig();

private slots:
    void on_recButton_pressed();
    void on_recButton_released();
};

#endif // MAINWINDOW_H
