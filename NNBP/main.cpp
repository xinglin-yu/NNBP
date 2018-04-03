#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include "NeuralNetBP.h"
#include "HandleFile.h"
#include "Sample.h"


/*奇偶性判断
若 n 个输入中有奇数个 1，则输出为 1；若 n 个输入中有偶数个 1，则输出为 0。
*/
int main()
{

	int TrainX[SampleTrain][IN_COUT];
	int TrainY[SampleTrain][OUT_COUT];
	int TestX[SampleTest][IN_COUT];
	int TestY[SampleTest][OUT_COUT];
	bp_nn bp;

	const int TrainTimes = 1;	//训练次数
	double Accuracy[TrainTimes];//正确率

	SampleTrain_Init(TrainX, TrainY);
	SampleTest_Init(TestX, TestY);

	//单次训练
	//InitBp(&bp);                    //初始化bp网络结构
	//TrainBp(&bp, TrainX, TrainY);   //训练bp神经网络
	//TestBp(&bp, TestX, TestY);       //测试bp神经网络

	//多次训练取平均值
	for (int i = 0; i < TrainTimes;i++)
	{
		InitBp(&bp);                    //初始化bp网络结构
		TrainBp(&bp, TrainX, TrainY);   //训练bp神经网络
		Accuracy[i]=TestBp(&bp, TestX, TestY);       //测试bp神经网络
	}


	//保存数据
	WriteToFile_Error(&bp, "Data\\XOR7_Error.txt");	//保存最后一次的误差
	WriteToFile_Accuracy("Data\\XOR7_Result.txt", Accuracy, TrainTimes);//保存所有的运行结果

	system("pause");

	return 1;
}

