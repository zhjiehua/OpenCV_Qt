#include "ColorPosDisClass.h"

void ColorPosDis::readIniData(void)
{
		gaussianBlurSigmaX = configIni->value("/openCV/gaussianBlurSigmaX").toDouble();  
		redHSVThreshod.highH = configIni->value("/openCV/redHSVThreshod.highH").toInt();
		redHSVThreshod.highS = configIni->value("/openCV/redHSVThreshod.highS").toInt();
		redHSVThreshod.highV = configIni->value("/openCV/redHSVThreshod.highV").toInt();
		redHSVThreshod.lowH = configIni->value("/openCV/redHSVThreshod.lowH").toInt();
		redHSVThreshod.lowS = configIni->value("/openCV/redHSVThreshod.lowS").toInt();
		redHSVThreshod.lowV = configIni->value("/openCV/redHSVThreshod.lowV").toInt();

		greenHSVThreshod.highH = configIni->value("/openCV/greenHSVThreshod.highH").toInt();
		greenHSVThreshod.highS = configIni->value("/openCV/greenHSVThreshod.highS").toInt();
		greenHSVThreshod.highV = configIni->value("/openCV/greenHSVThreshod.highV").toInt();
		greenHSVThreshod.lowH = configIni->value("/openCV/greenHSVThreshod.lowH").toInt();
		greenHSVThreshod.lowS = configIni->value("/openCV/greenHSVThreshod.lowS").toInt();
		greenHSVThreshod.lowV = configIni->value("/openCV/greenHSVThreshod.lowV").toInt();

		//��ȡ��ɫλ��ʶ�����
		levelCnt = configIni->value("colorPosDis/levelCnt").toInt();
		for(int i=1; i<= levelCnt; i++)
		{
			Point2f mc;

			QString strX = QString("colorPosDis/massCentroid%1.x").arg(i);
			QString strY = QString("colorPosDis/massCentroid%1.y").arg(i);
			mc.x = configIni->value(strX).toFloat();
			mc.y = configIni->value(strY).toFloat();

			massCentroid.push_back(mc);
		}

		massCentroidRange.width = configIni->value("colorPosDis/massCentroidRange.width").toInt();
		massCentroidRange.height = configIni->value("colorPosDis/massCentroidRange.height").toInt();
}

ColorPosDis::ColorPosDis()
{
	//Qt��ʹ��QSettings���дini�ļ�  

	//���ini�ļ��������ȡ�ļ����ݣ��������´���
	if(QFile::exists("./parameter.ini"))
	{
		qDebug() << "the file parameter.ini exists!\n";

		configIni = new QSettings("parameter.ini", QSettings::IniFormat);

		//��ȡini�ļ��е����ݵ��ڴ� 
		readIniData();
	}
	else
	{
		qDebug() << "the file parameter.ini is missing!\n";

		//QSettings���캯���ĵ�һ��������ini�ļ���·��,�ڶ���������ʾ���ini�ļ�,��������������ȱʡ  
		configIni = new QSettings("parameter.ini", QSettings::IniFormat);  
		//��ini�ļ���д������,setValue���������������Ǽ�ֵ��  
		//��ini�ļ��ĵ�һ����д������,openCV���µĵ�һ������  
		configIni->setValue("/openCV/gaussianBlurSigmaX", "5");  
		//��ini�ļ��ĵ�һ����д������,openCV���µĵڶ�������  
		configIni->setValue("/openCV/redHSVThreshod.highH", "9");
		configIni->setValue("/openCV/redHSVThreshod.highS", "255");
		configIni->setValue("/openCV/redHSVThreshod.highV", "255");
		configIni->setValue("/openCV/redHSVThreshod.lowH", "0");
		configIni->setValue("/openCV/redHSVThreshod.lowS", "120");
		configIni->setValue("/openCV/redHSVThreshod.lowV", "50");

		configIni->setValue("/openCV/greenHSVThreshod.highH", "92");
		configIni->setValue("/openCV/greenHSVThreshod.highS", "255");
		configIni->setValue("/openCV/greenHSVThreshod.highV", "255");
		configIni->setValue("/openCV/greenHSVThreshod.lowH", "59");
		configIni->setValue("/openCV/greenHSVThreshod.lowS", "120");
		configIni->setValue("/openCV/greenHSVThreshod.lowV", "130");

		//��ini�ļ��ĵڶ�����д������,colorPosDis���µĵ�һ������  
		configIni->setValue("colorPosDis/levelCnt", "10");
		//configIni->setValue("colorPosDis/levelCnt", "9");
		configIni->setValue("colorPosDis/massCentroid1.x", "690");
		configIni->setValue("colorPosDis/massCentroid1.y", "178");
		configIni->setValue("colorPosDis/massCentroid2.x", "1065");
		configIni->setValue("colorPosDis/massCentroid2.y", "188");
		configIni->setValue("colorPosDis/massCentroid3.x", "690");
		configIni->setValue("colorPosDis/massCentroid3.y", "289");
		configIni->setValue("colorPosDis/massCentroid4.x", "1059");
		configIni->setValue("colorPosDis/massCentroid4.y", "295");
		configIni->setValue("colorPosDis/massCentroid5.x", "638");
		configIni->setValue("colorPosDis/massCentroid5.y", "395");
		configIni->setValue("colorPosDis/massCentroid6.x", "1051");
		configIni->setValue("colorPosDis/massCentroid6.y", "402");
		configIni->setValue("colorPosDis/massCentroid7.x", "676");
		configIni->setValue("colorPosDis/massCentroid7.y", "506");
		configIni->setValue("colorPosDis/massCentroid8.x", "1042");
		configIni->setValue("colorPosDis/massCentroid8.y", "506");
		configIni->setValue("colorPosDis/massCentroid9.x", "676");
		configIni->setValue("colorPosDis/massCentroid9.y", "611");
		configIni->setValue("colorPosDis/massCentroid10.x", "1031");
		configIni->setValue("colorPosDis/massCentroid10.y", "618");

		configIni->setValue("colorPosDis/massCentroidRange.width", "150");
		configIni->setValue("colorPosDis/massCentroidRange.height", "50");

		//��ȡini�ļ��е����ݵ��ڴ� 
		readIniData();
	}
}

ColorPosDis::~ColorPosDis()
{
	delete configIni;
}

void ColorPosDis::SetHSVThreshod(HSVThreshod_TypeDef& threshod, HSVThreshod_ColorEnum color)
{
	if(color == HSVTHRESHOLD_RED)
	{
		redHSVThreshod.highH = threshod.highH;
		redHSVThreshod.highS = threshod.highS;
		redHSVThreshod.highV = threshod.highV;
		redHSVThreshod.lowH = threshod.lowH;
		redHSVThreshod.lowS = threshod.lowS;
		redHSVThreshod.lowV = threshod.lowV;

		configIni->setValue("/openCV/redHSVThreshod.highH", threshod.highH);
		configIni->setValue("/openCV/redHSVThreshod.highS", threshod.highS);
		configIni->setValue("/openCV/redHSVThreshod.highV", threshod.highV);
		configIni->setValue("/openCV/redHSVThreshod.lowH", threshod.lowH);
		configIni->setValue("/openCV/redHSVThreshod.lowS", threshod.lowS);
		configIni->setValue("/openCV/redHSVThreshod.lowV", threshod.lowV);
	}
	else if(color == HSVTHRESHOLD_GREEN)
	{
		greenHSVThreshod.highH = threshod.highH;
		greenHSVThreshod.highS = threshod.highS;
		greenHSVThreshod.highV = threshod.highV;
		greenHSVThreshod.lowH = threshod.lowH;
		greenHSVThreshod.lowS = threshod.lowS;
		greenHSVThreshod.lowV = threshod.lowV;

		configIni->setValue("/openCV/greenHSVThreshod.highH", threshod.highH);
		configIni->setValue("/openCV/greenHSVThreshod.highS", threshod.highS);
		configIni->setValue("/openCV/greenHSVThreshod.highV", threshod.highV);
		configIni->setValue("/openCV/greenHSVThreshod.lowH", threshod.lowH);
		configIni->setValue("/openCV/greenHSVThreshod.lowS", threshod.lowS);
		configIni->setValue("/openCV/greenHSVThreshod.lowV", threshod.lowV);
	}
}

void ColorPosDis::SetFilterPara(double para)
{
	gaussianBlurSigmaX = para;
	
	configIni->setValue("/openCV/gaussianBlurSigmaX", para);
}

int ColorPosDis::SetLevelCnt(int cnt)
{
	int oldLevelCnt = levelCnt;

	levelCnt = cnt;

	configIni->setValue("colorPosDis/levelCnt", cnt);

	return oldLevelCnt;
}

void ColorPosDis::SetMassCentroid(vector<Point2f>& mc, Rect &re)
{
	massCentroid.clear();
	for( int i = 0; i < mc.size(); i++ ) 	
	{ 
		massCentroid.push_back(mc.at(i));

		QString strX = QString("colorPosDis/massCentroid%1.x").arg(i+1);
		QString strY = QString("colorPosDis/massCentroid%1.y").arg(i+1);
		configIni->setValue(strX, float(mc.at(i).x));
		configIni->setValue(strY, float(mc.at(i).y));

		qDebug() << strX << " = " << mc.at(i).x;
		qDebug() << strY << " = " << mc.at(i).y;
	}

	massCentroidRange.width = re.width;
	massCentroidRange.height = re.height;
	configIni->setValue("colorPosDis/massCentroidRange.width", massCentroidRange.width);
	configIni->setValue("colorPosDis/massCentroidRange.height", massCentroidRange.height);
}

//#define SHOWIMAGE
int ColorPosDis::Process(const String& fileName, int flag)
{
	//���ļ�������ͼ��
	Mat srcImage = imread(fileName, IMREAD_COLOR);

	//�˲�
	GaussianBlur(srcImage, srcImage, cv::Size(0, 0), gaussianBlurSigmaX);

#ifdef SHOWIMAGE
	const char *pstrSrcWinTitle = "ԭͼ";
	const char *pstrHSVWinTitle = "HSVͼ";
	const char *pstrDestWinTitle = "Ŀ��ʶ��ͼ";
	const char *pstrDestWinTitle2 = "Ŀ��ʶ��ͼ2";
	const char *pstrContoursWinTitle = "����ͼ";

	//��������
	namedWindow(pstrSrcWinTitle, CV_WINDOW_AUTOSIZE);
	imshow(pstrSrcWinTitle, srcImage);
#endif

	/**************************��ɫʶ��************************/
	Mat imgHSV;
	vector<Mat> hsvSplit;
	cvtColor(srcImage, imgHSV,  COLOR_BGR2HSV);//Convert the captured frame from BGR to HSV

	//��Ϊ���Ƕ�ȡ���ǲ�ɫͼ��ֱ��ͼ���⻯��Ҫ��HSV�ռ���
	split(imgHSV, hsvSplit);
	equalizeHist(hsvSplit[2],hsvSplit[2]);
	merge(hsvSplit,imgHSV);

	//��ָ����������ʾͼ��
	//imshow(pstrHSVWinTitle, imgHSV);//show the original image

	Mat imgThresholdedRed, imgThresholdedGreen;

	inRange(imgHSV, Scalar(redHSVThreshod.lowH, redHSVThreshod.lowS, redHSVThreshod.lowV), 
		Scalar(redHSVThreshod.highH, redHSVThreshod.highS, redHSVThreshod.highV), imgThresholdedRed); //Threshold the image
	inRange(imgHSV, Scalar(greenHSVThreshod.lowH, greenHSVThreshod.lowS, greenHSVThreshod.lowV), 
		Scalar(greenHSVThreshod.highH, greenHSVThreshod.highS, greenHSVThreshod.highV), imgThresholdedGreen); //Threshold the image

	//������ (ȥ��һЩ���)
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(imgThresholdedRed, imgThresholdedRed, MORPH_OPEN, element);
	morphologyEx(imgThresholdedGreen, imgThresholdedGreen, MORPH_CLOSE, element);

	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholdedRed, imgThresholdedRed, MORPH_CLOSE, element);
	morphologyEx(imgThresholdedGreen, imgThresholdedGreen, MORPH_CLOSE, element);

#ifdef SHOWIMAGE
	imshow(pstrDestWinTitle, imgThresholdedRed);//show the thresholded image
	imshow(pstrDestWinTitle2, imgThresholdedGreen);//show the thresholded image
#endif
	/**************************��ɫʶ�����************************/

	/*************************����ʶ��**************************/
	int ret = 0;
	vector<vector<Point> > contours; 	
	vector<Vec4i> hierarchy;
	Rect re;
	//��������
	if(flag)
		findContours( imgThresholdedRed, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	else
		findContours( imgThresholdedGreen, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	qDebug() << "contours.size() = " << contours.size() << endl;

	if(contours.size() <= 0)
	{
		if(flag)
			return -1;
		else
			return 0;
	}

	//һ����ɫ��ĸ߶Ⱥͳ���
	re = boundingRect(contours.at(0));

	//���������� 	
	vector<Moments> mu(contours.size() ); 	
	for( int i = 0; i < contours.size(); i++ ) 	
	{ 
		mu[i] = moments( contours[i], false ); 
	} 	
	//�������������� 	
	vector<Point2f> mc( contours.size() ); 	
	for( int i = 0; i < contours.size(); i++) 	
	{ 
		mc[i] = Point2d( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
	}
	
	//�����ɫ��
	if(!flag)
	{
		if(contours.size() > 1)
		{
			ret = -1;
		}
		else
		{
			for(int j = 0; j < levelCnt; j++)
			{
				if(abs(massCentroid.at(j).x - mc[0].x) < massCentroidRange.width
					&& abs(massCentroid.at(j).y - mc[0].y) < massCentroidRange.height)
				{
					ret = j+1;
					break;
				}
			}
		}
	}

	//����ɫ�飬ͬʱ������������
	if(flag)
	{
		//��������
		for(int i = 0; i < contours.size()-1; i++)
		{
			for(int j = i+1; j < contours.size(); j++)
			{
				if(mc.at(i).y - mc.at(j).y > re.height)
				{
					Point2f temp = mc.at(i);
					mc.at(i) = mc.at(j);
					mc.at(j) = temp;
				}
			}
		}
		for(int i = 0; i < contours.size()-1; i++)
		{
			for(int j = i+1; j < contours.size(); j++)
			{
				if(mc.at(i).y - mc.at(j).y > re.height)
					break;
				if(mc.at(i).x - mc.at(j).x > re.width)
				{
					Point2f temp = mc.at(i);
					mc.at(i) = mc.at(j);
					mc.at(j) = temp;
				}
			}
		}


		if(mc.size() != levelCnt)
			return -1;

		SetMassCentroid(mc, re);
	}

#ifdef SHOWIMAGE
	//�������������Ĳ���ʾ 	
	Mat drawing = Mat::zeros( imgThresholdedRed.size(), CV_8UC3 ); 		
	for( int i = 0, j = 0; i< contours.size(); i++ , j++) 	
	{ 		
		Scalar color = Scalar( 255, 0, 0);
		drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
		circle( drawing, mc[i], 5, Scalar( 0, 0, 255), -1, 8, 0 );
		rectangle(drawing, boundingRect(contours.at(i)), cvScalar(0,255,0));
		char tam[100]; 
		sprintf(tam, "(%0.0f,%0.0f)",mc[i].x,mc[i].y); 
		putText(drawing, tam, Point(mc[i].x, mc[i].y), FONT_HERSHEY_SIMPLEX, 0.4, cvScalar(255,0,255),1); 	

		//cout << tam << endl;
	}

	namedWindow( pstrContoursWinTitle, CV_WINDOW_AUTOSIZE );
	imshow( pstrContoursWinTitle, drawing );
#endif
	/*************************����ʶ�����**************************/

	//�ȴ������¼�
	waitKey(1);

	return ret;
}

//�����ɫ��
int ColorPosDis::ProcessRed(const String& fileName)
{
	//���ļ�������ͼ��
	Mat srcImage = imread(fileName, IMREAD_COLOR);

	//�˲�
	GaussianBlur(srcImage, srcImage, cv::Size(0, 0), gaussianBlurSigmaX);

#ifdef SHOWIMAGE
	const char *pstrSrcWinTitle = "ԭͼ";
	const char *pstrHSVWinTitle = "HSVͼ";
	const char *pstrDestWinTitle = "Ŀ��ʶ��ͼ";
	const char *pstrContoursWinTitle = "����ͼ";

	//��������
	namedWindow(pstrSrcWinTitle, CV_WINDOW_AUTOSIZE);
	imshow(pstrSrcWinTitle, srcImage);
#endif

	/**************************��ɫʶ��************************/
	Mat imgHSV;
	vector<Mat> hsvSplit;
	cvtColor(srcImage, imgHSV,  COLOR_BGR2HSV);//Convert the captured frame from BGR to HSV

	//��Ϊ���Ƕ�ȡ���ǲ�ɫͼ��ֱ��ͼ���⻯��Ҫ��HSV�ռ���
	split(imgHSV, hsvSplit);
	equalizeHist(hsvSplit[2],hsvSplit[2]);
	merge(hsvSplit,imgHSV);

	//��ָ����������ʾͼ��
	//imshow(pstrHSVWinTitle, imgHSV);//show the original image

	Mat imgThresholdedRed, imgThresholdedGreen;

	inRange(imgHSV, Scalar(redHSVThreshod.lowH, redHSVThreshod.lowS, redHSVThreshod.lowV), 
		Scalar(redHSVThreshod.highH, redHSVThreshod.highS, redHSVThreshod.highV), imgThresholdedRed); //Threshold the image

	//������ (ȥ��һЩ���)
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(imgThresholdedRed, imgThresholdedRed, MORPH_OPEN, element);

	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholdedRed, imgThresholdedRed, MORPH_CLOSE, element);

#ifdef SHOWIMAGE
	imshow(pstrDestWinTitle, imgThresholdedRed);//show the thresholded image
#endif
	/**************************��ɫʶ�����************************/

	/*************************����ʶ��**************************/
	vector<vector<Point> > contours; 	
	vector<Vec4i> hierarchy;
	Rect re;
	//��������
	findContours( imgThresholdedRed, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	qDebug() << "contours.size() = " << contours.size() << endl;

	if(contours.size() <= 0 || contours.size() != levelCnt)
		return -1;

	//һ����ɫ��ĸ߶Ⱥͳ���
	re = boundingRect(contours.at(0));

	//���������� 	
	vector<Moments> mu(contours.size() ); 	
	for( int i = 0; i < contours.size(); i++ ) 	
	{ 
		mu[i] = moments( contours[i], false ); 
	} 	
	//�������������� 	
	vector<Point2f> mc( contours.size() ); 	
	for( int i = 0; i < contours.size(); i++) 	
	{ 
		mc[i] = Point2d( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
	}
	
	//��������
	for(int i = 0; i < contours.size()-1; i++)
	{
		for(int j = i+1; j < contours.size(); j++)
		{
			if(mc.at(i).y - mc.at(j).y > re.height)
			{
				Point2f temp = mc.at(i);
				mc.at(i) = mc.at(j);
				mc.at(j) = temp;
			}
		}
	}
	for(int i = 0; i < contours.size()-1; i++)
	{
		for(int j = i+1; j < contours.size(); j++)
		{
			if(mc.at(i).y - mc.at(j).y > re.height)
				break;
			if(mc.at(i).x - mc.at(j).x > re.width)
			{
				Point2f temp = mc.at(i);
				mc.at(i) = mc.at(j);
				mc.at(j) = temp;
			}
		}
	}

	SetMassCentroid(mc, re);

#ifdef SHOWIMAGE
	//�������������Ĳ���ʾ 	
	Mat drawing = Mat::zeros( imgThresholdedRed.size(), CV_8UC3 ); 		
	for( int i = 0, j = 0; i< contours.size(); i++ , j++) 	
	{ 		
		Scalar color = Scalar( 255, 0, 0);
		drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
		circle( drawing, mc[i], 5, Scalar( 0, 0, 255), -1, 8, 0 );
		rectangle(drawing, boundingRect(contours.at(i)), cvScalar(0,255,0));
		char tam[100]; 
		sprintf(tam, "(%0.0f,%0.0f)",mc[i].x,mc[i].y); 
		putText(drawing, tam, Point(mc[i].x, mc[i].y), FONT_HERSHEY_SIMPLEX, 0.4, cvScalar(255,0,255),1); 	

		//cout << tam << endl;
	}

	namedWindow( pstrContoursWinTitle, CV_WINDOW_AUTOSIZE );
	imshow( pstrContoursWinTitle, drawing );
#endif
	/*************************����ʶ�����**************************/

	//�ȴ������¼�
	waitKey(1);

	return 0;
}


//������ɫ��
int ColorPosDis::ProcessGreen(const String& fileName)
{
	//���ļ�������ͼ��
	Mat srcImage = imread(fileName, IMREAD_COLOR);

	//�˲�
	GaussianBlur(srcImage, srcImage, cv::Size(0, 0), gaussianBlurSigmaX);

#ifdef SHOWIMAGE
	const char *pstrSrcWinTitle = "ԭͼ";
	const char *pstrHSVWinTitle = "HSVͼ";
	const char *pstrDestWinTitle2 = "Ŀ��ʶ��ͼ2";
	const char *pstrContoursWinTitle = "����ͼ";

	//��������
	namedWindow(pstrSrcWinTitle, CV_WINDOW_AUTOSIZE);
	imshow(pstrSrcWinTitle, srcImage);
#endif

	/**************************��ɫʶ��************************/
	Mat imgHSV;
	vector<Mat> hsvSplit;
	cvtColor(srcImage, imgHSV,  COLOR_BGR2HSV);//Convert the captured frame from BGR to HSV

	//��Ϊ���Ƕ�ȡ���ǲ�ɫͼ��ֱ��ͼ���⻯��Ҫ��HSV�ռ���
	split(imgHSV, hsvSplit);
	equalizeHist(hsvSplit[2],hsvSplit[2]);
	merge(hsvSplit,imgHSV);

	//��ָ����������ʾͼ��
	//imshow(pstrHSVWinTitle, imgHSV);//show the original image

	Mat imgThresholdedGreen;

	inRange(imgHSV, Scalar(greenHSVThreshod.lowH, greenHSVThreshod.lowS, greenHSVThreshod.lowV), 
		Scalar(greenHSVThreshod.highH, greenHSVThreshod.highS, greenHSVThreshod.highV), imgThresholdedGreen); //Threshold the image

	//������ (ȥ��һЩ���)
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(imgThresholdedGreen, imgThresholdedGreen, MORPH_CLOSE, element);

	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholdedGreen, imgThresholdedGreen, MORPH_CLOSE, element);

#ifdef SHOWIMAGE
	imshow(pstrDestWinTitle2, imgThresholdedGreen);//show the thresholded image
#endif
	/**************************��ɫʶ�����************************/

	/*************************����ʶ��**************************/
	int ret = 0;
	vector<vector<Point> > contours; 	
	vector<Vec4i> hierarchy;
	Rect re;
	//��������
	findContours( imgThresholdedGreen, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	qDebug() << "contours.size() = " << contours.size() << endl;

	if(contours.size() <= 0)
		return 0;
	else if(contours.size() > 1)
		return -1;

	//���������� 	
	vector<Moments> mu(contours.size() ); 	
	for( int i = 0; i < contours.size(); i++ ) 	
	{ 
		mu[i] = moments( contours[i], false ); 
	} 	
	//�������������� 	
	vector<Point2f> mc( contours.size() ); 	
	for( int i = 0; i < contours.size(); i++) 	
	{ 
		mc[i] = Point2d( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
	}
	
	for(int j = 0; j < levelCnt; j++)
	{
		if(abs(massCentroid.at(j).x - mc[0].x) < massCentroidRange.width
			&& abs(massCentroid.at(j).y - mc[0].y) < massCentroidRange.height)
		{
			ret = j+1;
			break;
		}
	}

#ifdef SHOWIMAGE
	//�������������Ĳ���ʾ 	
	Mat drawing = Mat::zeros( imgThresholdedRed.size(), CV_8UC3 ); 		
	for( int i = 0, j = 0; i< contours.size(); i++ , j++) 	
	{ 		
		Scalar color = Scalar( 255, 0, 0);
		drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
		circle( drawing, mc[i], 5, Scalar( 0, 0, 255), -1, 8, 0 );
		rectangle(drawing, boundingRect(contours.at(i)), cvScalar(0,255,0));
		char tam[100]; 
		sprintf(tam, "(%0.0f,%0.0f)",mc[i].x,mc[i].y); 
		putText(drawing, tam, Point(mc[i].x, mc[i].y), FONT_HERSHEY_SIMPLEX, 0.4, cvScalar(255,0,255),1); 	

		//cout << tam << endl;
	}

	namedWindow( pstrContoursWinTitle, CV_WINDOW_AUTOSIZE );
	imshow( pstrContoursWinTitle, drawing );
#endif
	/*************************����ʶ�����**************************/

	//�ȴ������¼�
	waitKey(1);

	return ret;
}


void ColorPosDis::levelCntChanged(const QString &str)
{
	int val = str.toInt();
	SetLevelCnt(val);
}

#if 0

const char *pstrSrcImage = "2.jpg";
//const char *pstrSrcImage2 = "3.jpg";

int main(int argc, const char *argv[])
{
	ColorPosDis colPosDis;
	HSVThreshod_TypeDef hsvThreshod;

	//red
	hsvThreshod.highH = 9;
	hsvThreshod.highS = 255;
	hsvThreshod.highV = 255;
	hsvThreshod.lowH = 0;
	hsvThreshod.lowS = 120;
	hsvThreshod.lowV = 50;
	colPosDis.SetHSVThreshod(hsvThreshod, HSVTHRESHOLD_RED);

	//green
	hsvThreshod.highH = 92;
	hsvThreshod.highS = 255;
	hsvThreshod.highV = 255;
	hsvThreshod.lowH = 56;
	hsvThreshod.lowS = 120;
	hsvThreshod.lowV = 130;
	colPosDis.SetHSVThreshod(hsvThreshod, HSVTHRESHOLD_GREEN);

	//���ø�˹�˲�����
	colPosDis.SetFilterPara(5);

	//����Ҫʶ��ĵȼ�����
	colPosDis.SetLevelCnt(10);

	//������������
	if(colPosDis.Process(pstrSrcImage, 1) == -1)
	{
		cout << "If you make a mistake the level count?"<< endl << "If not,please justify the filter parameter!"<< endl;
	}

	while(1)
	{
		cout << "The passed index is " << colPosDis.Process(pstrSrcImage, 0) << endl;
	}

	return 0;
}

#endif