#pragma once
#include<cstdlib>
#include<string>
#include<Windows.h>
using namespace std;
class CChineseCode
{
public:
	static void UTF_8ToUnicode(wchar_t* pOut, char* pText);  // 把UTF-8转换成Unicode
	static void UnicodeToUTF_8(char* pOut, wchar_t* pText);  //Unicode 转换成UTF-8
	static void UnicodeToGB2312(char* pOut, wchar_t uData);  // 把Unicode 转换成 GB2312 
	static void Gb2312ToUnicode(wchar_t* pOut, char* gbBuffer);// GB2312 转换成　Unicode
	static void GB2312ToUTF_8(string& pOut, char* pText, int pLen);//GB2312 转为 UTF-8
	static void UTF_8ToGB2312(string& pOut, char* pText, int pLen);//UTF-8 转为 GB2312
	static string UTF8_To_string(const string& str);//UTF-8转为string，解决TXT中文乱码问题
};



inline void CChineseCode::UTF_8ToUnicode(wchar_t* pOut, char* pText)
{
	char* uchar = (char*)pOut;

	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);

	return;
}

inline void CChineseCode::UnicodeToUTF_8(char* pOut, wchar_t* pText)
{
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	char* pchar = (char*)pText;

	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));

	return;
}

inline void CChineseCode::UnicodeToGB2312(char* pOut, wchar_t uData)
{
	WideCharToMultiByte(CP_ACP, NULL, &uData, 1, pOut, sizeof(wchar_t), NULL, NULL);
	return;
}

inline void CChineseCode::Gb2312ToUnicode(wchar_t* pOut, char* gbBuffer)
{
	::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, gbBuffer, 2, pOut, 1);
	return;
}

inline void CChineseCode::GB2312ToUTF_8(string& pOut, char* pText, int pLen)
{
	char buf[4];
	int nLength = pLen * 3;
	char* rst = new char[long long(nLength) + 1];

	memset(buf, 0, 4);
	memset(rst, 0, nLength);
	int i = 0;
	int j = 0;
	while (i < pLen)
	{
		//如果是英文直接复制就可以
		if (*(pText + i) >= 0)
		{
			rst[j++] = pText[i++];
		}
		else if (nLength >= 4)
		{
			wchar_t pbuffer;
			Gb2312ToUnicode(&pbuffer, pText + i);

			UnicodeToUTF_8(buf, &pbuffer);

			unsigned short int tmp = 0;
			tmp = rst[j] = buf[0];
			tmp = rst[j + 1] = buf[1];
			tmp = rst[j + 2] = buf[2];

			j += 3;
			i += 2;
		}
	}
	rst[j] = '\0';
	//返回结果
	pOut = rst;
	delete[] rst;
	return;
}

inline void CChineseCode::UTF_8ToGB2312(string& pOut, char* pText, int pLen)
{
	char* newBuf = new char[long long(pLen) + 1];
	char Ctemp[4];
	memset(Ctemp, 0, 4);
	int i = 0;
	int j = 0;
	while (i < pLen)
	{
		if (pText[i] > 0)
		{
			newBuf[j++] = pText[i++];
		}
		else if (pLen >= 2)
		{
			WCHAR Wtemp;
			UTF_8ToUnicode(&Wtemp, pText + i);

			UnicodeToGB2312(Ctemp, Wtemp);

			newBuf[j] = Ctemp[0];
			newBuf[j + 1] = Ctemp[1];

			i += 3;
			j += 2;
		}
	}
	newBuf[j] = '\0';
	pOut = newBuf;
	delete[] newBuf;
	return;
}

inline string CChineseCode::UTF8_To_string(const string& str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}