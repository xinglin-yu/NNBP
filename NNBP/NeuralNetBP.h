#pragma once
#ifndef _NEURALNETBP_H
#define _NEURALNETBP_H

////XOR2
//#define IN_COUT			2     //输入向量维数
//#define OUT_COUT		1     //输出向量维数
//#define IMPLY_NUM		1     //隐含层层数
//
//#define SampleTrain		4		//训练样本数量 用0-127共128组数据全部参加训练
//#define SampleTest		4		//测试样本数量 用0-127共128组数据全部参加测试
//
//#define NN_ImplyCout	4		//隐含层节点数
//#define NN_Rate			0.5		//学习速率
//#define NN_Error		0.001   //精度控制参数
//#define NN_LOOP			100000   //最大循环次数

/* 参数该变量
	输入维数改变时，改变IN_COUT的值即可
	同时需要修改SampleTrain、SampleTest、NN_ImplyCout的值；
	本程序取：
	SampleTrain = 2^IN_COUT
	SampleTest  = 2^IN_COUT
	NN_ImplyCout  = （2-4） * IN_COUT
*/

//XOR7
#define IN_COUT			7     //输入向量维数
#define OUT_COUT		1     //输出向量维数
#define IMPLY_NUM		1     //隐含层层数

#define SampleTrain		128		//训练样本数量 用0-127共128组数据全部参加训练
#define SampleTest		128		//测试样本数量 用0-127共128组数据全部参加测试

#define NN_ImplyCout	25		//隐含层节点数
#define NN_Rate			0.4		//学习速率
#define NN_Error		0.001   //精度控制参数
#define NN_LOOP			100000   //最大循环次数


typedef struct {       //bp人工神经网络结构
	int h;             //实际使用隐层节点数
	double v[IN_COUT][50];   //隐藏层权矩阵i,隐层节点最大数量为50
	double w[50][OUT_COUT];   //输出层权矩阵
	double a;          //学习率
	double b;          //精度控制参数
	int LoopCout;      //最大循环次数
	int LoopItera;     //实际循环次数
	double Error[NN_LOOP];	//误差
} bp_nn;


int InitBp(bp_nn *bp); //初始化bp网络
int TrainBp(bp_nn *bp, int x[SampleTrain][IN_COUT], int y[SampleTrain][OUT_COUT]); //训练bp网络，样本为x，理想输出为y
int UseBp(bp_nn *bp, int Input[IN_COUT], double Output[OUT_COUT]);		 //使用bp网络
double TestBp(bp_nn *bp, int x[SampleTest][IN_COUT], int y[SampleTest][OUT_COUT]);//测试bp网络

#endif
