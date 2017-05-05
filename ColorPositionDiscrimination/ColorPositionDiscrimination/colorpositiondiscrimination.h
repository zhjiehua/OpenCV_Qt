#ifndef COLORPOSITIONDISCRIMINATION_H
#define COLORPOSITIONDISCRIMINATION_H

#include <QtGui/QMainWindow>
#include "ui_colorpositiondiscrimination.h"
#include <QTimer>
#include "Communication.h"
#include "ColorPosDisClass.h"

class ColorPositionDiscrimination : public QMainWindow
{
	Q_OBJECT

public:
	ColorPositionDiscrimination(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ColorPositionDiscrimination();

public slots:
	void timerFinish();
	void setLevel(int lev);
	void setFilterPara(int para);
	void processPic(void);

private:
	Ui::ColorPositionDiscriminationClass ui;

	QTimer *t;

	ColorPosDis *pColPosDis;
	Communication *pCom;
};

#endif // COLORPOSITIONDISCRIMINATION_H
