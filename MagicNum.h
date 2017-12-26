#ifndef __MAGIC_NUM
#define __MAGIC_NUM
#include "PluginTCalcFunc.h"


void MagicNum_API_1(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc);
void MagicNum_API_2(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc);
void MagicNum_API_3(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc);
void MagicNum_API_4(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc);	
void MagicNum_API_5(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc);	
void MagicNum_API_6(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc);
void MagicNum_API_7(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc);
void MagicNum_API_8(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc);
void MagicNum_API_9(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc);


struct stZZconf
{
	float _ZZrate;
	float *_highZZ;
	float *_lowZZ;
	int *_ZZ;
};

struct stStock
{
	bool _bInit;
	int _stockcode;
	int _period;
	int _barcnt;

	float *_openarray;
	float *_higharray;
	float *_lowarray;
	float *_closearray;

	int *_Year;
	int *_Month;
	int *_Day;
	int *_Hour;
	int *_Minute;

	stZZconf _ZZinfo;
};


extern stStock _gStock;
#endif //__MAGIC_NUM