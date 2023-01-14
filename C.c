#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//以下用 纯封装函数的思想/面向对象的思想 去做
//					1
// 封装数据：数据需要关键字
typedef struct data
{
	int first;		// 关键字
	char second[20];// 数据
}DATA,*LPDATA;

//					2
// 声明二叉搜索树的节点
typedef struct binaryTreeNode
{
	DATA element; // 元素/数据
	struct binaryTreeNode* LChild; // 左子树
	struct binaryTreeNode* RChild; // 右子树
}NODE, * LPNODE;

// 创建二叉搜索树的节点
LPNODE createNode1(DATA data) // 上面typedef了是*LPNODE，所以直接返回值是LPNODE
{
	LPNODE newNode = (LPNODE)malloc(sizeof(NODE));
	// 下面相当于初始化
	newNode->element = data;
	newNode->LChild = newNode->RChild = NULL;
	return newNode;
}
NODE* createNode2(DATA data)	// 上面typedef了是NODE，所以返回值是NODE*
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->element = data;
	newNode->LChild = newNode->RChild = NULL;
	return newNode;
}

//					3
// 声明二叉搜索树 
typedef struct binarySearchTree
{
	struct binaryTreeNode* root; // 节点的指针表示整棵树 - 根节点
	int treeSize;
}BTREE,*LPBTREE;

// 创建二叉搜索树
LPBTREE createbinarySearchTree1()
{
	// 创建 + 置空，相当于初始化
	LPBTREE tree = (LPBTREE)malloc(sizeof(BTREE));
	tree->root = NULL;	
	tree->treeSize = 0;
	return tree;
}
BTREE* createbinarySearchTree2()
{
	BTREE* tree = (BTREE*)malloc(sizeof(BTREE));// 此处用BTREE/LPBREE与上面道理相同
	tree->root = NULL;
	tree->treeSize = 0;
	return tree;
}

// 万金油函数
int size(LPBTREE tree)
{
	return tree->treeSize; // 返回树的大小
}
int empty(LPBTREE tree)
{
	if (tree->treeSize == 0) 
		return 1; // 说明树是空的
	else
		return 0; // 说明树不为空
}

// 插入节点
void insertNode(LPBTREE tree, DATA data)
{
	LPNODE moveNode = tree->root;
	LPNODE moveParentNode = NULL;
	while (moveNode!=NULL) // 找要插入的位置，当为NULL时表示找到
	{
		moveParentNode = moveNode;
		if (data.first < moveNode->element.first) // 新数据 < 树里的原数据
		{
			moveNode = moveNode->LChild;
		}
		else if (data.first > moveNode->element.first)// 新数据 > 树里的原数据
		{
			moveNode = moveNode->RChild;
		}
		else // 当要比较的数据和原数据相同，则将新数据覆盖进去
		{	// 由于我们写的是char类型的数据，所以要用字符串比较strcpy
			strcpy(moveNode->element.second, data.second);
			return;
		}
	}
	// 找到NULL后，开始插入，首先先创建节点
	NODE* newNode = createNode2(data);
	// 插入位置：移动节点的父节点（即NULL的上一个节点）
	if (tree->root == NULL)
	{ // 根节点为空，则新节点直接作为根节点
		tree->root = newNode;
	}
	else
	{
		if (moveParentNode->element.first > data.first)
		{	// 父节点的数据>新节点，将新节点插在父节点的左边
			moveParentNode->LChild = newNode;
		}
		else
		{	// 反之右边
			moveParentNode->RChild = newNode;
		}
	}
}

// 下面采用中序遍历的方法测试
// 1.打印树的节点
void printTree(LPNODE root)
{	
	if (root != NULL)
	{
		printTree(root->LChild);
		printf("%d\t%s\n", root->element.first, root->element.second);
		printTree(root->RChild);
	}
}	
// 2.打印树
void printSearchTree(LPBTREE tree)
{
	printTree(tree->root);
}
int main()
{
	DATA arr[7] = { 100,"张山",50,"里斯",180,"王五",40,"陈留",
					 55,"邦奇",190,"KAN",175,"chen" };
	BTREE* tree = createbinarySearchTree2();
	for(int i=0;i<7;i++)
	{
		insertNode(tree, arr[i]);
	}
	printSearchTree(tree);
	return 0;
}