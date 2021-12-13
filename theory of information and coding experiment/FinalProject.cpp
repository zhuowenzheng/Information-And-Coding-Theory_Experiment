#include <iostream>
#include<iomanip>
#include<math.h>
#include<cstring>
#include<algorithm>//为编码中对信息进行排序的步骤引入算法模块

#define lb 1/log(2)
#define HmaxC 1
#define ASCIIconst1 48

static double recursCodeLength = 0;

using namespace std;

//获取信源长度
template<class T>
int getSourceLength(T& source)//Bug not solved
{
	int sourceLength = (sizeof(source) / sizeof(source[0]));//利用数组的储存机制获取数组长度
	return sourceLength;
}
//获取单个信息的自信息量
double getSelfInfoQuantity(double messageP)//mesageP为信源概率
{
	double selfInfoQuantity;
	selfInfoQuantity = -lb * log(messageP);
	return selfInfoQuantity;
}
//获取信源熵
double getSourceEntropy(double messageP[],int sourceLength)
{
	double sourceEntropy = 0;
	for (int i = 0; i < sourceLength; i++)
	{
		sourceEntropy -= messageP[i] * lb * log(messageP[i]);
		
	}
	
	return sourceEntropy;
}
//获取冗余度
double getRedundancy(double messageP[],int sourceLength, double sourceEntropy)
{
	double redundancy;
	double Hmax;
	Hmax = lb * log(sourceLength);
	redundancy = 1 - sourceEntropy / Hmax;
	return redundancy;
}

//费诺编码

int cal = 1;//Number

void FanoCoding(double messageP[], int sourceLength, int begin, int end, string Fano,int codeLength[])
{
	
	sort(messageP, messageP + sourceLength, greater<double>());
	//
	double getSum(double sortArray[], int start, int last);//declaration;
	if (begin >= end)
	{
		cout << cal << " " << Fano << endl;
		cal++;
		codeLength[cal-2] = Fano.length();
		//cout << "code length:" << codeLength[cal]<<endl;
		return;
	}
	double sum = getSum(messageP, begin, end);
	int index = -1; // 初值设定 
	double minNum = sum; // 设定最小值 
	double tempSum = 0; // 前几个的和 
	for (int i = begin; i <= end; i++) {
		tempSum += messageP[i];
		if (abs(sum - 2 * tempSum) < minNum) {
			index = i; // 记录当前最小的值
			minNum = abs(sum - 2 * tempSum); // 更新最小值 
		}
	}
	// 递归左边部分 
	FanoCoding(messageP,sourceLength, begin, index, Fano + '0',codeLength); // 左边添加0
	// 递归右边部分 
	FanoCoding(messageP,sourceLength, index + 1, end, Fano + '1',codeLength); //右边添加1
	
	double avrCodeLength = 0;
	for (int j = 0; j < sourceLength; j++)
	{
		avrCodeLength += messageP[j] * codeLength[j];
	}

	recursCodeLength = avrCodeLength;
	//分析编码效率及码冗余度;
}
void FanoAnalyzing(double messageP[],int sourceLength,double avrCodeLength)
{
	double avrCodeEntropy = 0;
	double codingEfficiency = 0;
	double codeRedundancy = 0;

	
	//cout << avrCodeLength << endl;
	avrCodeEntropy = getSourceEntropy(messageP, sourceLength) / avrCodeLength;
	//cout << avrCodeEntropy << endl;
	codingEfficiency = avrCodeEntropy / HmaxC;

	codeRedundancy = 1 - codingEfficiency;
	cout << "编码效率 Coding Efficiency=" << codingEfficiency * 100 << "%" << endl;
	cout << "码冗余度 Code Redundancy=" << codeRedundancy * 100 << "%" << endl;

}

double getSum(double p[], int begin, int end) {
	double sum = 0;
	for (int i = begin; i <= end; i++) {
		sum += p[i];
	}
	return sum;
}

//typedef struct HuffmanNode {//利用Huffman二叉树进行Huffman编码
//	
//	double weight;
//	int sequence=0;
//	string HuffCode;
//	HuffmanNode* parent;
//	HuffmanNode* leftChild;
//	HuffmanNode* rightChild;
//}HuffManNode,*HuffmanTree;
//
//typedef char** HuffmanCode;

//void createHuffmanTree(HuffmanTree &HuffTree,int sourceLength, double messageP[])
//{
//	int createCounter = 0;
//	HuffmanNode* toStart;//def required
//	double findMin(double messageP[],int createCounter);
//	while (createCounter < sourceLength)
//	{
//
//		HuffmanNode* nodeLeft = new HuffmanNode;
//		HuffmanNode* nodeRight = new HuffmanNode;
//		HuffmanNode* nodeParent = new HuffmanNode;
//		HuffmanNode* pointer;
//		if(nodeLeft->parent==NULL)
//		{
//			nodeLeft = toStart;//initialize
//			nodeLeft->sequence = sourceLength - createCounter;
//		}
//		else
//		{
//			if (findMin(messageP, createCounter) <= pointer->weight)
//			{
//				pointer->HuffCode = "0";
//				nodeLeft = pointer;//continue
//				nodeLeft->HuffCode = "1";
//			}
//			else {
//				pointer->HuffCode = "1";
//				nodeRight = pointer;
//				nodeRight->HuffCode = "0";
//			}
//		}
//		//create HuffMan BinaryTree
//		if (nodeLeft == NULL)
//		{
//			nodeLeft->weight = findMin(messageP, createCounter);
//			nodeLeft->HuffCode = "1";
//			nodeLeft->sequence = sourceLength - createCounter;
//			createCounter++;
//		}
//		if (nodeRight == NULL);
//		{
//			nodeRight->weight = findMin(messageP, createCounter);
//		    nodeRight->HuffCode = "0";
//			nodeRight->sequence = sourceLength - createCounter;
//		    createCounter++; 
//		}
//		nodeLeft->parent = nodeParent;
//		nodeRight->parent = nodeParent;
//		nodeParent->leftChild = nodeLeft;
//		nodeParent->rightChild = nodeRight;
//		nodeParent->weight = nodeLeft->weight + nodeRight->weight;
//		messageP[sourceLength - createCounter] = nodeParent->weight;
//		pointer = nodeParent;
//	}
//	
//	//遍历
//
//}




double findMin(double messageP[],int sourceLength,int createCounter)
{
	//sort;
	sort(messageP, messageP + sourceLength-createCounter, greater<double>());
	return messageP[sourceLength - createCounter];
}
;


typedef struct
{
	double weight;
	int parent, childLeft, childRight;
}HTNode;

typedef HTNode* HuffmanTree;


//初始化哈夫曼树

void initHuffmanTree(HuffmanTree& HuffTree, int m)
{
	HuffTree = new HTNode[m];
	for (int i = 0; i < m; i++)
	{
		HuffTree[i].weight = 0;
		HuffTree[i].parent = -1;
		HuffTree[i].childLeft = -1;
		HuffTree[i].childRight = -1;
	}
}

//从n个结点中选取最小的两个结点

void SelectMin(HuffmanTree& HuffTree, int n, int& min1, int& min2)
{
	typedef struct
	{
		   double NewWeight;//存储权
		   int p;//存储该结点所在的位置
	}TempNode, * TempTree;

	TempTree TpTree = new TempNode[n];

	

	int j = 0;
	for (int i = 0; i < n; i++)
	{
		if (HuffTree[i].parent == -1 && HuffTree[i].weight != 0)
		{
			TpTree[j].NewWeight = HuffTree[i].weight;
			TpTree[j].p = i;
			j++;
		}
	}//将HuffTree中没有parent的结点存储到TpTree中

	int m1, m2;
	m1 = m2 = 0;
	for (int i = 0; i < j; i++)
	{
		if (TpTree[i].NewWeight < TpTree[m1].NewWeight)//此处不让取到相等，是因为结点中有相同权值的时候，m1取最前。
			m1 = i;
	}
	for (int i = 0; i < j; i++)
	{
		if (m1 == m2)
			m2++;//当m1在第一个位置的时候，m2向后移一位
		if (TpTree[i].NewWeight <= TpTree[m2].NewWeight && i != m1)//此处取到相等，是让在结点中有相同的权值的时候，m2取最后。

			m2 = i;
	}

	min1 = TpTree[m1].p;
	min2 = TpTree[m2].p;

}

//创建哈夫曼树
void createHuffmanTree(HuffmanTree& HuffTree,double messageP[], int sourceLength)
{

	int num;
	int min1, min2;

	num = 2 * sourceLength - 1;//哈夫曼树中结点的个数

	initHuffmanTree(HuffTree, num);

	for (int i = 0; i < sourceLength; i++)
	{
		HuffTree[i].weight=messageP[i];
	}

	for (int i = sourceLength; i < num; i++)
	{
		SelectMin(HuffTree, i, min1, min2);
		HuffTree[min1].parent = i;
		HuffTree[min2].parent = i;
		HuffTree[i].childLeft = min1;
		HuffTree[i].childRight = min2;
		HuffTree[i].weight = HuffTree[min1].weight + HuffTree[min2].weight;

		//cout << min1 << " " << min2 << endl;
	}
}

//构造哈夫曼编码

//哈夫曼编码定义
typedef struct
{
	char ch;
	char bits[10];
}CodeNode;

typedef CodeNode* HuffmanCode;

//哈夫曼编码的构造
void createHuffmanCode(HuffmanTree& HuffTree, HuffmanCode& HuffCode, int  sourceLength)
{
	
	int start;
	int c;
	int p;
	char* cd;
	char q;
	HuffCode = new CodeNode[sourceLength];
	cd = new char[sourceLength];
	cd[sourceLength - 1] = '\0';

	for (int i = 0; i < sourceLength; i++)
	{
		cin >> q;
		HuffCode[i].ch = q;
		start = sourceLength - 1;

		c = i;
		while ((p = HuffTree[c].parent) >= 0)
		{
			--start;
			cd[start] = (HuffTree[p].childLeft == c) ? '1' : '0';
			c = p;
		}
		strcpy_s(HuffCode[i].bits, &cd[start]);
	}

	delete cd;
}

//哈夫曼编码的输出与分析
void outputHuffmanCode(HuffmanCode& HuffCode,double messageP[], int sourceLength)
{
	for (int i = 0; i < sourceLength; i++)
	{
		cout << HuffCode[i].ch << " " << HuffCode[i].bits << endl;
	}
	double averageCodeLength = 0;//assign & initialize
	for (int i = 0; i < sourceLength; i++)
	{
		int lengthofch = 0;
		lengthofch = strlen(HuffCode[i].bits);
		averageCodeLength += lengthofch * messageP[i];
	}
	double averageCodeEntropy = 0;
	double codingEfficiency = 0;
	double codeRedundancy = 0;
	averageCodeEntropy = getSourceEntropy(messageP, sourceLength) / averageCodeLength;
	codingEfficiency = averageCodeEntropy / HmaxC;
	codeRedundancy = 1 - codingEfficiency;

	cout << "编码效率:" << 100 * codingEfficiency << "%" << endl;
	cout << "码冗余度" << 100 * codeRedundancy << "%" << endl;
}
//

void ShannonCoding(double messageP[],int sourceLength)//香农编码
{
	sort(messageP, messageP + sourceLength, greater<double>());
	int* codeLength=new int[sourceLength];//码长
	double tempCalStorage = 0;//临时寄存单元
	for (int i=0;i<sourceLength;i++)//calculate codeLength
	{
		tempCalStorage = -lb * log(messageP[i]);
		codeLength[i] = (int)tempCalStorage +1;
		cout << "codeLength:" << i << " " << codeLength[i]<<endl;
	}
	//calculate cumulative probabilities function
	double* cumuProb = new double[sourceLength];
	for (int i = 0; i < sourceLength; i++)
	{
		tempCalStorage = 0;//归零
		for(int j=0;j<i;j++)
		{
			tempCalStorage += messageP[j];
		}
		cumuProb[i] = tempCalStorage;
	}
	//covert F(xi) to binary and output;
	cout << "Shannon Coding as follow:" << endl;
	cout << "Sequence ShannonCode"<<endl;
	for (int j = 0; j < sourceLength; j++)
	{
		tempCalStorage = cumuProb[j];
		cout << " " <<j+1<<"        ";
		for (int i = 0; i < codeLength[j]; i++)
		{
			
			tempCalStorage *= 2;
			cout << (int)tempCalStorage;
			tempCalStorage -= (int)tempCalStorage;

		}
		cout << endl;
	}
	
	
	//calculate averageCodeLength
	double averageCodeLength = 0;//assign & initialize
	for (int i = 0; i < sourceLength; i++)
	{
		averageCodeLength += codeLength[i] * messageP[i];
	}
	double averageCodeEntropy=0;
	double codingEfficiency=0;
	double codeRedundancy=0;
	averageCodeEntropy = getSourceEntropy(messageP, sourceLength)/averageCodeLength;
	codingEfficiency = averageCodeEntropy / HmaxC;
	codeRedundancy = 1 - codingEfficiency;

	cout << "编码效率:" << 100 * codingEfficiency << "%" << endl;
	cout<<"码冗余度"<<100*codeRedundancy <<"%"<< endl;

	delete[] codeLength;
	delete[] cumuProb;

}

#define n 7
#define k 4
#define r 3//n,k,r values assigned for (7,4)Hamming Code;

void codingHummingCode()//汉明码(7,4)编码
{
	
	string origin;
	cout << "Please Input Original Code in 4 digits:" << endl;
	cin >> origin;
	int originCode[k];
	int superviseCode[r];
	for (int i = 0; i < k; i++)
	{
		originCode[i] =(int)origin[i];
	}
	//supervisionEquations
	superviseCode[0] = originCode[1] ^ originCode[2] ^ originCode[3];//x5=z2^x3^x4
	superviseCode[1] = originCode[0] ^ originCode[2] ^ originCode[3];//x6=x1^x3^x4
	superviseCode[2] = originCode[0] ^ originCode[1] ^ originCode[3];//x7=x1^x2^x4
	cout << "(7,4) Hamming Code of " << origin << " is:" << endl;
	for (int i = 0; i < k; i++)
		cout << originCode[i]-ASCIIconst1;//offseting
	for (int j = 0; j < r; j++)
		cout << superviseCode[j]-ASCIIconst1;
	cout << endl;
}

void decodingHummingCode()//汉明码(7,4)译码
{
	string Hamminged;
	cout << "Please Input Hamming Code in 7 digits:" << endl;
	cin >> Hamminged;
	int hamming[n];
	for (int i = 0; i < n; i++)
	{
		hamming[i] = ((int)Hamminged[i]) - ASCIIconst1;
		cout << hamming[i];
	}
	cout << endl;
	int checkCode[r] = { 0,0,0 };//assume as not wrong initialization
	int checkCodeList[n][r] = { { 0,1,1 },{ 1,0,1 },{1,1,0},{1,1,1},{1,0,0},{0,1,0},{0,0,1} };
	int noWrongCriteria[r] = { 0,0,0 };
	//checkCode Equations;
	checkCode[0] = hamming[1] ^ hamming[2] ^ hamming[3] ^ hamming[4];// s1=x2^x3^x4^x5
	checkCode[1] = hamming[0] ^ hamming[2] ^ hamming[3] ^ hamming[5];// s2=x1^x3^x4^x6
	checkCode[2] = hamming[0] ^ hamming[1] ^ hamming[3] ^ hamming[6];// s3=x1^x2^x4^x7
	cout << checkCode[0] << endl;
	cout << checkCode[1] << endl;
	cout << checkCode[2] << endl;
	if (checkCode[0] == noWrongCriteria[0]&&checkCode[1]==noWrongCriteria[1]&&checkCode[2]==noWrongCriteria[2])
	{
		cout << "No Wrong Code, original Code:";
		for (int i = 0; i < k; i++)
		{
			cout << hamming[i];
		}
	}
	else
	{
		for (int j = 0; j < n; j++)
		{
			if ((checkCode[0] == checkCodeList[j][0] && checkCode[1] == checkCodeList[j][1] && checkCode[2] == checkCodeList[j][2]))
			{
				cout << "Wrong code exists, wrong num:" << j + 1 << endl;
				hamming[j] = (hamming[j] == 0) ? 1:0;
				cout << "correctCode:";
				for (int w = 0; w < k; w++)
					cout << hamming[w];
				cout << endl;
				break;
			}
		}
	}
}




void cyclicDivisionCoding()//多项式除法电路循环码编码 以7,4循环码为基准
{

	int registerD[r] = { 0 };//置零
	string inputCode = { 0 };
	int cyclicCode[n] = { 0 };

	int generationPolynomial[r+1]={0};

	cout << "输入生成多项式中包含的项:(如g(x)=x^3+x+1,请输入1 0 1 1)" << endl;
	for (int l = 0; l < r +1; l++)
	{
		cin >> generationPolynomial[l];
	}
	//getInputCode
	cin >> inputCode;
	//直送m(r)
	for (int i = 0; i < k; i++)//下标倒序
	{
		cyclicCode[i] = (int)inputCode[i] - ASCIIconst1;
		//cout << cyclicCode[i];
	}//移入移位寄存器
	int feedback = 0;
	for (int j = 0; j < k; j++)
	{
		int feedbackA[r] = { 0 };
		if (generationPolynomial[r] == 1)
		{
			
			feedback = registerD[2] ^ (inputCode[j] - ASCIIconst1);
			//cout << "feedback:" << feedback << endl;
			
			feedbackA[0] = feedback;
			
		/*	cout << "feedback 0:" << feedbackA[0] << " ";
			cout << "register 0:" << registerD[0] << endl;*/
		}
	
	

		if (generationPolynomial[r - 1] == 1)
		{
			feedbackA[1] = feedback;
			

			//cout <<"feedback 1:"<< feedbackA[1]<<" ";
			//cout << "register 1:" << registerD[1] << endl;
		}
		/*else
		{
			cout << "feedback 1:" << feedbacka[1] << " ";
			cout << "register 1:" << registerd[1] << endl;
		}*/
		
		if (generationPolynomial[r - 2] == 1)
		{
			feedbackA[2] = feedback;
			
			/*cout << "feedback 2:" << feedbackA[2] <<" ";
			cout << "register 2:" << registerD[2] << endl;*/
		}
		//else
		//{

		//	cout << "feedback 2:" << feedbackA[2] << " ";
		//	cout << "register 2:" << registerD[2] << endl;
		//}
		
		
		
		if (generationPolynomial[r - 2] == 1)
		{
			registerD[2] = registerD[1] ^ feedbackA[2];
		}
		else
			registerD[2] = registerD[1];
		if (generationPolynomial[r - 1] == 1)
			registerD[1] = registerD[0] ^ feedbackA[1];
		else
			registerD[1] = registerD[0];
		registerD[0] = feedback;
		
		//cout << "register 0:" << registerd[0] << "register 1:" << registerd[1] << "register 2:" << registerd[2] << endl;


	}

	for (int i = k,j=2; i < n; i++,j--)
	{
		cyclicCode[i] = registerD[j];
	}
	cout << "(7,4)循环码电路编码结果为:";
	for (int i = 0; i < n; i++)
	{
		cout << cyclicCode[i];
	}
	cout << endl;
}

void cyclicDivisionDecoding()//多项式除法电路循环码译码
{
	string cyclicCode = "";
	cout << "输入7位循环码元:";
	cin >> cyclicCode;
	int registerD[r] = { 0 };//置零
	int cyclicCodeOperate[n] = { 0 };
	int checkCodeRegister[r] = { 0 };
	int checkCodeList[n][r] = { {1,0,1} ,{1,1,1} ,{1,1,0} ,{0,1,1} ,{1,0,0},{0,1,0}, {0,0,1}};//对于g(x)=x^3+x+1// C6~C0
	for (int i = 0; i < n; i++)//下标倒序
	{
		cyclicCodeOperate[i] = (int)cyclicCode[i] - ASCIIconst1;
		//	cout << cyclicCodeOperate[i];
	}

	//译码
	int generationPolynomial[r + 1] = { 0 };

	cout << "输入生成多项式中包含的项:(如g(x)=x^3+x+1,请输入1 0 1 1,(为便确认校验子表，此处限定该生成多项式))" << endl;
	for (int l = 0; l < r + 1; l++)
	{
		cin >> generationPolynomial[l];
	}

	for (int j = 0; j < n; j++)
	{
		int feedbackA[r] = { 0 };
		int feedback = 0;
		if (generationPolynomial[r] == 1)
		{

			feedback = registerD[2];
			//cout << "feedback:" << feedback << endl;

			feedbackA[0] = feedback ^ (cyclicCodeOperate[j] - ASCIIconst1);

			/*	cout << "feedback 0:" << feedbackA[0] << " ";
				cout << "register 0:" << registerD[0] << endl;*/
		}



		if (generationPolynomial[r - 1] == 1)
		{
			feedbackA[1] = feedback;


			//cout <<"feedback 1:"<< feedbackA[1]<<" ";
			//cout << "register 1:" << registerD[1] << endl;
		}
		/*else
		{
			cout << "feedback 1:" << feedbacka[1] << " ";
			cout << "register 1:" << registerd[1] << endl;
		}*/

		if (generationPolynomial[r - 2] == 1)
		{
			feedbackA[2] = feedback;

			/*cout << "feedback 2:" << feedbackA[2] <<" ";
			cout << "register 2:" << registerD[2] << endl;*/
		}
		//else
		//{

		//	cout << "feedback 2:" << feedbackA[2] << " ";
		//	cout << "register 2:" << registerD[2] << endl;
		//}



		if (generationPolynomial[r - 2] == 1)
		{
			registerD[2] = registerD[1] ^ feedbackA[2];
		}
		else
			registerD[2] = registerD[1];
		if (generationPolynomial[r - 1] == 1)
			registerD[1] = registerD[0] ^ feedbackA[1];
		else
			registerD[1] = registerD[0];
		registerD[0] = feedbackA[0];

		//cout << "register 0:" << registerD[0] << " register 1:" << registerD[1] << " register 2:" << registerD[2] << endl;
		for (int i = 0, j = r - 1; i < r; i++, j--)
		{
			checkCodeRegister[i] = registerD[j];

		}
		
	
		if ((checkCodeRegister[0] == 0) && (checkCodeRegister[1] == 0 ) && (checkCodeRegister[2] == 0))
		{
			cout << "No Wrong Code, original Code:";
			for (int i = 0; i < k; i++)
			{
				cout << cyclicCodeOperate[i];
			}
			cout << endl;
			cout << "校验子s2s1s0:";
			for (int i = 0; i < r; i++)
				cout << checkCodeRegister[i];
			cout << endl;
			break;
		}
		else {
			for (int m = 0; m < n; m++)
			{
				if ((checkCodeRegister[0] == checkCodeList[m][0]) && (checkCodeRegister[1] == checkCodeList[m][1]) && (checkCodeRegister[2] == checkCodeList[m][2]))
				{
					
					cout << "Wrong code exists, wrong num:C" << n-m-1 << endl;
					cyclicCodeOperate[m] = cyclicCodeOperate[m] == 0 ? 1 : 0;
					cout << "correctCode:";
					for (int w = 0; w < k; w++)
						cout << cyclicCodeOperate[w];
					cout << endl;
					cout << "校验子s2s1s0:";
					for (int i = 0; i < r; i++)
						cout << checkCodeRegister[i];
					cout << endl;
					break;
				}
			}
		}
	}
}



void convolutionCoding()//分组并行输入的(4,3,3)卷积码编码
{
	int convoN=4;
	int convoK=3;
	int convoM=3;
	int superviseCodeLength = convoN - convoK;//1
	//并行输入，采用m-1个移位寄存器(对于4,3,3为2个)
	//由监督矩阵[H]或者说p2,p1,p0确定异或逻辑
	//for (4,3,3) convolution code,
	//[H]=[ 1 1 1 1                 ]
	//    [ 1 0 1 0 1 1 1 1         ]
	//    [ 1 1 0 0 1 0 1 0 1 1 1 1 ]
	//        p2      p1      p0

	int registers[2] = {0};//移位寄存器
	
	string inputCode = "";
	//getInputCode
	cout << "请输入卷积码待编码序列:";
	cin >> inputCode;
	int* convolutionCode = new int[inputCode.length()];

	
	
	//直送m(r)
	for (int i = 0; i < inputCode.length(); i++)
	{
		convolutionCode[i] = (int)inputCode[i] - ASCIIconst1;
		//cout << convolutionCode[i];
	}

	//start convoluting;
	int supervisionOutputCode = 0;
	//step1: 寄存器置零
	//三个一组并行输入
	for (int i = 0; i < inputCode.length(); i+=3)
	{
		supervisionOutputCode = convolutionCode[i] ^ convolutionCode[i + 1] ^ convolutionCode[i + 2] ^ registers[1];//register D1=0;
		registers[1] = convolutionCode[i] ^ convolutionCode[i + 2] ^ registers[0];//D0=0;
		registers[0] = convolutionCode[i] ^ convolutionCode[i + 1];

		cout << convolutionCode[i] << convolutionCode[i + 1] << convolutionCode[i + 2] << supervisionOutputCode<<" ";
	}

}


//主函数
int main()
{

//自信息量
	double messageProb;
	cout << "请输入任意消息概率求其自信息量:" << endl;
	cin >> messageProb;
	double aSIQ;
	aSIQ = getSelfInfoQuantity(messageProb);
	cout <<"自信息量:"<<endl<< aSIQ << endl;
	int flag = 0;
//信源熵及冗余度
	//定义
	
	double arrayProb[8] = { 0.4,0.18,0.1,0.1,0.07,0.06,0.05,0.04};
	//
	//获取信源个数
	int sourceLength;
	sourceLength = getSourceLength(arrayProb);

//	cout << "Please Select: "<<endl<<"    1.getEntropy; 2.getRedundancy"<< endl;
//	
//	cin >> flag;
//	cout << endl;
//	switch (flag) {	
//		case 1:
//			cout << "信源熵:" << getSourceEntropy(arrayProb, sourceLength) << endl; 
//			break;
//		case 2:
//			cout <<"冗余度:"<< 100*getRedundancy(arrayProb, sourceLength,getSourceEntropy(arrayProb, sourceLength)) <<"%"<< endl;
//			break;
//}
//	cout << endl;
//	//switch case select CodingMode
//	//Fano
//	string Fano = ""; // 费诺编码结果 
//	int* codeLength = new int[sourceLength];
//
//	for (int i = 0; i < sourceLength; i++)
//	{
//		codeLength[i] = 0;//初始化码长储存器
//	}
//	
//	double avrCodeLength = 0;
//	FanoCoding(arrayProb, sourceLength, 0, sourceLength - 1, Fano,codeLength);
//	cout << "平均码长:" << recursCodeLength << endl;
//	FanoAnalyzing(arrayProb,sourceLength,recursCodeLength);
//	cout << endl;
//	delete[] codeLength;
	HuffmanTree HuffTree;
	/*HuffmanCode HuffCode;

	createHuffmanTree(HuffTree,arrayProb, sourceLength);
	createHuffmanCode(HuffTree, HuffCode, sourceLength);
	outputHuffmanCode(HuffCode,arrayProb, sourceLength);*/

	//cout << sourceLength << endl;
	

//	ShannonCoding(arrayProb, sourceLength);
	//codingHummingCode();
	//decodingHummingCode();
	//cyclicDivisionCoding();
	//cyclicDivisionDecoding();

	convolutionCoding();
	return 0;
}

