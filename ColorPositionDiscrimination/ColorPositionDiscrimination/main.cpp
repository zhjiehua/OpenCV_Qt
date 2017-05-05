#include "colorpositiondiscrimination.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ColorPositionDiscrimination w;
	QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
	//w.show();
	return a.exec();
}
