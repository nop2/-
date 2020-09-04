#pragma once


//typedef int bool;
//#define false 0
//#define true !false



////系统中所有进程数量
//#define PROCESSES_NUMBER 5
//
//typedef struct {
//	int	A;
//	int	B;
//	int	C;
//}RESOURCE;
//
////最大需求矩阵
//RESOURCE Max[PROCESSES_NUMBER] =
//{
//	{7,5,3},
//	{3,2,2},
//	{9,0,2},
//	{2,2,2},
//	{4,3,3}
//};
//
////已分配资源数矩阵
//RESOURCE Allocation[PROCESSES_NUMBER] =
//{
//	{0,1,0},
//	{2,0,0},
//	{3,0,2},
//	{2,1,1},
//	{0,0,2}
//};
//
////需求矩阵
//RESOURCE Need[PROCESSES_NUMBER] =
//{
//	{7,4,3},
//	{1,2,2},
//	{6,0,0},
//	{0,1,1},
//	{4,3,1}
//};
//
////可用资源向量
//RESOURCE Available = { 3,3,2 };
//
//int safe[PROCESSES_NUMBER];
//int path[PROCESSES_NUMBER];
//
//
////试探分配
//void ProbeAlloc(int process, RESOURCE* res)
//{
//	Available.A -= res->A;
//	Available.B -= res->B;
//	Available.C -= res->C;
//	Allocation[process].A += res->A;
//	Allocation[process].B += res->B;
//	Allocation[process].C += res->C;
//	Need[process].A -= res->A;
//	Need[process].B -= res->B;
//	Need[process].C -= res->C;
//}
////若试探分配后进入不安全状态，将分配回滚
//void RollBack(int process, RESOURCE* res)
//{
//	Available.A += res->A;
//	Available.B += res->B;
//	Available.C += res->C;
//	Allocation[process].A -= res->A;
//	Allocation[process].B -= res->B;
//	Allocation[process].C -= res->C;
//	Need[process].A += res->A;
//	Need[process].B += res->B;
//	Need[process].C += res->C;
//}
////安全性检查
//bool SafeCheck()
//{
//	bool Finish[PROCESSES_NUMBER] = { false };
//	RESOURCE Work = Available;
//	int finishCounter = 0;
//
//	for (int k = 0; k < PROCESSES_NUMBER; ++k) //每次选一个进程分配
//	{
//		int i;
//		//找到一个可分配资源的进程
//		for (i = 0; i < PROCESSES_NUMBER; ++i)
//		{
//			if (!Finish[i] && Need[i].A <= Work.A && Need[i].B <= Work.B && Need[i].C <= Work.C)
//			{
//				Finish[i] = true;
//				path[finishCounter++] = i;
//				if (finishCounter == PROCESSES_NUMBER)
//				{
//					return true;
//				}
//				Work.A += Allocation[i].A;
//				Work.B += Allocation[i].B;
//				Work.C += Allocation[i].C;
//				break;
//			}
//		}
//		if (i == PROCESSES_NUMBER) return false;
//	}
//
//
//	return false;
//}
//
//
////资源分配请求
//bool Request(int process, RESOURCE* res)
//{
//	if (Available.A < res->A || Available.B < res->B || Available.C < res->C)
//	{
//		printf("申请资源数不合法\n");
//		return false;
//	}
//	ProbeAlloc(process, res);
//	if (!SafeCheck())
//	{
//		RollBack(process, res);
//		printf("分配资源后系统处于不安全状态,拒绝分配\n");
//		return false;
//	}
//	printf("分配资源后系统处于安全状态,允许分配,一个安全序列为：");
//	for (int i = 0; i < PROCESSES_NUMBER; ++i)
//	{
//		printf("%d ", path[i]);
//	}
//	printf("\n");
//}
////输出资源分配表
//void PrintTable()
//{
//	printf("进程  最大需求   已分配   需要分配\n");
//	for (int i = 0; i < PROCESSES_NUMBER; ++i)
//	{
//		printf(" %d     %d,%d,%d     %d,%d,%d      %d,%d,%d\n", i, Max[i].A, Max[i].B, Max[i].C, Allocation[i].A, Allocation[i].B, Allocation[i].C, Need[i].A, Need[i].B, Need[i].C);;
//	}
//	printf("系统可用资源数：%d,%d,%d\n", Available.A, Available.B, Available.C);
//}


