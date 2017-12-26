#include "stdafx.h"
#include "TCalcFuncSets.h"
#include "MagicNum.h"

#include "ta-lib\include\ta_libc.h"


//生成的dll及相关依赖dll请拷贝到通达信安装目录的T0002/dlls/下面,再在公式管理器进行绑定

void TestPlugin1(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	for(int i=0;i<DataLen;i++)
		pfOUT[i]=i;
}

void TestPlugin2(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
//	char name[256] = "1234 Hello World";

#if 0
	for(int i=0;i<DataLen;i++)
	{
		pfOUT[i]=pfINa[i]+pfINb[i]+pfINc[i];
		pfOUT[i]=pfOUT[i]/3;
	}
#endif

	for(int i=0;i<DataLen;i++)
	{
		pfOUT[i]=pfINa[i];
	}	

}

void test_talib_ma(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	TA_Real    closePrice[10000];
	TA_Real    out[10000];
	TA_Integer outBeg;
	TA_Integer outNbElement;

	unsigned int i;

	/* ... initialize your closing price here... */
	for( i=0;i<DataLen;i++)
	{
		closePrice[i] = pfINa[i];
	}

	TA_Integer retCode = TA_MA( 0, DataLen,
		&closePrice[0],
		30,TA_MAType_SMA,
		&outBeg, &outNbElement, &out[0] );

	/* The output is displayed here */
	for( i=0; i < outNbElement; i++ )
	{
		pfOUT[i+outBeg] = out[i];
		//printf( "Day %d = %f\n", outBeg+i, out[i] );
	}
}




//加载的函数
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	{111,(pPluginFUNC)&TestPlugin1},
	{112,(pPluginFUNC)&TestPlugin2},
	{113,(pPluginFUNC)&test_talib_ma},
	
	/*magicnum*/
	 
	{1,(pPluginFUNC)&MagicNum_API_1},
	{2,(pPluginFUNC)&MagicNum_API_2},
	{3,(pPluginFUNC)&MagicNum_API_3},
	{4,(pPluginFUNC)&MagicNum_API_4},
	{5,(pPluginFUNC)&MagicNum_API_5},
	{6,(pPluginFUNC)&MagicNum_API_6},
	{7,(pPluginFUNC)&MagicNum_API_7},
	{8,(pPluginFUNC)&MagicNum_API_8},
	{9,(pPluginFUNC)&MagicNum_API_9},

	{0,NULL},
};

//导出给TCalc的注册函数
BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun)
{
	if(*pFun==NULL)
	{
		(*pFun)=g_CalcFuncSets;
		return TRUE;
	}
	return FALSE;
}
