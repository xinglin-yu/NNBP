#include <stdio.h>
#include "Sample.h"



//训练样本初始化 
int SampleTrain_Init(int Sx[SampleTrain][IN_COUT], int Sy[SampleTrain][OUT_COUT])
{
	int i,j;
	int sum = 0;

	for (i = 0; i < SampleTrain; i++)
	{
		sum = 0;
		for (j = 0; j < IN_COUT; j++)
		{
			Sx[i][IN_COUT-j-1]= (i >> j) & 1;	//依次取出各位
			sum += Sx[i][IN_COUT - j - 1];
		}
		Sy[i][0] = sum % 2;	//取余数
	}
	return 1;
}


//测试样本初始化 
int SampleTest_Init(int Sx[SampleTest][IN_COUT], int Sy[SampleTest][OUT_COUT])
{
	int i, j;
	int sum = 0;

	for (i = 0; i < SampleTest; i++)
	{
		sum = 0;
		for (j = 0; j < IN_COUT; j++)
		{
			Sx[i][IN_COUT - j - 1] = (i >> j) & 1;	//依次取出各位
			sum += Sx[i][IN_COUT - j - 1];
		}
		Sy[i][0] = sum % 2;	//取余数
	}
	return 1;
}




