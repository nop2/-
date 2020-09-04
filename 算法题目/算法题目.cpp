
/*
 * 编码：带有BOM的UTF-8
 * 
 */

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <iomanip>
using namespace std;


const int SIZE = 6; //棋盘大小 6*6
enum Direction { UP, DOWN, LEFT, RIGHT }; //行走方向枚举

struct Action //上一步动作记录
{
	int carId; //车号
	Direction direction; //方向
};

struct Car //车状态
{
	int id; //车号
	int row; //所在行  车的行列以左上角的坐标表示
	int col; //所在列
	int len; //长度   2/3
	bool isCross; //是否是横向的
};

struct Node
{
	int step; //步数
	int board[SIZE][SIZE]; //棋盘状态
	Car cars[18]; //汽车状态
	Action lastMove; //上次走法
	Node* parent; //解空间树父节点,用于生成路径
	Node* next; //链表下一节点，用于销毁链表
};

Node* start = nullptr; //起始棋盘状态
Node* last = nullptr; //链表最后一个节点
Node* ans = nullptr; //结果节点指针
Car redCar; //红车初始状态
int n; //小车数量

void Input(); //输入棋盘数据
void Destroy(); //销毁链表
void BFS(); //搜索解空间
bool CanEscape(const Node* node); //判断是否能够突出重围
string EnCode(const Node* node); //对棋盘编码
map<string, bool> boardMap; //棋盘编码为字符串，用于判断棋盘是否重复， 自定义键类型需要实现<
void Move(Node* p, int carId, Direction d, queue<Node*>& queue, int oldRow, int oldCol,
          int newRow, int newCol); //移动，就的位置是要填0的位置，新的位置是要移动到的位置
void PrintBoard(const Node* node); //输出状态

int main()
{
	Input();//输入数据

	clock_t begin = clock();
	BFS();//搜索解
	clock_t end = clock();

	cout << "\n搜索用时：" << (end - begin) / (double)CLOCKS_PER_SEC << "s" << endl;
	
	if (ans)
	{
		cout << "解步数：" << ans->step << endl << endl;
		stack<Node*> stack;
		while (ans->parent)
		{
			stack.push(ans);
			ans = ans->parent;
		}

		int count = 1;
		while (!stack.empty())
		{
			Node* a = stack.top();
			stack.pop();
			cout << "第" << count++ << "步: " << a->lastMove.carId << " ";
			switch (a->lastMove.direction)
			{
			case LEFT: cout << "←" << endl;
				break;
			case RIGHT: cout << "→" << endl;
				break;
			case UP: cout << "↑" << endl;
				break;
			case DOWN: cout << "↓" << endl;
				break;
			}
			PrintBoard(a);
			cout << endl;
		}
	}
	else
	{
		cout << "\n未搜索到解" << endl;
	}

	Destroy();//释放内存

	system("pause");
}

void BFS()
{
	queue<Node*> queue;

	queue.push(start);
	boardMap[EnCode(start)] = true;

	while (!queue.empty())
	{
		Node* p = queue.front();
		queue.pop();

		//判断是否突围
		if (CanEscape(p))
		{
			ans = p;
			break;
		}

		//n个车所有可能移动的状态加入队列
		for (int i = 1; i <= n; ++i)
		{
			Car car = p->cars[i];
			if (car.isCross)
			{
				//向左移动
				if (car.col - 1 >= 0 && p->board[car.row][car.col - 1] == 0)
				{
					Move(p, car.id, LEFT, queue, car.row, car.col + car.len - 1, car.row, car.col - 1);
				}
				//向右移动
				if (car.col + car.len < SIZE && p->board[car.row][car.col + car.len] == 0)
				{
					Move(p, car.id, RIGHT, queue, car.row, car.col, car.row, car.col + car.len);
				}
			}
			else
			{
				//向上移动
				if (car.row - 1 >= 0 && p->board[car.row - 1][car.col] == 0)
				{
					Move(p, car.id, UP, queue, car.row + car.len - 1, car.col, car.row - 1, car.col);
				}
				//向下移动
				if (car.row + car.len < SIZE && p->board[car.row + car.len][car.col] == 0)
				{
					Move(p, car.id, DOWN, queue, car.row, car.col, car.row + car.len, car.col);
				}
			}
		}
	}
}

void Move(Node* p, int carId, Direction d, queue<Node*>& queue, int oldRow, int oldCol, int newRow,
          int newCol)
{
	Node* node = new Node;
	copy(p, p + 1, node);
	node->board[newRow][newCol] = carId;
	node->board[oldRow][oldCol] = 0;

	string code = EnCode(node);
	if (boardMap[code] == true) //重复棋盘直接删掉,不加入队列
	{
		delete node;
	}
	else
	{
		boardMap[code] = true;
		node->next = nullptr;
		node->parent = p;
		node->step += 1;

		switch (d)
		{
		case LEFT: node->cars[carId].col -= 1;
			break;
		case RIGHT: node->cars[carId].col += 1;
			break;
		case UP: node->cars[carId].row -= 1;
			break;
		case DOWN: node->cars[carId].row += 1;
			break;
		}

		node->lastMove.carId = carId;
		node->lastMove.direction = d;

		last->next = node;
		last = node;
		queue.push(node);
	}
}

void PrintBoard(const Node* node)
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			cout << setw(2) << node->board[i][j] << " ";
		}
		cout << endl;
	}
}

void Input()
{
	start = new Node;
	start->step = 0;
	start->parent = nullptr;
	start->next = nullptr;
	start->lastMove = {-1, UP};
	last = start;

	cout << "请输入6x6的布局(空格分隔)：" << endl;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			cin >> start->board[i][j];
		}
	}
	cout << "请输入红车编号：";
	cin >> redCar.id;

	n = 0; //小车数量
	//分析各车的状态
	for (int i = 0; i < 18; ++i)
	{
		start->cars[i].id = 0;
	}
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			int carId = start->board[i][j];
			if (carId != 0 && start->cars[carId].id == 0)
			{
				if (carId > n) n = carId;
				start->cars[carId].id = carId;
				start->cars[carId].len = 0;
				start->cars[carId].row = i;
				start->cars[carId].col = j;

				if (j + 1 < SIZE && start->board[i][j + 1] == carId) //横向车
				{
					start->cars[carId].isCross = true;
					int k = j;
					while (k < SIZE && start->board[i][k] == carId)
					{
						++(start->cars[carId].len);
						//start->board[i][k] = 0;
						++k;
					}
				}
				else
				{
					//纵向
					start->cars[carId].isCross = false;
					int k = i;
					while (i < SIZE && start->board[k][j] == carId)
					{
						++(start->cars[carId].len);
						//start->board[k][j] = 0;
						++k;
					}
				}
			}
		}
	}

	redCar = start->cars[redCar.id];

	if (!redCar.isCross || redCar.row != 2)
	{
		cout << "\n无解" << endl;
		delete start;
		system("pause");
		exit(0);
	}
}

bool CanEscape(const Node* node)
{
	for (int i = node->cars[redCar.id].col + redCar.len; i < SIZE; ++i) //redCar的位置也会变动，不能用redCar的初始位置
	{
		if (node->board[2][i] != 0)
		{
			return false;
		}
	}
	return true;
}

string EnCode(const Node* node)
{
	string s(SIZE * SIZE, '0');
	int k = 0;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			s[k++] = node->board[i][j] + 'a';
		}
	}
	//cout << s.capacity() << endl;
	return s;
}

void Destroy()
{
	while (start)
	{
		Node* p = start;
		start = start->next;
		delete p;
	}
}

void Init()
{
	start = new Node;
	start->step = 0;
	start->parent = nullptr;
	start->next = nullptr;
	start->lastMove = { -1, UP };
	int a[6][6] = {
		{1, 1, 1, 0, 0, 2},
		{0, 0, 0, 0, 0, 2},
		{3, 3, 4, 0, 0, 2},
		{0, 0, 4, 5, 6, 6},
		{0, 0, 7, 5, 0, 0},
		{0, 0, 7, 8, 8, 8}
	};
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			start->board[i][j] = a[i][j];
		}
	}

	start->cars[1] = { 1, 0, 0, 3, true };
	start->cars[2] = { 2, 0, 5, 3, false };
	start->cars[3] = { 3, 2, 0, 2, true };
	start->cars[4] = { 4, 2, 2, 2, false };
	start->cars[5] = { 5, 3, 3, 2, false };
	start->cars[6] = { 6, 3, 4, 2, true };
	start->cars[7] = { 7, 4, 2, 2, false };
	start->cars[8] = { 8, 5, 3, 3, true };

	redCar = start->cars[3];
	n = 8;
	last = start;
}

/*
 * 1.棋盘分析   ....
 * 2.抽象数据结构
 * 3.核心算法实现 搜索、求解
 * 4.输入输出
 */

/*

测试数据

6.
0 0 1 0 0 0
0 0 1 0 0 0
2 2 1 0 0 0
0 0 0 0 0 3
0 0 0 0 0 3
4 4 4 0 0 3
红车 2

156.
0 2 3 3 5 5
0 2 0 4 6 6
1 1 0 4 11 0
7 8 8 8 11 12
7 0 9 0 11 12
7 0 9 10 10 12

1.
0 0 0 4 0 0
0 0 0 4 0 0
1 1 0 4 0 0
2 3 3 3 0 0
2 0 0 0 0 0
2 0 0 0 0 0

6.
0 0 2 0 0 0
0 0 2 0 0 0
1 1 2 0 0 0
0 0 0 0 0 4
0 0 0 0 0 4
3 3 3 0 0 4

12.
0 0 0 1 1 1
0 0 0 2 3 4
9 9 0 2 3 4
0 0 8 5 5 4
0 0 8 6 6 0
0 0 8 7 7 7

9.
1 1 1 0 0 2
0 0 0 0 0 2
3 3 4 0 0 2
0 0 4 6 7 7
0 0 5 6 0 0
0 0 5 8 8 8

23.
0 0 0 0 0 0
0 0 0 0 0 0
1 1 4 0 0 0
2 2 4 5 5 8
0 0 4 6 7 8
3 3 3 6 7 8

155.
0 2 3 3 4 4
0 2 6 5 5 7
1 1 6 0 0 7
8 9 9 10 0 7
8 0 0 10 11 11
8 12 12 12 0 0

157.
0 0 1 1 1 2
0 0 3 0 0 2
0 0 3 4 4 2
5 5 8 9 0 0
6 7 8 9 11 11
6 7 10 10 10 0

 
 */
