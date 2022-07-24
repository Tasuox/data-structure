//半天没结果 处于调试 界面 就是太卡了 突如其来 如风消逝

#include <iostream>
#define InitSize 10

using namespace std;
struct  SqList {
	int length;
	int MaxSize;
	//int* data;//动态创建数组分两步，先创建指针，然后在申请空间
	int data[InitSize];
};
//基本操作
bool InsertList(SqList& L, int i, int e);
bool DeleteList(SqList& L, int i);
int SearchList(SqList& L, int e);
int SearchListForXInexist(SqList& L, int e);
int SearchListForSecond(SqList& L, int e);
void SelectionSort(SqList& L);
//题目
bool DeleteMin(SqList& a);
void Reverse(SqList& a);
void DeleteX(SqList& a, int b);
bool DeleteXBetweenSandT(SqList& a, int b, int c);
void DeleteDuplicateX(SqList& a);
SqList MergeSandL(SqList& S, SqList& L);
SqList ReverseListAandB(SqList& L, int m, int n);
void FindXandReverseorInsertX(SqList& L, int e);
void LeftShiftList(SqList& L, int i);
int GetMidNum(SqList& L, SqList& S);
int GetMainNum(SqList& L);
int GetMinimumPositiveIntegerDoesNotAppear(SqList& L);

void printL(SqList& a);

int main()
{
	SqList L = {
	L.length = 0,
	L.MaxSize = 10,
	//L.data = new int[InitSize],//动态申请数组
	};
	SqList S = {
	S.length = 0,
	S.MaxSize = 10,
	};
	InsertList(L, 1, 3);
	InsertList(L, 2, 2);
	InsertList(L, 3, 1);
	InsertList(L, 4, 4);
	InsertList(L, 5, 9);

	InsertList(S, 1, 3);
	InsertList(S, 2, 4);
	InsertList(S, 3, 5);
	/*DeleteList(L, 3);
	DeleteList(L, 2);
	DeleteList(L, 1);
	DeleteList(L, 1);*/
	//SearchList(L, 5);

	//题目
	//DeleteMin(L);
	//Reverse(L);
	//DeleteX(L, 2);
	//DeleteXBetweenSandT(L, 2, 4);
	//DeleteDuplicateX(L);
	//MergeSandL(S, L);
	//ReverseListAandB(L, 3, 2);
	//FindXandReverseorInsertX(L,99);
	//LeftShiftList(L, 2);
	//cout << GetMidNum(S, L) << endl;
	//cout << GetMainNum(L) << endl;
	cout << GetMinimumPositiveIntegerDoesNotAppear(L) << endl;
	//printL(L);
	printL(L);
	return 0;
}
//基础操作
//按位序插入
bool InsertList(SqList& L, int i, int e) {//i插入元素的位置（位序）；e待插入元素
	if (i<1 || i>L.length + 1 || L.length >= L.MaxSize) {
		cout << "wrong!" << endl;
		return false;
	}
	for (int j = L.length; j >= i; j--) {//j也是位序，=i是为了把i上原本的元素后移
		L.data[j] = L.data[j - 1];//位序到坐标记得-1
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}
//按位序删除
bool DeleteList(SqList& L, int i) {
	if (i < 1 || i> L.length+1 || L.length < 1) {
		cout << "wrong!" << endl;
		return false;
	}
	for (int j = i; j < L.length; j++) {//这里j也是位序，转化下标注意-1
		L.data[j - 1] = L.data[j];//后面的值往前移动
	}
	L.length--;
	//printL(L);
	return true;
}
//按值查找一个元素 //删除重复元素时，这里会找到自身，所以并不好用
int SearchList(SqList& L, int e) {//这里返回位序,>=1，所以返回0就是出错了。
	for (int j = 0; j < L.length; j++) {//j这里是下标
		if (e == L.data[j]) {
			//cout << "this num is local in: " << j + 1 << endl;
			return j + 1;//返回位序
		}
	}
	cout << "not found" << endl;
	return 0;//表示没有找到
}
//按不存于表中的值，查找其应该处于表中的位置(返回位序)
int SearchListForXInexist(SqList& L, int e) {
	for (int j = 0; j < L.length; j++) {//j，下标
		if (e > L.data[j] && e < L.data[j + 1]) {
			//比如e = 4，应该放到3和99中间，实际上取代了99的位置，而j+1是元素3所在的位序
			return (j + 1) + 1;
		}
		else if (e < L.data[0]) {
			return 1;
		}
		else if (e > L.data[L.length - 1]) {//如果e大于L中最后一个（也就是最大的元素）
			return L.length + 1;//那么它就应该放在最后一个位置,也就是=（新）length=L.length + 1
		}
	}
}
//按值查找元素在表中的第二个相同元素
int SearchListForSecond(SqList& L, int e) {//根据元素值找顺序表中第二个元素所在位置
	int count = 0;
	for (int j = 0; j < L.length; j++) {//j这里是下标
		if (e == L.data[j]) {//第一次找到，不执行return，让count+1
			if (count == 1) {
				return j + 1;//返回位序
			}
			count++;
		}
	}
	cout << "not found" << endl;
	return 0;//表示没有找到
}
//选择排序
void SelectionSort(SqList& L) {
	int i; int k = 0;
	for (int j = 0; j < L.length; j++) {
		int minNum = 999;//这个是当前遍历位置到后面，这一范围内的最小值，非整体的最小值
		for (i = j; i < L.length; i++) {
			if (minNum > L.data[i]) {
				minNum = L.data[i];
				k = i;
			}
		}
		if (L.data[j] > minNum) {//更改后面最小值和当前“首”元素位置
			L.data[k] = L.data[j];//首元素值赋给之后的最小元素（“首”元素依次后移，并非真正的首元素）
			L.data[j] = minNum;
		}
	}
}

//题目
//1
bool DeleteMin(SqList& L) {
	int min = 9999;
	if (L.length < 1) {
		cout << "this array is empty.\n";
		return false;
	}
	int j;
	for (j = 0; j < L.length; j++) {
		if (min > L.data[j]) {
			min = L.data[j];
		}
	}cout << "min is:" << min << endl;//cout输出时当有字符串和数字，不使用+而是使用<<！
	L.data[j] = L.data[L.length - 1];
	cout << "last num is:" << L.data[j] << endl;
	L.length--;
	return true;
}
//2
void Reverse(SqList& L)
{
	int temp;
	for (int j = 0; j < L.length / 2; j++) {//注意光标只走一半，此时后面的也完成了交换
		temp = L.data[L.length - 1 - j];
		L.data[L.length - 1 - j] = L.data[j];
		L.data[j] = temp;
	}
}
//3 -- 时间复杂度n*n ==> 先遍历一遍，遇到要删除的就让后面代替，但是，后面替代它的数不能是删除范围内的
//==> 大致思路不变，只是这次用两个光标，i负责寻找要删除的数据，j负责寻找后面符合条件的替代数据
void DeleteX(SqList& L, int x) {
	int j = 0; int i = 1;
	while (j < L.length - 1) {
		if (L.data[j] == x) {//找到待删除数据，如果
			if (L.data[j + i] == x) {//如果后面的1到i个数据是否也是待删除数据，当+1未找到数据时，
				//由于大光标没有变，程序将按原路再次走到这里，然后再+1，如此便能扩大搜索的范围
				i++;
				if (i + j == L.length) {//如果从大光标所处后一个位置搜索后面所有的位置都还没有可移动过来的，就结束
					break;
				}
			}
			else {//直到找到非删除数据，
				L.data[j] = L.data[j + i]; //把它的值覆盖过来
				L.data[j + i] = x;//再原本值设置为要删除的值
				j++;//处理完毕，才让大光标后移，处理下一个数据
				i = 1;//处理完毕，小光标置为初始值，以便下次再从j+1，j+2，j+3
			}
		}
		else {//不相等就让光标后移
			j++;
		}
	}
	cout << " i : " << i << " j : " << j << endl;
	int count = 0;
	for (int n = L.length - 1; n > 0; n--) {
		if (L.data[n] == x) {
			count++;
		}
	}
	L.length -= count;
}
//4,5(4是有序，5是随意顺序表)
bool DeleteXBetweenSandT(SqList& L, int s, int t) {
	if (s >= t || L.length < 1) {
		cout << "not valid s and t, or this array is empty" << endl;
		return false;
	}
	int j = 0; //j是下标
	int i = 1;
	while (j < L.length - 1) {
		if (L.data[j]<t && L.data[j]>s) {//找到要删除的数据，从这里开始，往后查找
			if (L.data[j + i]<t && L.data[j + i]>s) {//j+1,j+2,j+3,j+4
				i++;
				if (i + j == L.length) {//如果后面所有数据都要删除，就结束
					break;
				}
			}
			else {//找到非删除数据
				L.data[j] = L.data[j + i]; //把它的值覆盖过来
				L.data[j + i] = s + 1;//把原本位置的值设置为要删除值
				j++;//处理完毕，大光标后移，处理下一个数据
				i = 1;//处理完毕，小光标置为初始值，以便下次再j+1，j+2，j+3
			}
		}
		else {//大光标找到非删除数据
			j++;//大光标后移
		}
	}
	int count = 0;
	for (int n = L.length; n >= 1; n--) {
		if (L.data[n - 1]<t && L.data[n - 1]>s) {
			count++;
		}
	}
	L.length -= count;
	//注意：return不能写到print的前面，否则什么都看不到了
	return true;
}
//6
void DeleteDuplicateX(SqList& L) {//特殊删除函数，只允许每个数字的第一次出现
	//第一个元素在顺序表中的第一元素所在，就是自身。
	//int local;//避免Search函数执行两次;必须执行两次，while中删除元素结束后得变值，否则退不出循环
	for (int i = 0; i < L.length; i++) {
		//while就是if的升级版，if中满足条件执行一次，while中满足条件执行n次
		while (SearchListForSecond(L, L.data[i]) != 0) {//删除该元素在表中的第二个相同元素
			DeleteList(L, SearchListForSecond(L, L.data[i]));
		}//若还有相同元素（返回值不=0）就再次进入循环
	}
	//--------思路二：（需要先排序！）每遍历一个元素就统计后面有多少个相同的元素，然后执行该次数的删除
	SelectionSort(L);
	int j;
	for (j = 0; j < L.length; j++) {
		int count = 0;
		while (L.data[j] == L.data[j + 1 + count] && j + 1 + count < L.length) {//1122233首先1会比较1次，删除首位置1一次=122233，j+1，到2位置，计数2次，按2所在位置删除两次
			//删除元素实际是往前移动，而后面原本的没有变，只是减少了表长来表示，这里由于后面没有删除，1334-》1344（只是长度减1，显示134），而判断重复的语句看到4后面还有4，就会再删除
			count++;
		}
		for (int i = 0; i < count; i++) {
			DeleteList(L, j + 1);//j是位序，函数要求输入下标
		}
	}
}
//7 
SqList MergeSandL(SqList& S, SqList& L) {
	for (int l = 0; l < L.length; l++) {//排序算法
		for (int s = 0; s < S.length; s++) {//L里面找到最小的，然后去S里找大于它的最小的值
			if (L.data[l] < S.data[s]) {
				//这里之所以产生问题，是因为s是【下标】而非【位序】，插入函数中i是位序
				InsertList(S, s + 1, L.data[l]);//把 L.data[l]放到S中的s位置
				break;
			}
			else if (L.data[l] > S.data[S.length - 1]) {//如果L里面找到的最小的，还是大于S里面的最大的，那就把L中最小元素连同后面的所有元素都添加到S的最后面
				for (int k = l; k < L.length; k++) {//往后移动数据，当然要从最后面的开始
					S.data[S.length] = L.data[k];
					S.length++;
				}
			}
		}
	}
	return S;
}
//8
SqList ReverseListAandB(SqList& L, int m, int n) {
	SqList tempList = {
	tempList.length = 0,
	tempList.MaxSize = 10,
	};
	for (int i = 1; i < m + 1; i++) {//遍历原顺序表把A表(m个元素)的元素添加到临时表中，i这里使用位序，调用后面函数方便点
		//如果一个顺序表长2，L.data[m]刚好是它后面一个格子的位置
		InsertList(tempList, i, L.data[0]);//每次把表头添加过去，然后后面所有元素往前移动
		DeleteList(L, 1);//删除原表中A表的元素并把B表往前移动
		//所以“迁移”元素下标和删除元素的位序不变
	}
	//printL(tempList);
	for (int j = 1; j < tempList.length + 1; j++) {//此时L中前面是n个元素的B表
		InsertList(L, n + j, tempList.data[j - 1]);//把临时表中的元素添加到L中的B表后面
	}
	return L;
}
//9
void FindXandReverseorInsertX(SqList& L, int e) {
	int localE, temp;
	localE = SearchList(L, e);
	temp = e;
	if (localE != 0) {//查找成功
		L.data[localE - 1] = L.data[localE];//后面的值移到E处
		L.data[localE] = e;
	}
	else {//查找失败
		int i = SearchListForXInexist(L, e);
		InsertList(L, i, e);
	}
}
//10（真）
//(1)思路：先使用插入函数将集合中的数添加到顺序表中；
//首先提出表首元素，然后删除表首元素，最后把表首元素赋值到末尾
//（2）
void LeftShiftList(SqList& L, int i) {
	int temp;
	for (int j = 1; j < i + 1; j++) {//左移i个位置
		temp = L.data[0];//将表首元素取出，然后删除表首，这会让剩下元素左移（length会-1，因此要+1）
		DeleteList(L, 1);
		L.length++;
		L.data[L.length - 1] = temp;//把表头元素移到最后一个位置
	}
}

//11
//1.两个升序列表各自有一个指针，每次比较两个列表中的数据，取出较小者，当取出的是L/2位置的数据，就是中位数
int GetMidNum(SqList& L, SqList& S) {
	int MidNum = 0;//返回0表示出错
	int local = 1;//位序从1开始
	int S_point = 0;
	int L_point = 0;
	while (local <= (L.length + S.length) / 2) {
		if (L.data[L_point] <= S.data[S_point]) {
			MidNum = L.data[L_point];
			L_point++;
		}
		else {
			MidNum = S.data[S_point];
			S_point++;
		}
		local++;
	}
	return MidNum;
}

//12
//1.主元素必须个数超过总体一半，也就是说，如果最多出现元素的个数等于一半或者小于，都是没有主元素的
//首先排序，然后遍历整个顺序表，当某个元素后一个元素和它相同，就让计数器+1，并把主要元素设定为它，当别的
 //元素个数超过，就换它做主要元素，最后看个数是否满足要求，如果是返回，不是返回-1
int GetMainNum(SqList& L) {
	int MainNum = 0;
	//选择排序
	SelectionSort(L);
	//统计
	int Totalcount = 0;//这里最后判断的时候要+1，例如1，1，1，1，比较三次count+3，实际上是4个
	for (int j = 0; j < L.length - 1; j++) {
		int count = 0;
		int n = j;
		while (L.data[n] == L.data[n + 1 + count]) {//排序完成后，相同元素肯定相邻，这里比较某一元素和后面1234...个元素是否相同
			count++;
		}
		if (Totalcount < count) {
			Totalcount = count;
			MainNum = L.data[n];
		}
	}
	//判断是否是主要元素
	if (Totalcount + 1 > L.length / 2) {
		return MainNum;
	}
	else {
		return -1;
	}
}

//13
//找未出现最小正整数，采取比对方法，首先排序，然后去除重复元素，接着用1，2，3依次开始比对，直到出现
//表中没有的元素即是所求结果
int GetMinimumPositiveIntegerDoesNotAppear(SqList& L) {
	//排序
	SelectionSort(L);
	//printL(L);
	//删除重复元素
	int j;
	for (j = 0; j < L.length; j++) {
		int count = 0;
		while (L.data[j] == L.data[j + 1 + count] && j+1+count<L.length) {//1122233首先1会比较1次，删除首位置1一次=122233，j+1，到2位置，计数2次，按2所在位置删除两次
			//删除元素实际是往前移动，而后面原本的没有变，只是减少了表长来表示，这里由于后面没有删除，1334-》1344（只是长度减1，显示134），而判断重复的语句看到4后面还有4，就会再删除
			count++;
		}
		for (int i = 0; i < count; i++) {
			DeleteList(L, j+1);//j是位序，函数要求输入下标
		}
	}
	//printL(L);
	//比较
	int flag = false;
	for (int num = 1; num < 99; num++) {//这里限定置用1到99之间的数去比较
		for (int k = 0; k < L.length; k++) {
			flag = true;
			if (num == L.data[k]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			return num;
		}
	}
	return -1;//如果1到99比较完都有，那么就返回-1，超过了比较范围
}

//辅助函数，打印数组的值
void printL(SqList& L) {
	for (int x = 0; x < L.length; x++) {
		cout << "new array:" << L.data[x] << endl;
	}
	cout << "L.length is: " << L.length << endl;
	//cout << " show data[4]: " << L.data[4] << endl;
}
