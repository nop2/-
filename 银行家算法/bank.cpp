//#include "bank.h"
//
//
//bool SafeCheck()
//{
//	bool Finish[PROCESSES_NUMBER] = {false};
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
//				++finishCounter;
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
//bool Request(int process, RESOURCE* res)
//{
//	if (Available.A < res->A || Available.B < res->B || Available.C < res->C)
//	{
//		return false;
//	}
//	ProbeAlloc(process, res);
//	if(!SafeCheck())
//	{
//		RollBack(process, res);
//	}
//	
//}
//
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
//
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
