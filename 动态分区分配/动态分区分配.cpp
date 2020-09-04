#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define n 20 //模拟实验中，允许的最大作业数目 
#define m 20 //模拟实验中，允许的最大空闲分区数目 
#define minisize 100 //分配分区时，若寻找到的最小适合空间相对作业请求的空间来 ，说仍大于该数值，则要分割该分区

struct used_t
{
	int address; //已分配分区起始地址 
	int length; //已分配分区长度，单位为字节 
	int flag; //已分配分区表的标志项 
} used_table[n]; //已分配分区表 
struct free_t
{
	int address; //空闲分区起始地址 
	int length; //空闲分区长度，单位为字节 
	int flag; //空闲分区表的标志项 
} free_table[m]; //空闲分区表

int used_counter = 0;
int free_counter = 1;

//初始化空闲分区的长度
void Init(int length)
{
	free_table[0] = {0, length, 0};
}

int Alloc(int pid, int size)
{
	if (free_counter == 0) return 0;
	sort(free_table, free_table + free_counter, [](free_t& f1, free_t& f2) { return f1.length < f2.length; });
	for (int i = 0; i < free_counter; ++i)
	{
		//找到符合要求且最小的分区
		if (free_table[i].length >= size)
		{
			//空闲分区较大则分割，不大则全部分配
			if (free_table[i].length > minisize)
			{
				used_table[used_counter++] = {free_table[i].address, size, pid};
				free_table[i].address += size;
				free_table[i].length -= size;
				if (free_table[i].length == 0)
				{
					for (int j = i; j < free_counter - 1; ++j)
					{
						free_table[j] = free_table[j + 1];
					}
					--free_counter;
				}
			}
			else
			{
				used_table[used_counter++] = {free_table[i].address, free_table[i].length, pid};

				for (int j = i; j < free_counter - 1; ++j)
				{
					free_table[j] = free_table[j + 1];
				}
				--free_counter;
			}

			return true;
		}
	}
	return false;
}


int Recycle(int pid)
{
	int i = -1;
	for (i = 0; i < used_counter; ++i)
	{
		if (used_table[i].flag == pid)
		{
			int front = -1, back = -1;
			for (int j = 0; j < free_counter; ++j)
			{
				if (free_table[j].address + free_table[j].length == used_table[i].address)
				{
					front = j;
					break;
				}
			}
			for (int j = 0; j < free_counter; ++j)
			{
				if (free_table[j].address == used_table[i].address + used_table[i].length)
				{
					back = j;
					break;
				}
			}

			//回收分区后三种情况
			//前后都不临界，空闲分区+1
			if (front == -1 && back == -1)
			{
				free_table[free_counter++] = {used_table[i].address, used_table[i].length, 0};
			}
			else if (front >= 0 && back == -1)
			{
				free_table[front].length += used_table[i].length;
			}
			else if (front == -1 && back >= 0)
			{
				free_table[back].address = used_table[i].address;
				free_table[back].length += used_table[i].length;
			}
			else
			{
				//前后都邻接，空闲分区合并，数量-1
				free_table[front].length += free_table[back].length + used_table[i].length;
				for (int j = back; j < free_counter - 1; ++j)
				{
					free_table[j] = free_table[j + 1];
				}
				--free_counter;
			}

			for (int j = i; j < used_counter - 1; ++j)
			{
				used_table[j] = used_table[j + 1];
			}
			--used_counter;

			return true;
		}
	}
	return false;
}

void Print()
{
	printf("-----------空闲分区表-----------\n");
	printf("序号  首地址   长度   标识\n");

	for (int i = 0; i < free_counter; ++i)
	{
		printf("%d       %d      %d     %d\n", i, free_table[i].address, free_table[i].length, free_table[i].flag);
	}

	printf("-----------分配分区表-----------\n");
	printf("序号  首地址   长度   标识\n");

	for (int i = 0; i < used_counter; ++i)
	{
		printf("%d       %d      %d     %d\n", i, used_table[i].address, used_table[i].length, used_table[i].flag);
	}
}

int main()
{
	Init(1000);
	Print();

	while (true)
	{
		printf("\n");
		int pid, size, op;
		printf("输入进程号、空间大小、操作：");
		scanf_s("%d%d%d", &pid, &size, &op);

		if (op == 1)
		{
			if (Alloc(pid, size) == 1)
			{
				printf("分配成功\n");
				Print();
			}
			else
			{
				printf("分配失败\n");
			}
		}
		else
		{
			if (Recycle(pid))
			{
				printf("回收成功\n");
				Print();
			}
			else
			{
				printf("回收失败\n");
			}
		}
	}
}
