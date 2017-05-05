#include "Communication.h"

QString protocol[] = 
{
	"l,",
	"c,",
};

Communication::Communication(quint32 port)
{
	tcpPort = port;
	tcpSocketServer = new QTcpServer();
	//tcpSocketServer->listen(QHostAddress("127.0.0.1"), port);
	if(!tcpSocketServer->listen(QHostAddress::Any, port))
	{
		qDebug() << "listen error: " << tcpSocketServer->errorString();  
        return; 
	}
	else
	{
		qDebug() << "server start is ok!";
	}
	connect(tcpSocketServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

Communication::~Communication()
{
	delete tcpSocketServer;
}

void Communication::acceptConnection()
{
	tcpSocketClientConnection = tcpSocketServer->nextPendingConnection();
	if( NULL == tcpSocketClientConnection )  
    {  
        qDebug() << "socket is error";  
        return ;
    } 
	connect(tcpSocketClientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void Communication::readClient()
{
	QString buf = tcpSocketClientConnection->readAll();
	//����
	//char buf[100];
	//memset(buf, 0, 100);
	//tcpSocketClientConnection->read(buf,100);

	switch(buf.at(0).toAscii())
	{
	case 'l':
	case 'L':
		{
		qDebug() << "It's setting Level:" << buf;

		QString s = buf.section(',', 1, 1).trimmed();//��ȡ���ź��������
		emit(setLevel(s.toInt())); //���ü���
		break;
		}
	case 'f':
	case 'F':
		{
		qDebug() << "It's Setting Filter Parameter:" << buf;

		QString s = buf.section(',', 1, 1).trimmed();//��ȡ���ź��������
		emit(setFilterPara(s.toInt())); //���ü���
		break;
		}
	case 'c':
	case 'C':
		qDebug() << "It's Processing Picture:" << buf;

		emit(processPic());//����ͼƬ
		break;
	default:
		qDebug() << "socket data is error!" << buf;
		break;
	}
}	
