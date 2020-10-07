#include "QtWidgetsApplication1.h"
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
        lrcn = 0;
        lrcend = false;
        resize(600, 400);
        centralWidget = new QWidget(this);
        QFile file("good.html");
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::information(NULL, QStringLiteral("��ʾ"),QStringLiteral("�򲻿���html�ļ�"));//��ʾ��ʾ��
        }
        QTextStream textStream(&file);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(0, 10, 431, 271));
        textBrowser->setReadOnly(false);
        textBrowser->setHtml(textStream.readAll());//Ŀǰ���Զ�ȡhtml�ļ��е��ı�����������
        readLrc("dshh.lrc");
        QString str(" < Hello Qt!>\n");//��ͨ�ķ�ʽ����Html
        QColor  clrR(255, 0, 0);//�ı�����ɫ
        QStringToHtmlFilter(str);
        QStringToHtml(str, clrR);
        QString imgPath = QString("dshh.jpg");
        //ͼƬ�ĵ�ַ
        imgPathToHtml(imgPath);//��imgת����html��ʾ
        textBrowser->insertHtml(imgPath);//����ͼƬ
        textBrowser->insertHtml(str);//����HTML�ı�
        setCentralWidget(centralWidget);
        pushbutton = new QPushButton(centralWidget);
        pushbutton->setGeometry(QRect(450, 300, 100, 40));
        timer = new QTimer();
        timer->setTimerType(Qt::CoarseTimer);
        QObject::connect(pushbutton,SIGNAL(clicked()),this,SLOT(StartTime()));
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(TimeAdd()));//�����Զ���
        menuBar = new QMenuBar(this);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        setMenuBar(menuBar);
        mainToolBar = new QToolBar(this);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(this);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        setStatusBar(statusBar);
}

void QtWidgetsApplication1::TimeAdd() {
    windowtime += 0.01;
    if (!lrcend && windowtime >= veclrc[lrcn].time) {
        qDebug() << veclrc[lrcn].lrcs;
        lrcn++;
        if (lrcn == veclrc.size()) {
            lrcend = true;
        }
    }
}

void QtWidgetsApplication1::StartTime() {
    timer->start(10);
    playMusic();
}

void QtWidgetsApplication1::readLrc(QString lrcpath)
{
    QFile file(lrcpath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(NULL, QStringLiteral("��ʾ"), QStringLiteral("�򲻿���lrc�ļ�"));//��ʾ��ʾ��
    }
    QRegExp timere("\\d{2}:\\d{2}\\.\\d{2}");
    QString str;
    while (!file.atEnd())
    {
        str = file.readLine();
        int pos = str.indexOf(timere);
        QTextStream in(&str);
        int min = 0;
        qreal sec = 0;
        char c;
        if (pos >= 0)
        { 
            in >> c >> min >> c >> sec>>c;
            lrc lr;
            lr.time = min * 60.0 + sec;
            lr.lrcs = in.readLine();
            veclrc.push_back(lr);
        }
    }
    qSort(veclrc.begin(), veclrc.end(), [](const lrc& infoA, const lrc& infoB) {
        return infoA.time < infoB.time; });
}
