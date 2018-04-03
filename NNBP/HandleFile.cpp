
#include <stdio.h>
#include "HandleFile.h"


//误差值保存
int WriteToFile_Error(bp_nn *bp,char fileName[])
{
	FILE *fp;
	int i;
	//fp = fopen("dataParity7.txt", "w");//打开文件以便写入数据 
	fp = fopen(fileName, "w");//打开文件以便写入数据 
	for (i = 0; i < (*bp).LoopItera; i++)
	{
		//将误差写入fp指向的文件  
		fprintf(fp, "%f\n", (*bp).Error[i]);
	}
	fclose(fp);               //写入完毕，关闭文件 

	return 1;
}

//运算结果保存
int WriteToFile_Accuracy(char fileName[], double Accuracy[],int length)
{
	FILE *fp;
	int i;
	//fp = fopen("dataParity7.txt", "w");//打开文件以便写入数据 
	fp = fopen(fileName, "w");//打开文件以便写入数据 
	int temp=sizeof(Accuracy) / sizeof(Accuracy[0]);
	for (i = 0; i < length; i++)
	{
		//将结果写入fp指向的文件  
		fprintf(fp, "%f\n", Accuracy[i]);
	}
	fclose(fp);               //写入完毕，关闭文件 

	return 1;
}


//读取文件
int ReadFile(bp_nn *bp, char fileName[])
{
	FILE *fp;
	int i;

	int b[2] = { 0 };

	fp = fopen(fileName, "r");//打开文件以便从中读取数据 
	for (i = 0; i < 2; i++)
	{
		//从fp指向的文件中读取10个整数到b数组  
		fscanf(fp, "%d", &b[i]);
	}
	fclose(fp);        //读取完毕，关闭文件 

	for (i = 0; i < 2; i++)
	{
		//输出从fp文件读取的10个整数。  
		printf("%d\n", b[i]);
	}

	int c = b[0] &( 1<<5 );
	int d = (b[0] >> (4 - 1)) & 1;
	int e = (b[0] >> (4 - 1)) ;
	int f = (11111 >> (4 - 1));

	printf("%d\n", c);
	printf("%d\n", d);

	return 1;
}




