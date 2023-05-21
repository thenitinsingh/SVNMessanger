#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QWebSocket>
#include <QFlags>

//import Qt3D.Input 2.0
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    connect(ui->send,SIGNAL(clicked()),this,SLOT(onsendclicked()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(OnreadyRead()));
   //connect(socket, SIGNAL(readyRead()),this, SLOT(ping()));
   //QTimer *timer = new QTimer(this);
   //connect(timer, SIGNAL(timeout()), this, SLOT(ping()));
   //timer->start(1000);

    initSocket();
}
void MainWindow::ping()
{
    qDebug()<<"Inside ping";
    ui->radioButton->setChecked(true);

   /* if(isValid())
    {
        qDebug()<<"Inside ping";
    }*/
}
void MainWindow::initSocket()
{
   /*check if socket is created and its not null*/
    // bind the socket if its available and check the return value
    //if return value is correct make a flag of socket binded successfully
     socket->bind(QHostAddress::LocalHost, rxportnum);

}
void MainWindow::OnreadyRead()
{
    QColor color = ui->textEdit_display->textColor();
    ui->textEdit_display->setTextColor(Qt::blue);
    QHostAddress sender;
    quint16 senderPort;
    QByteArray datagram;
    QString dataString;
    dataString.clear();
    qDebug()<<"data rx";
    while (socket->hasPendingDatagrams())
    {
              QNetworkDatagram datagram = socket->receiveDatagram();
              dataString.append(datagram.data());
              qDebug()<< "dataString"<<dataString;
    }
    ui->textEdit_display->setAlignment(Qt::AlignRight );

    ui->textEdit_display->append("<Receiver> "+dataString);

    dataString.clear();
}
void MainWindow ::onsendclicked()
{
    QColor color = ui->textEdit_display->textColor();
    ui->textEdit_display->setTextColor(Qt::red);
    QByteArray dataStringByteArray;
    dataStringByteArray.clear();
    inputString=ui->msgbar->text();
    dataStringByteArray.append(inputString);

    txmadd.setAddress(ui->lineEdit_Ip->text());
    portnum = ui->lineEdit_port->text().toInt();

    int i =socket->writeDatagram(dataStringByteArray,txmadd,portnum);
    qDebug()<<txmadd<<i;

    dataStringByteArray.clear();
    ui->textEdit_display->setAlignment(Qt::AlignLeft );
    ui->textEdit_display->append("<Me> "+inputString);
    inputString.clear();
    ui->msgbar->clear();
}
MainWindow::~MainWindow()
{
    delete ui;
}

