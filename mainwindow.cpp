#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeVariables();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeVariables()
{
    //instantiating the modules and connecting them
    audio = new Snd_facility(this);

    connect(this,SIGNAL(start_recording_sig()),audio,SLOT(recButtonPressed()));
    connect(this,SIGNAL(stop_recording_sig()),audio,SLOT(recButtonReleased()));
    network = new Ntw_facility(this);

    connect(this,SIGNAL(start_recording_sig()),network,SLOT(recButton_pressed()));
    connect(this,SIGNAL(stop_recording_sig()), network,SLOT(recButton_released()));

    connect(audio,SIGNAL(chunk_dataOutput(QByteArray)),network,SLOT(chunkAudioOutput_ready(QByteArray)));

    connect(network,SIGNAL(audioPacket(QByteArray)),audio,SLOT(playAudioPacket(QByteArray)));

    // connect(audio,SIGNAL(not_receiving_state()),network,SLOT(stop_receiving()));

    // connect(audio,SIGNAL(receiving_state()),network,SLOT(restart_receiving()));

}

//send a signal to the audio module to start recording from microphone
void MainWindow::on_recButton_pressed()
{
    emit start_recording_sig();
}

//send a signal to the audio to stop recording from microphone
void MainWindow::on_recButton_released()
{
    emit stop_recording_sig();
}
