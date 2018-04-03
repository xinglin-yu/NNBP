
/*
Referrence:
BP人工神经网络基本算法C语言实现【转】
http://blog.163.com/mthupc_0725/blog/static/28935506200942811235114/
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "NeuralNetBP.h"


//神经网络激活函数
double fnet(double net) { 

	double temp=0;

	//Sigmoid函数
	temp= 1.0 / (1 + exp(-net)); 

	return temp;

}

int InitBp(bp_nn *bp) { //初始化bp网络

	//请输入隐层节点数，最大数为50
	(*bp).h = NN_ImplyCout;
	//请输入学习率
	(*bp).a = NN_Rate;    //(*bp).a为double型数据，所以必须是lf
	//请输入精度控制参数
	(*bp).b = NN_Error;
	//请输入最大循环次数
	(*bp).LoopCout = NN_LOOP;

	//产生随机数初始化权值矩阵
	int i, j;
	srand((unsigned)time(NULL));
	for (i = 0; i < IN_COUT; i++)
		for (j = 0; j < (*bp).h; j++)
			(*bp).v[i][j] = rand() / (double)(RAND_MAX);
	for (i = 0; i < (*bp).h; i++)
		for (j = 0; j < OUT_COUT; j++)
			(*bp).w[i][j] = rand() / (double)(RAND_MAX);

	return 1;
}

int TrainBp(bp_nn *bp, int x[SampleTrain][IN_COUT], int y[SampleTrain][OUT_COUT]) 
{
	//训练bp网络，样本为x，理想输出为y
	double f = (*bp).b;                      //精度控制参数
	double a = (*bp).a;                      //学习率
	int h = (*bp).h;                         //隐层节点数
	double v[IN_COUT][50], w[50][OUT_COUT];  //权矩阵
	double ChgH[50], ChgO[OUT_COUT];         //修改量矩阵
	double O1[50], O2[OUT_COUT];             //隐层和输出层输出量
	int LoopCout = (*bp).LoopCout;           //最大循环次数
	int i, j, k, n;
	double temp;


	for (i = 0; i < IN_COUT; i++)            // 复制结构体中的权矩阵 
		for (j = 0; j < h; j++)
			v[i][j] = (*bp).v[i][j];
	for (i = 0; i < h; i++)
		for (j = 0; j < OUT_COUT; j++)
			w[i][j] = (*bp).w[i][j];

	double e = f + 1;
	for (n = 0; e > f && n < LoopCout; n++)
	{ //对每个样本训练网络
		e = 0;
		for (i = 0; i < SampleTrain; i++)
		{
			for (k = 0; k < h; k++) {          //计算隐层输出向量
				temp = 0;
				for (j = 0; j < IN_COUT; j++)
					temp = temp + x[i][j] * v[j][k];
				O1[k] = fnet(temp);
			}
			for (k = 0; k < OUT_COUT; k++) { //计算输出层输出向量
				temp = 0;
				for (j = 0; j < h; j++)
					temp = temp + O1[j] * w[j][k];
				O2[k] = fnet(temp);
			}
			for (j = 0; j < OUT_COUT; j++)    //计算输出层的权修改量    
				ChgO[j] = O2[j] * (1 - O2[j]) * (y[i][j] - O2[j]);
			for (j = 0; j < OUT_COUT; j++)   //计算输出误差
				e = e + (y[i][j] - O2[j]) * (y[i][j] - O2[j]);
			for (j = 0; j < h; j++) {         //计算隐层权修改量
				temp = 0;
				for (k = 0; k < OUT_COUT; k++)
					temp = temp + w[j][k] * ChgO[k];
				ChgH[j] = temp * O1[j] * (1 - O1[j]);
			}
			for (j = 0; j < h; j++)           //修改输出层权矩阵
				for (k = 0; k < OUT_COUT; k++)
					w[j][k] = w[j][k] + a * O1[j] * ChgO[k];
			for (j = 0; j < IN_COUT; j++)     //修改隐含层权矩阵
				for (k = 0; k < h; k++)
					v[j][k] = v[j][k] + a * x[i][j] * ChgH[k];
		}
		(*bp).Error[n] = e;		//记录误差

		if (n % 10 == 0)
		{
			printf("循环次数：%d, 误差 : %f\n",n,e);
		}
	}
	(*bp).LoopItera = n;		//实际循环次数

	printf("总共循环次数：%d\n", n);
	printf("调整后的隐层权矩阵：\n");
	for (i = 0; i < IN_COUT; i++) {
		for (j = 0; j < h; j++)
			printf("%f    ", v[i][j]);
		printf("\n");
	}
	printf("调整后的输出层权矩阵：\n");
	for (i = 0; i < h; i++) {
		for (j = 0; j < OUT_COUT; j++)
			printf("%f    ", w[i][j]);
		printf("\n");
	}
	for (i = 0; i < IN_COUT; i++)             //把结果复制回结构体 
		for (j = 0; j < h; j++)
			(*bp).v[i][j] = v[i][j];
	for (i = 0; i < h; i++)
		for (j = 0; j < OUT_COUT; j++)
			(*bp).w[i][j] = w[i][j];
	printf("bp网络训练结束！\n\n");

	return 1;
}


int UseBp(bp_nn *bp, int Input[IN_COUT], double Output[OUT_COUT]) {    //使用bp网络
	double O1[50];
	double O2[OUT_COUT]; //O1为隐层输出,O2为输出层输出
	int i, j;

	double temp;
	for (i = 0; i < (*bp).h; i++) {
		temp = 0;
		for (j = 0; j < IN_COUT; j++)
			temp += Input[j] * (*bp).v[j][i];
		O1[i] = fnet(temp);
	}
	for (i = 0; i < OUT_COUT; i++) {
		temp = 0;
		for (j = 0; j < (*bp).h; j++)
			temp += O1[j] * (*bp).w[j][i];
		O2[i] = fnet(temp);
	}
	//输出值
	for (i = 0; i < OUT_COUT; i++)
	{
		Output[i] = O2[i];
	}
	return 1;
}



double TestBp(bp_nn *bp, int x[SampleTest][IN_COUT], int y[SampleTest][OUT_COUT])
{    //使用bp网络

	int i, j;
	int Input[IN_COUT];
	double Output[OUT_COUT];	//此处的输出是实际计算输出 所以为double型
	int yMeasure[SampleTest];
	int CorrectN = 0;
	double Accuracy = 0;	//正确率

	for (i = 0; i < SampleTest; i++)
	{
		for (j = 0; j < IN_COUT; j++)
		{
			Input[j] = x[i][j];
		}

		////显示输入值
		//printf("输入值为: ");
		//for (int k = 0; k < IN_COUT; k++)
		//{
		//	printf("%d ", Input[k]);
		//}
		//printf("\n");

		UseBp(bp, Input, Output);      //测试bp神经网络子函数

		////显示输出值
		//printf("输出值为: ");
		//for (int k = 0; k < OUT_COUT; k++)
		//{
		//	printf("%.3f ", Output[k]);
		//}
		//printf("\n");

		////显示真值
		//printf("真值为: ");
		//for (int k = 0; k < OUT_COUT; k++)
		//{
		//	printf("%d ", y[i][OUT_COUT - 1]);
		//}
		//printf("\n\n");

		//结果分类
		if (Output[OUT_COUT - 1] >= 0.5)
		{
			yMeasure[i] = 1;
		}
		else
		{
			yMeasure[i] = 0;
		}


		if (y[i][OUT_COUT - 1] == yMeasure[i])	//真值=测量值
		{
			CorrectN++;
		}
	}

	Accuracy=CorrectN * 1.0 / SampleTest;	//计算正确率
	//显示测试结果
	printf("n=7 时，BPNN 测试结果为：\n");
	printf("  测试样本数：%d\n", SampleTest);
	printf("  正确样本数：%d\n", CorrectN);
	printf("  正确率为  ：%f\n", Accuracy);
	printf("\n\n");


	return Accuracy;

}


