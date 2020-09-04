#include<iostream>
#include<stack>
#include<queue>
#include<algorithm>
#include<cstdio>
#include<stdio.h> 
#include<cmath>
#include<string.h>
using namespace std;
#define N 6 
int flag = 1;
struct node
{
	node* father;//走前一步
	int state[N][N];
	node* next;//链表
};

node* current;
const node* head;
node* next_node;

void show_state(node* c)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			printf("%3d |", c->state[i][j]);
			//cout << c->state[i][j] << " | ";
		}
		cout << endl;
	}
}
void input_initial_state(int p[][6], node& root)
{
	// 36   2==> 18   3==> 12

	//红车  1 --18  红车      20--30  
	//四种情况  竖着2 横着2   竖着3 横着3
	//编码规则  红车一定是横着 2     横2  [1,20]   竖2 是 [21,40]  横3  [41,50]  竖3[51,60]
	int i;
	cout << "select num :";
	cin >> i;
	switch (i)
	{
	case 1:// [2,6] 输出  红车 为 1 1 

		p[0][0] = 0; p[0][1] = 0; p[0][2] = 0; p[0][3] = 51; p[0][4] = 0; p[0][5] = 0;
		p[1][0] = 0; p[1][1] = 0; p[1][2] = 0; p[1][3] = 51; p[1][4] = 0; p[1][5] = 0;
		p[2][0] = 1; p[2][1] = 1; p[2][2] = 0; p[2][3] = 51; p[2][4] = 0; p[2][5] = 0;
		p[3][0] = 52; p[3][1] = 41; p[3][2] = 41; p[3][3] = 41; p[3][4] = 0; p[3][5] = 0;
		p[4][0] = 52; p[4][1] = 0; p[4][2] = 0; p[4][3] = 0; p[4][4] = 0; p[4][5] = 0;
		p[5][0] = 52; p[5][1] = 0; p[5][2] = 0; p[5][3] = 0; p[5][4] = 0; p[5][5] = 0;
		break;
	case 2:
		p[0][0] = 0; p[0][1] = 0; p[0][2] = 0; p[0][3] = 0; p[0][4] = 0; p[0][5] = 0;
		p[1][0] = 0; p[1][1] = 0; p[1][2] = 0; p[1][3] = 0; p[1][4] = 0; p[1][5] = 0;
		p[2][0] = 0; p[2][1] = 0; p[2][2] = 0; p[2][3] = 0; p[2][4] = 0; p[2][5] = 0;
		p[3][0] = 0; p[3][1] = 0; p[3][2] = 0; p[3][3] = 0; p[3][4] = 0; p[3][5] = 0;
		p[4][0] = 0; p[4][1] = 0; p[4][2] = 0; p[4][3] = 0; p[4][4] = 0; p[4][5] = 0;
		p[5][0] = 0; p[5][1] = 0; p[5][2] = 0; p[5][3] = 0; p[5][4] = 0; p[5][5] = 0;
		break;
	case 3:

		break;
	case 4:

		break;

	}


	root.father = NULL;
	root.next = NULL;
}

bool check_repeat(node* p)//查看是否为新的状态 true重复
{
	node* traverse;
	traverse = (node*)head;
	/*for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					printf("%3d |*",head->state[i][j]);
					//cout << c->state[i][j] << " | ";
				}
				cout << endl;
			}*/
	int record = 0, sum = 0;//record记录不相同次数，sum对比总次数
	while (traverse)
	{

		/*for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					printf("%3d |",traverse->state[i][j]);
					//cout << c->state[i][j] << " | ";
				}
				cout << endl;
			}*/
		cout << endl;
		int remark = record;//跳出双循环
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (p->state[i][j] != traverse->state[i][j])//状态矩阵出现同位置不同元素，认为是2中不同状态
				{
					record = record + 1;
					break;
				}//检查到是一个新状态，记录一次重复
			}
			if (remark != record)break;
		}

		//循环对比后，发现是旧状态
		traverse = traverse->next;

		sum = sum + 1;
		if (traverse->next == NULL)
			break;
	}
	//遍历结束,对比sum和record，若sum==record 代表每次对比都出现不同状态，说明是一种新状态
	printf("%d  %d\n", sum, record);
	if (sum == record)return false;
	else return true;
}

bool is_success(node* p)
{
	for (int i = 0; i < 6; i++)
		if (p->state[2][i] > 1)
			return false;
	return true;
}
int update(int a[][6], node*& t, node*& next_node)
//待移动目标a1[i1][j1]，移动到位置a1[x1][y1],待移动目标a2[i2][j2]，移动到位置a2[x2][y2]
{
	//建立新状态结点
	node* p;
	next_node->next = new node;
	p = next_node->next;
	p->next = NULL;

	for (int b = 0; b < 6; b++)
	{
		for (int c = 0; c < 6; c++)
		{
			p->state[b][c] = a[b][c];
		}
	}//建立新状态结点

	if (check_repeat(p) == true)//状态重复
	{

		delete p;
		next_node->next = NULL;
		return 1;
	};//检查重复

	p->father = current;
	//next_node->next = &new_state;
	next_node = p;

	if (is_success(p))
	{
		//找到了目标状态，输出移动过程
		stack <node*> show_way;

		while (next_node->father != NULL)
		{
			show_way.push(next_node);
			next_node = next_node->father;
		}
		flag = 0;
		node* show; int x = 1;
		show = show_way.top();
		while (show_way.empty() == false)
		{
			cout << "di" << x << "setps:" << endl;
			show_state(show);
			show_way.pop();
			if (show_way.size() != 0)
				show = show_way.top();
			x = x + 1;
		}
	}
	return 0;
}
void row_2(int a[][6], int i, int j, node*& c, node*& n)//优化 ： 用一个数组标记 当前小车左右有几个空格
{

	if (j < 5 && a[i][j] == a[i][j + 1])//横2
	{
		if (j >= 1 && a[i][j - 1] == 0)//left 1
		{

			swap(a[i][j], a[i][j - 1]);
			swap(a[i][j + 1], a[i][j]);
			update(a, c, n);

		}
		if (j >= 2 && a[i][j - 1] == 0 && a[i][j - 2] == 0)//left,2
		{
			swap(a[i][j], a[i][j - 2]);
			swap(a[i][j + 1], a[i][j - 1]);
			update(a, c, n);
		}
		if (j >= 3 && a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0)//left,3
		{
			swap(a[i][j], a[i][j - 3]);
			swap(a[i][j + 1], a[i][j - 2]);
			update(a, c, n);
		}

		if (j >= 4 && a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0 && a[i][j - 4] == 0)//left,4
		{
			swap(a[i][j], a[i][j - 4]);
			swap(a[i][j + 1], a[i][j - 3]);
			update(a, c, n);
		}
		if (j <= 3 && a[i][j + 2] == 0)//right 1
		{

			swap(a[i][j + 1], a[i][j + 2]);
			swap(a[i][j], a[i][j + 1]);

			update(a, c, n);

		}
		if (j <= 2 && a[i][j + 2] == 0 && a[i][j + 3] == 0)//right,2
		{
			swap(a[i][j + 1], a[i][j + 3]);
			swap(a[i][j], a[i][j + 2]);
			update(a, c, n);
		}
		if (j <= 1 && a[i][j + 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0)//right,3
		{
			swap(a[i][j + 1], a[i][j + 4]);
			swap(a[i][j], a[i][j + 3]);
			update(a, c, n);
		}

		if (j <= 0 && a[i][j + 2] == 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)//right,4
		{
			swap(a[i][j + 1], a[i][j + 5]);
			swap(a[i][j], a[i][j + 4]);
			update(a, c, n);
		}
	}
}
void col_2(int a[][6], int i, int j, node*& c, node*& n)
{
	if (i < 5 && a[i][j] == a[i + 1][j])//竖2
	{
		if (i >= 1 && a[i - 1][j] == 0)//up 1
		{
			swap(a[i][j], a[i - 1][j]);
			swap(a[i + 1][j], a[i][j]);
			update(a, c, n);
		}
		if (i >= 2 && a[i - 1][j] == 0 && a[i - 2][j] == 0)//up,2
		{
			swap(a[i][j], a[i - 2][j]);
			swap(a[i][j + 1], a[i - 1][j]);
			update(a, c, n);
		}
		if (i >= 3 && a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0)//up,3
		{
			swap(a[i][j], a[i - 3][j]);
			swap(a[i][j + 1], a[i - 2][j]);
			update(a, c, n);
		}

		if (i >= 4 && a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i - 4][j] == 0)//up,4
		{
			swap(a[i][j], a[i - 4][j]);
			swap(a[i][j + 1], a[i - 3][j]);
			update(a, c, n);
		}
		//down
		if (i <= 3 && a[i - 1][j] == 0)//1
		{
			swap(a[i + 1][j], a[i + 2][j]);
			swap(a[i][j], a[i + 1][j]);
			update(a, c, n);
		}
		if (i <= 2 && a[i - 1][j] == 0 && a[i - 2][j] == 0)//2
		{
			swap(a[i + 1][j], a[i + 3][j]);
			swap(a[i][j], a[i + 2][j]);
			update(a, c, n);
		}
		if (i <= 1 && a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0)//3
		{
			swap(a[i + 1][j], a[i + 4][j]);
			swap(a[i][j], a[i + 3][j]);
			update(a, c, n);
		}

		if (i <= 0 && a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0 && a[i - 4][j] == 0)//4
		{
			swap(a[i + 1][j], a[i + 5][j]);
			swap(a[i][j], a[i + 4][j]);
			update(a, c, n);
		}

	}
}
int row_3(int a[][6], int i, int j, node*& c, node*& n)
{
	if (j < 4 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2])//横3
	{
		if (j >= 1 && a[i][j - 1] == 0)//left 1
		{
			swap(a[i][j], a[i][j - 1]);
			swap(a[i][j + 1], a[i][j]);
			swap(a[i][j + 2], a[i][j + 1]);
			update(a, c, n);
		}
		if (j >= 2 && a[i][j - 1] == 0 && a[i][j - 2] == 0)//left,2
		{
			swap(a[i][j], a[i][j - 2]);
			swap(a[i][j + 1], a[i][j - 1]);
			swap(a[i][j + 2], a[i][j]);
			update(a, c, n);
		}
		if (j >= 3 && a[i][j - 1] == 0 && a[i][j - 2] == 0 && a[i][j - 3] == 0)//left,3
		{
			swap(a[i][j], a[i][j - 3]);
			swap(a[i][j + 1], a[i][j - 2]);
			swap(a[i][j + 2], a[i][j - 1]);
			update(a, c, n);
		}
		if (j <= 2 && a[i][j + 3] == 0)//right,2
		{
			swap(a[i][j + 2], a[i][j + 3]);
			swap(a[i][j + 1], a[i][j + 2]);
			swap(a[i][j], a[i][j + 1]);
			update(a, c, n);
		}
		if (j <= 1 && a[i][j + 3] == 0 && a[i][j + 4] == 0)//right,3
		{
			swap(a[i][j + 2], a[i][j + 4]);
			swap(a[i][j + 1], a[i][j + 3]);
			swap(a[i][j], a[i][j + 2]);
			update(a, c, n);
		}

		if (j <= 0 && a[i][j + 3] == 0 && a[i][j + 4] == 0 && a[i][j + 5] == 0)//right,4
		{
			swap(a[i][j + 2], a[i][j + 5]);
			swap(a[i][j + 1], a[i][j + 4]);
			swap(a[i][j], a[i][j + 3]);
			update(a, c, n);
		}
	}
	return 0;
}
int col_3(int a[][6], int i, int j, node*& c, node*& n)
{
	if (i < 4 && a[i][j] == a[i + 1][j])//竖2
	{
		if (i >= 1 && a[i - 1][j] == 0)//up 1
		{
			swap(a[i][j], a[i - 1][j]);
			swap(a[i + 1][j], a[i][j]);
			swap(a[i + 2][j], a[i + 1][j]);
			update(a, c, n);
		}
		if (i >= 2 && a[i - 1][j] == 0 && a[i - 2][j] == 0)//up,2
		{
			swap(a[i][j], a[i - 2][j]);
			swap(a[i][j + 1], a[i - 1][j]);
			swap(a[i][j + 2], a[i][j]);
			update(a, c, n);
		}
		if (i >= 3 && a[i - 1][j] == 0 && a[i - 2][j] == 0 && a[i - 3][j] == 0)//up,3
		{
			swap(a[i][j], a[i - 3][j]);
			swap(a[i][j + 1], a[i - 2][j]);
			swap(a[i][j + 2], a[i - 1][j]);
			update(a, c, n);
		}
		//down
		if (i <= 2 && a[i - 3][j] == 0)//2
		{
			swap(a[i + 2][j], a[i + 3][j]);
			swap(a[i + 1][j], a[i + 2][j]);
			swap(a[i][j], a[i + 1][j]);
			update(a, c, n);
		}
		if (i <= 1 && a[i - 3][j] == 0 && a[i - 4][j] == 0)//3
		{
			swap(a[i + 2][j], a[i + 4][j]);
			swap(a[i + 1][j], a[i + 3][j]);
			swap(a[i][j], a[i + 2][j]);
			update(a, c, n);
		}

		if (i <= 0 && a[i - 3][j] == 0 && a[i - 4][j] == 0 && a[i - 5][j] == 0)//4
		{
			swap(a[i + 2][j], a[i + 5][j]);
			swap(a[i + 1][j], a[i + 4][j]);
			swap(a[i][j], a[i + 3][j]);
			update(a, c, n);
		}
	}
	return 0;
}
int build_tree(node*& c, node*& n)
{
	//if (!c) return 0;
	int a[6][6];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			a[i][j] = c->state[i][j];
		}
	}
	//printf("%3d |",c->state[0][0]);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (a[i][j] >= 1 && a[i][j] <= 20)
				row_2(a, i, j, c, n);
			if (a[i][j] >= 21 && a[i][j] <= 40)
				col_2(a, i, j, c, n);
			if (a[i][j] >= 41 && a[i][j] <= 50)
				row_3(a, i, j, c, n);
			if (a[i][j] >= 51 && a[i][j] <= 60)
				col_3(a, i, j, c, n);
			//printf("%3d |",c->state[i][j]);
		}
		//cout<<endl;

	}
	//判断当前状态图可移动的情况，给每种情况生成子节点

	c = c->next;//当前结点移动到下一个节点
	return 0;
}



int main()
{
	cout << "**********" << endl;
	struct node root;
	input_initial_state(root.state, root);
	current = &root;//当前节点
	next_node = &root;
	head = &root;//头
	//show_state(current);
	//build_tree(current, next_node);

	while (flag)
	{
		build_tree(current, next_node);
	}
	system("pause");
	return 0;
}