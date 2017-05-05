#ifndef COLORPOSDISCLASS_H
#define COLORPOSDISCLASS_H

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#include <iostream>
using namespace std;

#include <QObject>
#include <QSettings> 
#include <QFile>
#include <QDebug>

typedef struct
{
	int lowH;
	int highH;
	int lowS; 
	int highS;
	int lowV;
	int highV;
}HSVThreshod_TypeDef;

typedef enum
{
	HSVTHRESHOLD_RED = 0,
	HSVTHRESHOLD_GREEN,
}HSVThreshod_ColorEnum;

class ColorPosDis :  public QObject
{
	Q_OBJECT

public:
	ColorPosDis();
	~ColorPosDis();
	void SetHSVThreshod(HSVThreshod_TypeDef& threshod, HSVThreshod_ColorEnum color);
	void SetFilterPara(double para);
	int SetLevelCnt(int cnt);

	/** @brief 处理图片，颜色位置识别，正常返回绿色块的序号。
		
	如果flag=1，则初始化重心数据，这时如果重心数与总级数不相同，则表示重心初始化失败，返回-1。

	@param fileName 图片名称
	@param flags	0：不初始化重心数据
					1：初始化重心数据
	*/
	int Process(const String& fileName, int flag = 0);

	int ProcessRed(const String& fileName);
	int ProcessGreen(const String& fileName);

private:

	void SetMassCentroid(vector<Point2f>& mc, Rect &re);
	void readIniData(void);

	HSVThreshod_TypeDef redHSVThreshod; //红色阈值
	HSVThreshod_TypeDef greenHSVThreshod; //绿色阈值
	double gaussianBlurSigmaX;//高斯滤波参数
	vector<Point2f> massCentroid; //重心
	Rect massCentroidRange; //重心可偏移位置
	int levelCnt; //总级数

	QSettings *configIni; //ini文件操作指针
	
public slots:
	void levelCntChanged(const QString &str);
};

#endif