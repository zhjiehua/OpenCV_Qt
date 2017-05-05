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

	/** @brief ����ͼƬ����ɫλ��ʶ������������ɫ�����š�
		
	���flag=1�����ʼ���������ݣ���ʱ������������ܼ�������ͬ�����ʾ���ĳ�ʼ��ʧ�ܣ�����-1��

	@param fileName ͼƬ����
	@param flags	0������ʼ����������
					1����ʼ����������
	*/
	int Process(const String& fileName, int flag = 0);

	int ProcessRed(const String& fileName);
	int ProcessGreen(const String& fileName);

private:

	void SetMassCentroid(vector<Point2f>& mc, Rect &re);
	void readIniData(void);

	HSVThreshod_TypeDef redHSVThreshod; //��ɫ��ֵ
	HSVThreshod_TypeDef greenHSVThreshod; //��ɫ��ֵ
	double gaussianBlurSigmaX;//��˹�˲�����
	vector<Point2f> massCentroid; //����
	Rect massCentroidRange; //���Ŀ�ƫ��λ��
	int levelCnt; //�ܼ���

	QSettings *configIni; //ini�ļ�����ָ��
	
public slots:
	void levelCntChanged(const QString &str);
};

#endif