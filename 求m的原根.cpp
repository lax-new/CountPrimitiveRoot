#include<stdio.h>

int size;

bool juge_ifprime(int m){		//判断输入的m是否为奇素数 
	for(int i=2;i<=m/2;i++){
		if(m%i==0)
			return false;		//如果最大公因子为1返回false 
	}
	return true;				//否则返回true
}

void count_EulerNot(int m,int* array){	//计算输入的m的素数分解式 
	int temp1=m;
	if(int(juge_ifprime(m))==1){		//如果输入的m为奇素数，将其减一之后再算 
		temp1-=1;
	}
	int number=0;						//存放素因数的数组指针 
	int temp=temp1; 
	while(temp!=1){
		for(int i=2;i<=temp;i++){
			if(int(juge_ifprime(i))==1&&temp%i==0&&i!=m)
			{
				array[number++]=i;
				temp/=i;				//找到一个素因数(或当i=m)之后将temp除以i改变temp的值使得它能跳出循环
			}
		}						 
	}
} 

int count_Euler(int *array,int m){
	int Eulernumber;
	if(int(juge_ifprime(m))==1){
		return m-1;
	}
	else{
	for(int i=0;i<size;i++){
		if(array[i]!=-1){
			Eulernumber=m/array[i]*(array[i]-1);
		}
	}
	return Eulernumber;}
}

bool juge_HUSU(int a,int m){	//判断两数是否互素,即它们的最大公约数是否为1 
	for(int i=2;i<=a;i++){
		if(a%i==0&&m%i==0){
			return false;
		}
	}
	return true;
} 

void count_mHUSU(int *brrby,int m){	//求与m互素的数的数组的函数,并求出最小原根(第二次调用的时候求的是和欧拉函数互素的数组)
	int number=0;					//遍历并存储brrby数组的int型指针 
	int temp=m;
	for(int i=1;i<temp;i++){
		if(juge_HUSU(i,temp)!=0&&number<size){
			brrby[number++]=i;
		}
	}
} 

bool juge_MinPrimitiveRoot(int temp,int brrby,int m){	//在brrby数组中选一个与m互素的数计算它的temp次方是否mod m余m-1判断它是否为最小原根 
	int number=1;			//定义一个number用于存放传入的temp的值 
	for(int i=0;i<temp;i++){
		number*=brrby;
		number=number%m;
		if(number==1)
		return false; 
	}
	if(number==m-1)
	return true;
	else
	return false;
}

int count_MinPrimitiveRoot(int m,int *array,int *brrby,int Eulernumber){//计算最小原根,其中array为素因数数组,brrby为与欧拉函数互素的数的数组 
	int temp;
	for(int i=0;i<size;i++){
		if(array[i]!=-1){
			for(int j=0;j<size;j++){
			temp=Eulernumber/array[i];	//欧拉函数和素因数的除数q
			if(int(juge_MinPrimitiveRoot(temp,brrby[j],m))==0){
				
			} 
			if(int(juge_MinPrimitiveRoot(temp,brrby[j],m))==1&&brrby[j]!=-1){
				return brrby[j];
			}
			}
		}
	}
	return -1;
}

void Sort(int* array){		//对array数组从大到小排序 
	int temp;				//临时变量用于交换数组元素 
	for(int i=0;i<size;i++){
		for(int j=i+1;j<size;j++){
			if(array[i]!=-1&&array[j]!=-1&&array[i]>array[j]){
				temp=array[i];
				array[i]=array[j];
				array[j]=temp;
			}
		}
	}
} 

void Delete_same(int *array){		//将素因数数组的相同元素剔除 
	for(int i=0;i<size;i++){
		for(int j=i+1;j<size;j++){
			if(array[i]==array[j]){
				array[j]=-1;
			}
		}
	}
}

void ALL_primeroot(int minprimerroot,int *drrdy,int *crrcy,int m){	//传入的参数为最小原根和与m互素的数组drrdy，函数求出所有的原根并存在crrcy数组里 
	int temp=1;
	for(int i=0;i<size;i++){
		if(drrdy[i]!=-1){
			for(int j=0;j<drrdy[i];j++){
				temp*=minprimerroot;
				temp%=m;
			}
			crrcy[i]=temp;
			temp=1;
		}
	}
} 

int main(){
	int m;
	printf("输入你要求的数：");
	scanf("%d",&m);					//输入需要求的原根数m 
	size=m/2;
	int array[size];					//用于存放素因数的数组array 
	int brrby[size];					//用于存放与m互素的数字的数组 
	int crrcy[size];					//用于存放m的所有原根的数组 
	int drrdy[size];
	for(int i=0;i<size;i++){			//将此数组全部数据初始化为-1,用于区分 
		array[i]=-1;
		brrby[i]=-1;
		crrcy[i]=-1; 
		drrdy[i]=-1;
	}
	count_EulerNot(m,array);		//此时array数组里不为-1的就是m的素因数分解 
	Delete_same(array);				//剔除array数组里相同的数
	int Eulernumber=count_Euler(array,m);	//计算m的欧拉函数 
	count_EulerNot(Eulernumber,array);		//此时array数组里不为-1的就是m的素因数分解 
	Delete_same(array);				//剔除array数组里相同的数
	Sort(array);					//对数组array进行从大到小的排序 
	count_mHUSU(brrby,m);			//求与m互素的元素，放入brrby中
	int minprimerroot=count_MinPrimitiveRoot(m,array,brrby,Eulernumber);//求最小原根 
	if(minprimerroot==-1){
		printf("该数没有原根！\n");
		return 0;
	}
	printf("最小原根为：%d\n",minprimerroot);	//打印最小原根
	count_mHUSU(drrdy,Eulernumber);			//求与Eulernumber互素的元素，放入brrby中
	ALL_primeroot(minprimerroot,drrdy,crrcy,m);	//知道最小原根之后进行遍历求出其他所有原根 
	Sort(crrcy);					//对数组crrcy进行从大到小的排序 
	int primernumber=0;				//定义用于计算原根个数的变量 
	for(int i=0;i<size;i++){		//对brrby数组进行遍历，找出有多少个原根 
		if(drrdy[i]!=-1){
			primernumber++;
		}
	}
	printf("欧拉函数的值为：%d\n",Eulernumber);	//输出欧拉函数的值 
	printf("一共有%d个原根！\n原根从大到小排列为：\n",primernumber);//输出原根的个数 
	for(int i=0;i<size;i++){		//打印数组crrcy里的内容 
		if(crrcy[i]!=-1){
			printf("%d\t",crrcy[i]);
		}
	}
	printf("\n");
}
