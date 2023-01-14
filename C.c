#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//������ ����װ������˼��/��������˼�� ȥ��
//					1
// ��װ���ݣ�������Ҫ�ؼ���
typedef struct data
{
	int first;		// �ؼ���
	char second[20];// ����
}DATA,*LPDATA;

//					2
// ���������������Ľڵ�
typedef struct binaryTreeNode
{
	DATA element; // Ԫ��/����
	struct binaryTreeNode* LChild; // ������
	struct binaryTreeNode* RChild; // ������
}NODE, * LPNODE;

// ���������������Ľڵ�
LPNODE createNode1(DATA data) // ����typedef����*LPNODE������ֱ�ӷ���ֵ��LPNODE
{
	LPNODE newNode = (LPNODE)malloc(sizeof(NODE));
	// �����൱�ڳ�ʼ��
	newNode->element = data;
	newNode->LChild = newNode->RChild = NULL;
	return newNode;
}
NODE* createNode2(DATA data)	// ����typedef����NODE�����Է���ֵ��NODE*
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->element = data;
	newNode->LChild = newNode->RChild = NULL;
	return newNode;
}

//					3
// �������������� 
typedef struct binarySearchTree
{
	struct binaryTreeNode* root; // �ڵ��ָ���ʾ������ - ���ڵ�
	int treeSize;
}BTREE,*LPBTREE;

// ��������������
LPBTREE createbinarySearchTree1()
{
	// ���� + �ÿգ��൱�ڳ�ʼ��
	LPBTREE tree = (LPBTREE)malloc(sizeof(BTREE));
	tree->root = NULL;	
	tree->treeSize = 0;
	return tree;
}
BTREE* createbinarySearchTree2()
{
	BTREE* tree = (BTREE*)malloc(sizeof(BTREE));// �˴���BTREE/LPBREE�����������ͬ
	tree->root = NULL;
	tree->treeSize = 0;
	return tree;
}

// ����ͺ���
int size(LPBTREE tree)
{
	return tree->treeSize; // �������Ĵ�С
}
int empty(LPBTREE tree)
{
	if (tree->treeSize == 0) 
		return 1; // ˵�����ǿյ�
	else
		return 0; // ˵������Ϊ��
}

// ����ڵ�
void insertNode(LPBTREE tree, DATA data)
{
	LPNODE moveNode = tree->root;
	LPNODE moveParentNode = NULL;
	while (moveNode!=NULL) // ��Ҫ�����λ�ã���ΪNULLʱ��ʾ�ҵ�
	{
		moveParentNode = moveNode;
		if (data.first < moveNode->element.first) // ������ < �����ԭ����
		{
			moveNode = moveNode->LChild;
		}
		else if (data.first > moveNode->element.first)// ������ > �����ԭ����
		{
			moveNode = moveNode->RChild;
		}
		else // ��Ҫ�Ƚϵ����ݺ�ԭ������ͬ���������ݸ��ǽ�ȥ
		{	// ��������д����char���͵����ݣ�����Ҫ���ַ����Ƚ�strcpy
			strcpy(moveNode->element.second, data.second);
			return;
		}
	}
	// �ҵ�NULL�󣬿�ʼ���룬�����ȴ����ڵ�
	NODE* newNode = createNode2(data);
	// ����λ�ã��ƶ��ڵ�ĸ��ڵ㣨��NULL����һ���ڵ㣩
	if (tree->root == NULL)
	{ // ���ڵ�Ϊ�գ����½ڵ�ֱ����Ϊ���ڵ�
		tree->root = newNode;
	}
	else
	{
		if (moveParentNode->element.first > data.first)
		{	// ���ڵ������>�½ڵ㣬���½ڵ���ڸ��ڵ�����
			moveParentNode->LChild = newNode;
		}
		else
		{	// ��֮�ұ�
			moveParentNode->RChild = newNode;
		}
	}
}

// ���������������ķ�������
// 1.��ӡ���Ľڵ�
void printTree(LPNODE root)
{	
	if (root != NULL)
	{
		printTree(root->LChild);
		printf("%d\t%s\n", root->element.first, root->element.second);
		printTree(root->RChild);
	}
}	
// 2.��ӡ��
void printSearchTree(LPBTREE tree)
{
	printTree(tree->root);
}
int main()
{
	DATA arr[7] = { 100,"��ɽ",50,"��˹",180,"����",40,"����",
					 55,"����",190,"KAN",175,"chen" };
	BTREE* tree = createbinarySearchTree2();
	for(int i=0;i<7;i++)
	{
		insertNode(tree, arr[i]);
	}
	printSearchTree(tree);
	return 0;
}