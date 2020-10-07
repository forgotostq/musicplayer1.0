#include "head.h"
/*
Ϊ�˿���˳���ز���html�ļ�����Ҫ���¼�������
*/
void QStringToHtmlFilter(QString& str)
{
    /*
    ����html�����ԣ��ᵼ��һЩ�����ַ�������ʾ���������ڱ�ǵġ�<����>�����ո񣬻��еȡ����Ե�һ����Ҫ�Դ���ӵ�QString����ת����ת����html֧�ֵ��ı���ʽ��ʹ�����º�����
    */
    //ע���⼸�д����˳�����ң��������ɶ���滻
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
    //����html������ԣ���QStringת����
    QByteArray array;
    array.append(crl.red());
    array.append(crl.green());
    array.append(crl.blue());
    QString strC(array.toHex());
    //���������TextBrowser��������²�ɫ���֡�
    str = QString("<span style=\" color:#%1;\">%2</span>").arg(strC).arg(str);
}

void imgPathToHtml(QString& path)
{
    //����ͼƬû�������ַ������⣬����ʵ�����������ס���ʹ�����º�����ͼƬ·��ת��Ϊhtml
    path = QString("<img src=\"%1\"/>").arg(path);
}

void playMusic()
{
    PlaySound(TEXT("dshh.wav"),NULL,SND_FILENAME|SND_ASYNC);
}

