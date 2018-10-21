#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<windows.h>
//#include<math.h>
typedef char DataType;
typedef struct BTreeNode{
	DataType data;
	struct BTreeNode *pLeft;
	struct BTreeNode *pRight;
}BTreeNode;
//�����⣬ÿ�δ��������ݹ��˼��
BTreeNode * CreateTree(char ** str){//����ָ�룬���������б����ĵ�ַ
if (**str == 0){
	return NULL;
}

if (**str == '#'){
	(*str)++;
	return NULL;
}

    BTreeNode *pRoot = (BTreeNode *)malloc(sizeof(BTreeNode));
    pRoot->data = ** str;//������
    (*str)++;
	pRoot->pLeft = CreateTree(str);
	pRoot->pRight = CreateTree(str);
	return pRoot;

}

//����ǰ��
void PreOrder(BTreeNode *pRoot)
{
	if (pRoot == NULL)
	{
		return;//����
	}

	printf("%c", pRoot -> data);//�����
	PreOrder(pRoot->pLeft);//������
	PreOrder(pRoot->pRight);//������
}

void InOrder(BTreeNode *pRoot){
	if (pRoot == NULL)
	{
		return;//����
	}
	

	PreOrder(pRoot->pLeft);//������
	printf("%c", pRoot->data);//�����
	PreOrder(pRoot->pRight);//������ 
}
void PostOrder(BTreeNode *pRoot){
	if (pRoot == NULL)
	{
		return;//����
	}

	PreOrder(pRoot->pLeft);//������
	PreOrder(pRoot->pRight);//������
	printf("%c", pRoot->data);//�����
}
//����˼��
//����ʹ��ȫ�ֱ���  int sum=0;
void NodeSize(BTreeNode *pRoot)
{
	int sum = 0;
	if (pRoot == NULL)
	{
		return ;
	}
	
	sum++;
	NodeSize(pRoot->pLeft);//������
	NodeSize(pRoot->pRight);//������

}
//Ҷ�ӽڵ�ĸ���
int LeafSizeTravel(BTreeNode *pRoot, int n){
	if (pRoot == NULL){
		return n;
	}
	if (pRoot->pLeft == NULL && pRoot->pRight == NULL){
		return n + 1;
	}
	n = LeafSizeTravel(pRoot->pLeft, n);
	n = LeafSizeTravel(pRoot->pRight, n);
	return n;
}
//�ս���Ҷ�ӽڵ㷵��Ϊ0�����ҽ��Ϊ�յĽ���Ҷ�ӽڵ��������Ϊ1��

int LeafSizeSubproblem(BTreeNode *pRoot){
	if (pRoot == NULL){
		return 0;
	}
	if (pRoot->pLeft == NULL && pRoot->pRight == NULL){
		return 1;
	}

	return LeafSizeSubproblem(pRoot->pLeft) + LeafSizeSubproblem(pRoot->pRight);
}

//���������������н��ĸ���  ������������
int NodeSizeSubproblem(BTreeNode *pRoot){
	if (pRoot == NULL){
		return 0;
	}
	return NodeSizeSubproblem(pRoot->pLeft) + NodeSizeSubproblem(pRoot->pRight) +1;
}

//�����ĵ�k����ĸ��� k>=1
//�ݹ���ڣ���������K��Ϊ�գ��������ҽ����ĸ���
int GetLevelKSize(BTreeNode *pRoot, int k){
	//assert(k > 0);
	//����
	if (pRoot == NULL){
		return 0;
	}
	//���ǿ��������ĸ���
	if (k == 1){
		return 1;
	}

	//���k��ʵ����k-1��
	return GetLevelKSize(pRoot->pLeft, k - 1) + GetLevelKSize(pRoot->pRight, k - 1);
}

//����  �����������������һȦ�Ҳ���������Ϊ�գ���������������
BTreeNode *Find(BTreeNode *pRoot,DataType data){
	if (pRoot == NULL){
		return NULL;
	}
	if (pRoot->data == data){
		return pRoot;
	}
	BTreeNode *pFound = Find(pRoot -> pLeft,data);
	if (pFound != NULL){
		return pFound;
	}
	return Find(pRoot->pRight, data);
}
#define Max(m,n) ((m)>(n)?(m):(n))

int GetHeight(BTreeNode *pRoot){
	//assert(n > 1);
	if (pRoot == NULL){
		return 0;
	}
	int m = GetHeight(pRoot->pLeft);
	int n = GetHeight(pRoot->pRight);
	//����Ч��
	if (pRoot->pLeft == NULL && pRoot->pRight == NULL){
		//int m = 0;
		return 1;
	}
	
	return Max(m, n) + 1;
}

void Test()
{
	//char *s = "A";
	char *s = "AB#C##D#E";
	BTreeNode *pRoot = CreateTree(&s);
	/*PreOrder(pRoot);
	printf("\n");
	InOrder(pRoot);
	printf("\n");
	PostOrder(pRoot);
	printf("\n");
	printf("Tree\n");*/

	printf("%d\n",NodeSizeSubproblem(pRoot));
	printf("%d\n", LeafSizeTravel (pRoot, 0));
	printf("%d\n", LeafSizeSubproblem(pRoot));
	printf("%d\n", GetLevelKSize(pRoot, 0));
	printf("%d\n", Find(pRoot, 'A'));
	printf("%d\n", Find(pRoot, 'B'));
	printf("%d\n", GetHeight(pRoot));
}
