#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QUdpSocket>
#include <QNetworkDatagram>
#define rxportnum 5000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QString inputString;
    void SayHello();
    QUdpSocket *socket;
    QKeyEvent *event;
    QTimer *timer;
    /*QUdpSocket udpSocket;
    QNetworkDatagram datagram;

    bool hasPendingDatagrams;*/
    ~MainWindow();
     QHostAddress txmadd;
     int portnum;
public slots:
    void onsendclicked();
    void OnreadyRead();
    //void OnradioButtonClicked();
    void ping();


private:
    Ui::MainWindow *ui;
    void initSocket();
};


#endif // MAINWINDOW_H
