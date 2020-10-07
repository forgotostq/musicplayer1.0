#include "head.h"
/*
为了可以顺利地插入html文件，需要如下几个函数
*/
void QStringToHtmlFilter(QString& str)
{
    /*
    由于html的特性，会导致一些特殊字符不能显示，例如用于标记的‘<’‘>’、空格，换行等。所以第一步需要对待添加的QString进行转化，转化成html支持的文本方式。使用如下函数：
    */
    //注意这几行代码的顺序不能乱，否则会造成多次替换
    str.replace("&", "&amp;");
    str.replace(">", "&gt;");
    str.replace("<", "&lt;");
    str.replace("\"", "&quot;");
    str.replace("\'", "&#39;");
    str.replace(" ", "&nbsp;");
    str.replace("\n", "<br>");
    str.replace("\r", "<br>");
}

void QStringToHtml(QString& str, QColor crl)
{
    //根据html标记语言，将QString转化。
    QByteArray array;
    array.append(crl.red());
    array.append(crl.green());
    array.append(crl.blue());
    QString strC(array.toHex());
    //例如在你的TextBrowser中添加如下彩色文字。
    str = QString("<span style=\" color:#%1;\">%2</span>").arg(strC).arg(str);
}

void imgPathToHtml(QString& path)
{
    //由于图片没有特殊字符的问题，所以实现起来很容易。先使用如下函数将图片路径转换为html
    path = QString("<img src=\"%1\"/>").arg(path);
}

void playMusic()
{
    PlaySound(TEXT("dshh.wav"),NULL,SND_FILENAME|SND_ASYNC);
}

