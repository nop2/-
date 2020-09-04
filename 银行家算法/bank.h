#pragma once


//typedef int bool;
//#define false 0
//#define true !false



////ϵͳ�����н�������
//#define PROCESSES_NUMBER 5
//
//typedef struct {
//	int	A;
//	int	B;
//	int	C;
//}RESOURCE;
//
////����������
//RESOURCE Max[PROCESSES_NUMBER] =
//{
//	{7,5,3},
//	{3,2,2},
//	{9,0,2},
//	{2,2,2},
//	{4,3,3}
//};
//
////�ѷ�����Դ������
//RESOURCE Allocation[PROCESSES_NUMBER] =
//{
//	{0,1,0},
//	{2,0,0},
//	{3,0,2},
//	{2,1,1},
//	{0,0,2}
//};
//
////�������
//RESOURCE Need[PROCESSES_NUMBER] =
//{
//	{7,4,3},
//	{1,2,2},
//	{6,0,0},
//	{0,1,1},
//	{4,3,1}
//};
//
////������Դ����
//RESOURCE Available = { 3,3,2 };
//
//int safe[PROCESSES_NUMBER];
//int path[PROCESSES_NUMBER];
//
//
////��̽����
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
////����̽�������벻��ȫ״̬��������ع�
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
////��ȫ�Լ��
//bool SafeCheck()
//{
//	bool Finish[PROCESSES_NUMBER] = { false };
//	RESOURCE Work = Available;
//	int finishCounter = 0;
//
//	for (int k = 0; k < PROCESSES_NUMBER; ++k) //ÿ��ѡһ�����̷���
//	{
//		int i;
//		//�ҵ�һ���ɷ�����Դ�Ľ���
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
////��Դ��������
//bool Request(int process, RESOURCE* res)
//{
//	if (Available.A < res->A || Available.B < res->B || Available.C < res->C)
//	{
//		printf("������Դ�����Ϸ�\n");
//		return false;
//	}
//	ProbeAlloc(process, res);
//	if (!SafeCheck())
//	{
//		RollBack(process, res);
//		printf("������Դ��ϵͳ���ڲ���ȫ״̬,�ܾ�����\n");
//		return false;
//	}
//	printf("������Դ��ϵͳ���ڰ�ȫ״̬,�������,һ����ȫ����Ϊ��");
//	for (int i = 0; i < PROCESSES_NUMBER; ++i)
//	{
//		printf("%d ", path[i]);
//	}
//	printf("\n");
//}
////�����Դ�����
//void PrintTable()
//{
//	printf("����  �������   �ѷ���   ��Ҫ����\n");
//	for (int i = 0; i < PROCESSES_NUMBER; ++i)
//	{
//		printf(" %d     %d,%d,%d     %d,%d,%d      %d,%d,%d\n", i, Max[i].A, Max[i].B, Max[i].C, Allocation[i].A, Allocation[i].B, Allocation[i].C, Need[i].A, Need[i].B, Need[i].C);;
//	}
//	printf("ϵͳ������Դ����%d,%d,%d\n", Available.A, Available.B, Available.C);
//}


