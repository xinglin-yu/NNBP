#pragma once
#ifndef _HANDLEFILE_H
#define _HANDLEFILE_H

#include "NeuralNetBP.h"


//误差值保存
int WriteToFile_Error(bp_nn *bp, char fileName[]);
//运算结果保存
int WriteToFile_Accuracy(char fileName[], double Accuracy[], int length);
//读取文件
int ReadFile(bp_nn *bp, char fileName[]);

#endif






