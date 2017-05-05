#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <iostream>
using namespace std;

#include <QObject>
#include <QSettings> 
#include <QFile>
#include <QDebug>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class Communication :  public QObject
{
	Q_OBJECT

public:
	Communication(quint32 port);
	~Communication();

	QTcpSocket *tcpSocketClientConnection;
private:
	quint32 tcpPort;
	QTcpServer *tcpSocketServer;

public slots:
	void acceptConnection();
	void readClient();

signals:
	void setLevel(int lev);
	void setFilterPara(int para);
	void processPic(void);

};

extern QString protocol[];

#endif