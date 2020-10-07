#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT
public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);
    void readLrc(QString lrcpath);
private slots:
    void TimeAdd();
    void StartTime();
private:
    QVector<lrc> veclrc;
    QWidget* centralWidget;
    QTextBrowser* textBrowser;
    QMenuBar* menuBar;
    QToolBar* mainToolBar;
    QStatusBar* statusBar;
    QTimer* timer;
    QPushButton* pushbutton;
    qreal windowtime = 0;
    unsigned lrcn;
    bool lrcend;
};
