#pragma once
#include<Windows.h>
#include<Mmsystem.h>
#include<qstring.h>
#include<iostream>
#include<qcolor.h>
#pragma comment(lib,"winmm.lib")
void QStringToHtmlFilter(QString& str);
void QStringToHtml(QString& str, QColor crl);
void imgPathToHtml(QString& path);
void playMusic();