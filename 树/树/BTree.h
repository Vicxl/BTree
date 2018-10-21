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
//子问题，每次创建数；递归的思想
BTreeNode * CreateTree(char ** str){//传入指针，遍历过程中变量的地址
if (**str == 0){
	return NULL;
}

if (**str == '#'){
	(*str)++;
	return NULL;
}

    BTreeNode *pRoot = (BTreeNode *)malloc(sizeof(BTreeNode));
    pRoot->data = ** str;//构造结点
    (*str)++;
	pRoot->pLeft = CreateTree(str);
	pRoot->pRight = CreateTree(str);
	return pRoot;

}

//树的前序
void PreOrder(BTreeNode *pRoot)
{
	if (pRoot == NULL)
	{
		return;//空树
	}

	printf("%c", pRoot -> data);//处理根
	PreOrder(pRoot->pLeft);//处理左
	PreOrder(pRoot->pRight);//处理右
}

void InOrder(BTreeNode *pRoot){
	if (pRoot == NULL)
	{
		return;//空树
	}
	

	PreOrder(pRoot->pLeft);//处理左
	printf("%c", pRoot->data);//处理根
	PreOrder(pRoot->pRight);//处理右 
}
void PostOrder(BTreeNode *pRoot){
	if (pRoot == NULL)
	{
		return;//空树
	}

	PreOrder(pRoot->pLeft);//处理左
	PreOrder(pRoot->pRight);//处理右
	printf("%c", pRoot->data);//处理根
}
//遍历思想
//或者使用全局变量  int sum=0;
void NodeSize(BTreeNode *pRoot)
{
	int sum = 0;
	if (pRoot == NULL)
	{
		return ;
	}
	
	sum++;
	NodeSize(pRoot->pLeft);//处理左
	NodeSize(pRoot->pRight);//处理右

}
//叶子节点的个数
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
//空结点的叶子节点返回为0；左右结点为空的结点的叶子节点个数返回为1；

int LeafSizeSubproblem(BTreeNode *pRoot){
	if (pRoot == NULL){
		return 0;
	}
	if (pRoot->pLeft == NULL && pRoot->pRight == NULL){
		return 1;
	}

	return LeafSizeSubproblem(pRoot->pLeft) + LeafSizeSubproblem(pRoot->pRight);
}

//利用子问题求树中结点的个数  先求左，再求右
int NodeSizeSubproblem(BTreeNode *pRoot){
	if (pRoot == NULL){
		return 0;
	}
	return NodeSizeSubproblem(pRoot->pLeft) + NodeSizeSubproblem(pRoot->pRight) +1;
}

//求树的第k层结点的个数 k>=1
//递归出口：结束条件K层为空；计算左右结点根的个数
int GetLevelKSize(BTreeNode *pRoot, int k){
	//assert(k > 0);
	//空树
	if (pRoot == NULL){
		return 0;
	}
	//不是空树，根的个数
	if (k == 1){
		return 1;
	}

	//求第k层实则求k-1层
	return GetLevelKSize(pRoot->pLeft, k - 1) + GetLevelKSize(pRoot->pRight, k - 1);
}

//查找  ，后边先找左子树，一圈找不到，返回为空，返回再找右子树
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
	//提升效率
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
