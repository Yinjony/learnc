#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define INFINITY 32768
typedef int Keytype;
typedef char OtherType;
typedef struct{
    Keytype key;
    OtherType other_data;
}RecordType;
//插入类排序
//直接插入排序：具有稳定性
void InsSort(RecordType r[],int n){//数组r，n为数目
    for(int i=2;i<=n;i++){//自前向后，依次比较
        r[0]=r[i];//0处为监视哨，先把要插入的数据放到里面
        int j=i-1;//从i的前一位开始比较，
        while(r[0].key<r[j].key){//如果插入值小于目前所在的值
            r[j+1]=r[j];//整体向后移
            j--;//然后再向前比较
        }
        r[j+1]=r[0];//遇到不能再小的的值时，插入到该位的下一位，完成排序
    }
}
//折半插入排序：具有稳定性
void BinSort(RecordType r[],int n){
    for(int i=2;i<=n;i++){
        RecordType x=r[i];//对i进行插入
        int low=1,high=i-1;//i-1为封顶，将i插入到1~i-1之间
        while(low<=high){//进行折半查找
            int mid=(low+high)/2;
            if(x.key<r[mid].key) high=mid-1;
            else low=mid+1;
        }
        for(int j=i-1;j>=low;j--) r[j+1]=r[j];//找到目标位置后，进行整体向后移动，空出位置
        r[low]=x;//然后插入
    }
}
//希尔排序：不具有稳定性，例如{2,4,1,2}
void ShellInsert(RecordType r[],int n,int delta){//近似于等差数列，所以d为1时，就是插入排序
    for(int i=1+delta;i<=n;i++){
        if(r[i].key<r[i-delta].key){//让1+d和1位置的关键字进行比较
            r[0]=r[i];//放到监视哨里
            int j;
            for(j=i-delta;j>0&&r[0].key<r[j].key;j-=delta) r[j+delta]=r[j];//每隔d项的关键字组成一个子排序列，进行插入排序    
            r[j+delta]=r[0];//其实是进行交换
        }
    }
}
void ShellSort(RecordType r[],int n,int delta[],int m){
    //增量取法，有Shell提出的d=floor(n/2),d=floor(d/2),直到d=1,；也有Knuth提出的d=floor(d/3)+1等等
    for(int i=0;i<=m-1;i++) ShellInsert(r,n,delta[i]);//对每一个d值进行排序
}

//交换类排序
//冒泡排序：具有稳定性
void BubbleSort(RecordType r[],int n){
    bool change=true;
    for(int i=1;i<=n-1&&change;i++){//比较n-1趟
        change=false;
        RecordType x;
        for(int j=1;j<=n-i;j++){
            if(r[j].key>r[j+1].key){
                x=r[j];
                r[j]=r[j+1];
                r[j+1]=x;
                change=true;
            }
        }
    }
}
//快速排序：不具有稳定性，例如{3,3,2}
int QKPass(RecordType r[],int low,int high){//一趟快速排序
    RecordType x=r[low];//意为将r[low]处置为空单元
    while(low<high){
        while(low<high&&r[high].key>=x.key) high--;//找到右半部分比x小的
        if(low<high){//然后放到左边空单元处
            r[low]=r[high];//右边成空单元
            low++;
        }
        while(low<high&&r[low].key<x.key) low++;//找到左半部分比x大的
        if(low<high){//然后放到右边空单元处
            r[high]=r[low];//左边成空单元
            high--;
        }
    }
    r[low]=x;//然后插入
    return low;
}
void QKSort(RecordType r[],int low,int high){
    if(low<high){
        int pos=QKPass(r,low,high);//先进行一趟排序
        QKSort(r,low,pos-1);//对左半部分排序
        QKSort(r,pos+1,high);//对右半部分排序
    }
}

//选择类排序
//简单选择排序：不具有稳定性，例如{3,3,2}
void SelectSort(RecordType r[],int n){//向后找更小的关键字，然后进行互换
    for(int i=1;i<=n-1;i++){
        int k=i;
        for(int j=i+1;j<=n;j++) if(r[j].key<r[k].key) k=j;
        if(k!=i){
            RecordType x=r[i];
            r[i]=r[k];
            r[k]=x;        
        }
    }
}
//树形选择排序：具有稳定性
//堆排序：不具有稳定性，例如{5,5,3}，树形排序的改良版
void sift(RecordType r[],int k,int m){//重建堆，r[k...m]，以r[k]为根的大根堆（虽然不是树结构，但是看作是树结构）
    RecordType t=r[k];//将最顶部的数据存放起来
    Keytype x=r[k].key;
    int i=k;
    int j=2*i;//左子树
    bool finished=false;
    while(j<=m&&!finished){
        if(j+1<=m&&r[j].key<r[j+1].key) j++;//如果右子树更大则转到右子树里面去筛选
        if(x>=r[j].key) finished=true;//筛选完毕
        else{
            r[i]=r[j];//小于的话，那么该处的记录上移，然后该处当作是t所在位置
            i=j;
            j=2*i;
        }
    }
    r[i]=t;//将t填入恰当的位置
}
void crt_heap(RecordType r[],int n){//建立初始堆
    for(int i=n/2;i>=1;i--){//从第floor(n/2)个记录开始进行筛选堆，因为该记录是最后一个非叶结点记录
        sift(r,i,n);
    }
}
void HeapSort(RecordType r[],int n){//递增排序，先建大根树；递减排序，先建小根树。不管大根小根都只是某结点与左右子树结点的大小比较，左右结点不知道谁大谁小
    crt_heap(r,n);//先建立初始堆
    for(int i=n;i>=2;i--){
        RecordType b=r[1];//将堆顶与堆尾的记录进行交换
        r[1]=r[i];
        r[i]=b;
        sift(r,1,i-1);//换完后再进行重构堆
    }
}

//归并类排序：具有稳定性
void Merge(RecordType r[],int low,int mid,int high){//合并相邻的的两个有序子序列
    int i,j,k;
    RecordType *A=(RecordType*)malloc(sizeof(RecordType)*(high-low+1));//造一个辅助空间
    i=low;j=mid+1;k=0;
    while((i<=mid)&&(j<=high)){//合并两个子列
        if(r[i].key<=r[j].key){
            A[k]=r[i];
            i++;k++;
        }else{
            A[k]=r[j];
            j++;k++;
        }
    }
    while(i<=mid){//如果没有合并完则继续合并
        A[k]=r[i];
        k++;i++;
    }
    while(j<=high){
        A[k]=r[j];
        k++;j++;
    }
    for(i=low,k=0;i<=high;i++,k++) r[i]=A[k];//然后再把排列好的移到r中
    free(A);
}
void MergeSort(RecordType r[],int low,int high){
    int mid;
    if(low<high){
        mid=(low+high)/2;
        MergeSort(r,low,mid);//对两部分进行分割，然后一直分割，分到不能再分再进行归并
        MergeSort(r,mid+1,high);
        Merge(r,low,mid,high);
    }
}

// 分配类排序
// 链式基数排序：具有稳定性
#define RADIX 10
#define KEY_SIZE 3
#define LIST_SIZE 20
typedef struct{
    Keytype keys[KEY_SIZE];//子关键数组
    OtherType other_data;//其他数据项
    int next;//静态链域
}RecordTypex;
typedef struct{
    RecordTypex r[LIST_SIZE+1];
    int length;
    int keynum;
}SLinkList;
typedef int PVector[RADIX];

void Distribute(RecordTypex r[],int i,PVector f,PVector e){//进行分配，i是关键字第i位
    int j;
    for(j=0;j<RADIX;j++) f[j]=0;//初始化f分配集
    int p=r[0].next;//p指向第一个结点
    while(p!=0){
        j=r[p].keys[i];//找到j结点
        if(f[j]==0) f[j]=p;//f存第一位结点
        else r[e[j]].next=p;//改变next
        e[j]=p;//e存最后一个结点
        p=r[p].next;//往下进行
    }
}
void Collet(RecordTypex r[],PVector f,PVector e){//进行收集
    int j=0;
    while(f[j]==0) j++;//找到第一个含有结点数目不是0的一组
    r[0].next=f[j];//接上
    int t=e[j];//最后一位
    while(j<RADIX-1){
        j++;//先加
        while((j<RADIX-1)&&(f[j]==0)) j++;//找到下一个结点数不为0的一组
        if(f[j]!=0){
            r[t].next=f[j];//同上的操作
            t=e[j];
        }
    }
    r[t].next=0;//尾结点
}
void RadixSort(RecordTypex r[],int n,int d){//d是从关键字第d位开始
    for(int i=0;i<=n-1;i++) r[i].next=i+1;//初始化next位置
    r[n].next=0;
    PVector head,tail;
    for(int i=d-1;i>=0;i--){//从第i位开始，每次进行一波分配和收集
        Distribute(r,i,head,tail);
        Collet(r,head,tail);
    }
}

int main(){
    int t;
    int n=4;
    RecordType r[n+1];
    printf("1、插入类排序\n2、交换类排序\n3、选择类排序\n4、归并类排序\n5、分配类排序\n选择排序类别:");
    scanf("%d",&t);
    if(t!=5){
        printf("输入排序数据:");
        int k;
        for(int i=1;i<=n;i++){
            scanf("%d",&k);
            r[i].key=k;
        }
    }
    switch(t){
        case 1:{//插入类排序
            printf("1、直接插入排序\n2、折半插入排序\n3、希尔排序\n选择排序方式:");
            scanf("%d",&t);
            switch(t){
                case 1:{//直接插入排序
                    InsSort(r,n);break;
                }
                case 2:{//折半插入排序
                    BinSort(r,n);break;
                }
                case 3:{//希尔排序
                    int delta[n];
                    delta[0]=floor(n/2);
                    int i;
                    for(i=0;i>=0;i++){
                        if(delta[i]==1) {
                            i++;
                            break;
                        }
                        delta[i+1]=floor(delta[i]/2);
                    }
                    ShellSort(r,n,delta,i);
                    break;
                }
                default:printf("错误！");
            }
            printf("排序结果:");
            for(int i=1;i<=n;i++){
                printf("%d ",r[i].key);
            }
            break;
        }
        case 2:{//交换类排序
            printf("1、冒泡排序\n2、快速排序\n选择排序方式:");
            scanf("%d",&t);
            switch(t){
                case 1:{//冒泡排序
                    BubbleSort(r,n);
                    break;
                }
                case 2:{//快速排序
                    QKSort(r,1,n);
                    break;
                }
                default:printf("错误！");
            }
            printf("排序结果:");
            for(int i=1;i<=n;i++){
                printf("%d ",r[i].key);
            }
            break;
        }
        case 3:{//选择类排序
            printf("1、简单选择排序\n2、堆排序\n选择排序方式:");
            scanf("%d",&t);
            switch(t){
                case 1:{//简单选择排序
                    SelectSort(r,n);
                    break;
                }
                case 2:{//堆排序
                    HeapSort(r,n);
                    break;
                }
                default:printf("错误！");
            }
            printf("排序结果:");
            for(int i=1;i<=n;i++){
                printf("%d ",r[i].key);
            }
            break;
        }
        case 4:{//归并类排序
            MergeSort(r,1,n);
            printf("排序结果:");
            for(int i=1;i<=n;i++){
                printf("%d ",r[i].key);
            }
            break;
        }
        case 5:{//分配类排序
            printf("输入排序数据:");
            RecordTypex x[n+1];
            int k;
            for(int i=1;i<=n;i++){
                for(int j=0;j<KEY_SIZE;j++){
                    scanf("%1d",&k);
                    x[i].keys[j]=k;
                }
            }
            RadixSort(x,n,KEY_SIZE);
            printf("排序结果:");
            int i=0;
            while(x[i].next!=0){
                for(int j=0;j<KEY_SIZE;j++){
                    printf("%d",x[x[i].next].keys[j]);
                }
                printf(" ");
                i=x[i].next;
            }
            break;
        }
        default:printf("错误！");
    }
}







