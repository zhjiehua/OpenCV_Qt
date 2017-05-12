#include "colorpositiondiscrimination.h"
#include "ColorPosDisClass.h"

//#define TEST_MODE

#ifndef TEST_MODE
#define CALIBRATION_PICTURE_NAME "cal.jpg"
#define CURRENT_PICTURE_NAME "cur.jpg"
#else
#define CALIBRATION_PICTURE_NAME  "0_new.jpg"
#endif

ColorPositionDiscrimination::ColorPositionDiscrimination(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	//ui.setupUi(this);

	//t = new QTimer();
	//connect( t, SIGNAL(timeout()),this, SLOT(timerFinish()) );
	//t->start(1000); // 2秒单触发定时器

	pCom = new Communication(8885);
	pColPosDis = new ColorPosDis();

	//connect(ui.levelCntEdit, SIGNAL(dataChanged(const QString &)), pColPosDis, SLOT(levelCntChanged(const QString &)));

	connect(pCom, SIGNAL(setLevel(int)), this, SLOT(setLevel(int)));
	connect(pCom, SIGNAL(setFilterPara(int)), this, SLOT(setFilterPara(int)));
	connect(pCom, SIGNAL(processPic()), this, SLOT(processPic()));
}

ColorPositionDiscrimination::~ColorPositionDiscrimination()
{
	delete pColPosDis;
	delete pCom;
	delete t;
}

void ColorPositionDiscrimination::timerFinish()
{
	static int flag = 0;
	static int flag2 = 0;
	if(!flag)
	{
		int pos;
		flag = 1;
		if(!flag2)
		{
			flag2 = 1;
			pos = pColPosDis->ProcessGreen("6.png");
		}
		else
		{
			flag2 = 0;
			pos = pColPosDis->ProcessGreen("6.png");
		}
		qDebug() << "the pos is " << pos; 
		ui.levelLabel->setNum(pos);

		flag = 0;
	}
}

void ColorPositionDiscrimination::setLevel(int lev)
{
	int oldLevel = pColPosDis->SetLevelCnt(lev); //记录级数，如果处理图片后颜色块与该数目不对，则需要将该数据修改回来

	//识别块个数颜色，记录颜色块坐标信息
	//int ret = pColPosDis->Process(CALIBRATION_PICTURE_NAME, 1);
	int ret = pColPosDis->ProcessRed(CALIBRATION_PICTURE_NAME);
	if(ret == -1)
	{
		pColPosDis->SetLevelCnt(oldLevel);
		qDebug() << "Error : The picture red count is not equal to level count!";
	}
	else
		ret = lev;

	QString str = protocol[0] + QString::number(ret);
	pCom->tcpSocketClientConnection->write(str.toAscii());
}

void ColorPositionDiscrimination::setFilterPara(int para)
{
	pColPosDis->SetFilterPara(para);
}

void ColorPositionDiscrimination::processPic(void)
{
	int ret = 0;

#ifdef TEST_MODE
	static int i = 0;
	QString s = QString::number(i) + "_new.jpg";
	//ret = pColPosDis->Process(s.toStdString());
	ret = pColPosDis->ProcessGreen(s.toStdString());
	qDebug() <<	s;
	i++;
	if(i>4)
		i = 0;
#else
	//ret = pColPosDis->Process(CURRENT_PICTURE_NAME);
	ret = pColPosDis->ProcessGreen(CURRENT_PICTURE_NAME);
#endif

	QString str = protocol[1] + QString::number(ret);
	pCom->tcpSocketClientConnection->write(str.toAscii());
}