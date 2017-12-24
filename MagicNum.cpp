#include "stdafx.h"
#include "TCalcFuncSets.h"
#include "MagicNum.h"


stStock _gStock={0};

//通达信的数组  第DataLen-1个是最新的当前K
//the Zero index is the first one(the oldest) in history Kbar.


float _openarray[10000];
float  _higharray[10000];
float  _lowarray[10000];
float  _closearray[10000];
float  _HighZZarray[10000];
float  _LowZZarray[10000];
int _ZZ[10000];

int _Year[10000];
int _Month[10000];
int _Day[10000];
int _Hour[10000];
int _Minute[10000];



void debug()
{

 //MessageBox(NULL, "The message", "The caption", MB_OK);
}

//check if outbuf is empty or the different size.
bool util_checkbuf(stStock _Stock,int DataLen, float* inbuf,float* outbuf)
{
	return true;
#if 0
	if(outbuf == NULL)
	{
		outbuf = (float*)malloc(DataLen*sizeof(float));	
		if( outbuf==NULL )
		{
			debug();
			return false;
		}
	}else
	{
		if(_Stock._barcnt != DataLen)
		{
			// reallocate array to a new size
			float* tempbuf = outbuf;
			outbuf = (float*)realloc(outbuf,DataLen*sizeof(float));
			if(tempbuf)
			{
				free(tempbuf);
			}
			else
			{
				debug();
				// if realloc failed, the original pointer needs to be freed
				free(tempbuf);
				outbuf = NULL;
				return false;
			}
		}
	}

#endif

	//now outbuf is the correct size and not null
	//refresh to the acutal kbar len
	_Stock._barcnt = DataLen;
	return true;



}



bool util_checkbuf(stStock _Stock,int DataLen, float* inbuf,int* outbuf)
{

#if 0
	if(outbuf == NULL)
	{
		outbuf = (int*)malloc(DataLen*sizeof(int));	
		if( outbuf==NULL )
		{
			debug();
			return false;
		}
	}else
	{
		if(_Stock._barcnt != DataLen)
		{
			// reallocate array to a new size
			int* tempbuf = (int*)realloc(outbuf,DataLen*sizeof(int));
			if(tempbuf)
			{
				debug();
				free(outbuf);
				outbuf = tempbuf;
			}
			else
			{
				debug();
				// if realloc failed, the original pointer needs to be freed
				free(outbuf);
				outbuf = NULL;
				return false;
			}
		}
	}
#endif

	//now outbuf is the correct size and not null
	//refresh to the acutal kbar len
	_Stock._barcnt = DataLen;
	return true;


}

//Get stocknumber .e.g 300116 ,002014
//input :  stock code , kbar period 
void MagicNum_API_1(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	_gStock._stockcode = (int)pfINa[0];
	_gStock._period = (int)pfINb[0];

	if(_gStock._bInit != 1)
	{
		debug();

		_gStock._openarray = NULL;
		_gStock._higharray = NULL;
		_gStock._lowarray = NULL;
		_gStock._closearray = NULL;
		_gStock._Year = NULL;
		_gStock._Month = NULL;
		_gStock._Day = NULL;
		_gStock._Hour = NULL;
		_gStock._Minute = NULL;

		_gStock._bInit = 1;

		_gStock._openarray = &_openarray[0];
		_gStock._higharray = &_higharray[0];
		_gStock._lowarray = &_lowarray[0];
		_gStock._closearray = &_closearray[0];
		_gStock._ZZinfo._highZZ = &_HighZZarray[0];
		_gStock._ZZinfo._lowZZ = &_LowZZarray[0];
		_gStock._ZZinfo._ZZ = &_ZZ[0];

		_gStock._Year = &_Year[0];
		_gStock._Month = &_Month[0];
		_gStock._Day = &_Day[0];
		_gStock._Hour = &_Hour[0];
		_gStock._Minute = &_Minute[0];

	}

	//util_checkbuf(_gStock,DataLen,pfINa,_gStock._openarray); 
	//util_checkbuf(_gStock,DataLen,pfINb,_gStock._closearray);

}





//feed Open,Close
void MagicNum_API_2(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	if( util_checkbuf(_gStock,DataLen,pfINa,_gStock._openarray) 
		&& util_checkbuf(_gStock,DataLen,pfINb,_gStock._closearray) 
		)
	{
		for(int i=0;i<DataLen;i++)
		{
			_gStock._openarray[i] = pfINa[i];
			_gStock._closearray[i] = pfINb[i];

			pfOUT[i] = pfINc[i];
		}
	}else
	{
			debug();
	}
}

//feed high,low,volume
void MagicNum_API_3(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	if( util_checkbuf(_gStock,DataLen,pfINa,_gStock._lowarray) 
		&& util_checkbuf(_gStock,DataLen,pfINb,_gStock._higharray)
		)
	{
		for(int i=0;i<DataLen;i++)
		{
			_gStock._higharray[i] = pfINa[i];
			_gStock._lowarray[i] = pfINb[i];
		}
	}else
	{
			debug();
	}
}

//feed time : Year Month Day Hour Minute
void MagicNum_API_4(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	if( util_checkbuf(_gStock,DataLen,pfINa,_gStock._Year) 
		&& util_checkbuf(_gStock,DataLen,pfINb,_gStock._Month)
		&& util_checkbuf(_gStock,DataLen,pfINc,_gStock._Day)
		)
	{
		for(int i=0;i<DataLen;i++)
		{
			_gStock._Year[i] = (int)pfINa[i];
			_gStock._Month[i] = (int)pfINb[i];
			_gStock._Day[i] = (int)pfINc[i];
		}
	}else
	{
			debug();
	}
}

//输入zigzag数值 : H的ZZ  L的ZZ  ,Zrate

void MagicNum_API_5(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	//update the zzrate : 4% 10% etc
	_gStock._ZZinfo._ZZrate = pfINc[0];

	if( util_checkbuf(_gStock,DataLen,pfINa,_gStock._ZZinfo._highZZ)
		&& util_checkbuf(_gStock,DataLen,pfINa,_gStock._ZZinfo._lowZZ)
		)
	{
		for(int i=0;i<DataLen;i++)
		{
			_gStock._ZZinfo._highZZ[i] = pfINa[i];
			_gStock._ZZinfo._lowZZ[i] = pfINb[i];

		//	_HighZZarray[i] = pfINa[i];
		//	_LowZZarray[i] = pfINb[i];
		}	
	
		for( i=0;i<DataLen;i++)
		{
			pfOUT[i] = _gStock._ZZinfo._ZZrate ; //_gStock._ZZinfo._lowZZ[i];
		}

	}else
	{
			debug();
	}
}

//


int CheckFractal(float* inbuf,int pos)
{	
	if(pos<2) 
		return -1;

	if( inbuf[pos-1] < inbuf[pos-2] && inbuf[pos-1] < inbuf[pos])
	{
		//bottom
		return 1;
	}
	else if( inbuf[pos-1] > inbuf[pos-2] && inbuf[pos-1] > inbuf[pos])
	{
		//top
		return 2;
	}

	return 0;
}

void MagicNum_API_6(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	int lastfractaltype = 0;
	int diff = 0;

	for(int i=1;i<DataLen;i++)
	{
		if( CheckFractal(_gStock._ZZinfo._highZZ,i) == 2)
		{
			//HH的zz的top
			//pfOUT[i-1] = 2;
	
			if(lastfractaltype==0)
			{
				diff = 0;
				pfOUT[i-1] = 2;
								
				_gStock._ZZinfo._ZZ[i-1] = 2;
				lastfractaltype = 2;
			}
			else if(lastfractaltype==2)
			{
				lastfractaltype = 2;

				if(_gStock._ZZinfo._highZZ[i-diff] < _gStock._ZZinfo._highZZ[i] )
				{				
					//set back
					pfOUT[i-diff-1] = -1;
					pfOUT[i-1] = 2;
					
					_gStock._ZZinfo._ZZ[i-diff-1] = -1;
					_gStock._ZZinfo._ZZ[i-1] = 2;

					diff = 0;
				}else
				{
					pfOUT[i-1] = 0;	
					_gStock._ZZinfo._ZZ[i-1] = 0;
				}
				
			}
			else if(lastfractaltype==1)
			{
				if( _gStock._higharray[i-1] > _gStock._lowarray[i-diff]  )
				{
					pfOUT[i-1] = 2;

					_gStock._ZZinfo._ZZ[i-1] = 2;
					lastfractaltype = 2;
				}else
				{
					pfOUT[i-1] = 0;
					pfOUT[i-diff-1] = -1;

					_gStock._ZZinfo._ZZ[i-diff-1] = -1;
					_gStock._ZZinfo._ZZ[i-1] = 0;

					lastfractaltype = 1;
				}

				diff = 0;
			}
		}
		else if( CheckFractal(_gStock._ZZinfo._lowZZ,i) == 1)
		{
			//LL的ZZ的btm
			//pfOUT[i-1] = 1;
			if(lastfractaltype==0)
			{
				diff = 0;
				pfOUT[i-1] = 1;							
				_gStock._ZZinfo._ZZ[i-1] = 1;

				lastfractaltype = 1;
			}
			else if(lastfractaltype==1)
			{
				lastfractaltype = 1;


				if( _gStock._lowarray[i] < _gStock._lowarray[i-diff] )
				{
					pfOUT[i-diff-1] = -1;
					pfOUT[i-1] = 1;

					_gStock._ZZinfo._ZZ[i-diff-1] = -1;
					_gStock._ZZinfo._ZZ[i-1] = 1;

					diff = 0;
				}else
				{
					pfOUT[i-1] = 0;

					_gStock._ZZinfo._ZZ[i-1] = 0;
				}

			}
			else if(lastfractaltype==2)
			{
				

				if( _gStock._lowarray[i-1] < _gStock._higharray[i-diff])
				{				
					pfOUT[i-1] = 1;
					_gStock._ZZinfo._ZZ[i-1] = 1;

					lastfractaltype = 1;
				}else
				{
					pfOUT[i-diff-1] = -1;
					pfOUT[i-1] = 0;

					_gStock._ZZinfo._ZZ[i-diff-1] = -1;
					_gStock._ZZinfo._ZZ[i-1] = 0;

					lastfractaltype = 2;
				}

				diff = 0;
			}
		}
		else
		{
			pfOUT[i-1] = 0;
			_gStock._ZZinfo._ZZ[i-1] = 0;
		}

		diff++;
		//
		
	}

	//
	if(lastfractaltype==1)
	{
		pfOUT[i-1] = 1;

		_gStock._ZZinfo._ZZ[i-1] = 1;
	}
	else if(lastfractaltype==2)
	{
		pfOUT[i-1] = 2;
		_gStock._ZZinfo._ZZ[i-1] = 2;
	}

}


void MagicNum_API_7(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
#if 0
	for(int i=1;i<DataLen;i++)
	{
		if( CheckFractal(_gStock._ZZinfo._highZZ,i) == 2)
		{
			//HH的zz的top
			pfOUT[i-1] = 5;
			
		}
		else if( CheckFractal(_gStock._ZZinfo._lowZZ,i) == 1)
		{
			//LL的ZZ的btm
			pfOUT[i-1] = 4;
			
		}
		else
		{
			pfOUT[i-1] = 3;

		}
	}
#endif
	for(int i=0;i<DataLen;i++)
	{
		pfOUT[i] = _gStock._ZZinfo._ZZ[i];
	}

}

//search ZZ to see if there is price=time kbar
void MagicNum_API_8(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	int tunning = (int)pfINa[0];

	for(int i=0;i<DataLen;i++)
	{
		int turntype = _gStock._ZZinfo._ZZ[i];

		//it's turn point
		if( (turntype == 1) || (turntype == 2) )
		{
			int ktime1 = 0;
			int ktime2 = 0;
			float ktv1 = 0.0;
			float ktv2 = 0.0;

			//the highest/lowest 2 values
			if(turntype == 2)
			{
				ktv1 = _gStock._higharray[i];
				ktv2 = max(_gStock._openarray[i],_gStock._closearray[i]);
			}else if(turntype == 1)
			{
				ktv1 = _gStock._lowarray[i];
				ktv2 = min(_gStock._openarray[i],_gStock._closearray[i]);
			}

			ktime1 = ktv1*10+tunning;
			ktime2 = ktv2*10+tunning;

			//check if the ktime bar is turn point bar
			if( _gStock._ZZinfo._ZZ[i+ktime1] !=0 
				||
				_gStock._ZZinfo._ZZ[i+ktime2] !=0 
				||
				_gStock._ZZinfo._ZZ[i-ktime1] !=0 
				||
				_gStock._ZZinfo._ZZ[i-ktime2] !=0 
			  )
			{
				pfOUT[i] = 1;
			}
			else
			{
				pfOUT[i] = 0;
			}
		
		} // end zz
		else
		{
			pfOUT[i] = 0;
		}

	} // end for top loop
}