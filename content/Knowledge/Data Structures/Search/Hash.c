#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define m 50
#define NULLKEY 32768
typedef int KeyType;
typedef struct node{
    KeyType key;
    struct node *next;
}Node;
typedef struct{
    KeyType key;
    //其他值，例如
    // char name;等等
    Node *data; 
}RecordType;
typedef RecordType HashTable[m];

//哈希地址算法
/*1、数字分析法：已知关键字集合并且所有关键字位数都比哈希表长度要长，例如一组数据中第四位和
第七位的取值十分均匀，则81346532,81301367地址可分别取为43,06*/
/*2、平方取中法：一般用于英文字母关键字，例如Y编码为25，E编码为05，K编码为11，A编码为01
则KEYA编码为11052501，平方后122157778255001，取中间值得到778作为地址*/
/*3、分段叠加法：对位数十分长的数据，按照哈希表的长度（例如1000，则三位一段），从头开始分割关键字，
舍去小于这个这个位数的分割段，将分割后的每一段进行相加（可以移位叠加即低位与低位对齐，
也可以折叠叠加即来回折叠），例如12360324711202065，移位叠加后123+603+...得1105，哈希地址为105，
折叠叠加后123+306+...得907，哈希地址,907*/
/*4、除留余数法：设哈希表长m，p为小于m的最大素数，则H(k)=k%p，得到哈希地址*/
int sushu(int x){
    for(int i=x;i>0&&i<=x;i--){
        int j=2;
        while(j<i){
            if(i%j==0) break;
            j++;
        }
        if(j>=i) return i;
    } 
}
int p; 
int hash(KeyType key){
    return key%p;
}
/*5、伪随机数法：用random函数*/

//创建哈希表,解决冲突方法
/*1、开放定址法*/
void CreateHash(HashTable ht){
    for(int i=0;i<m;i++) ht[i].key=NULLKEY;//初始化
    printf("输入一组数值：");
    int key,h;
    scanf("%d",&key);
    while(key!=NULLKEY){
        h=hash(key);
        if(ht[h].key!=NULLKEY){//有冲突
            //1、线性探测再散列1,2,3...m-1
            for(int i=0;i<m-1;i++){
                int hi=(h+i)%m;
                if(ht[hi].key==NULLKEY){
                    ht[h].key=key;
                    break;
                }
            }
            //2、二次探测再散列1²,-1²,2²,-2²...k²（k<=m/2）
            /*for(int i=0;i<=m/2;i++){
                int is=pow(i,2);
                int hi;
                hi==(h+is)%m;
                if(ht[hi]->key==NULLKEY){
                    ht[h]->key=key;
                    break;
                }
                hi=(h-is)%m;
                if(ht[hi]->key==NULLKEY){
                    ht[h]->key=key;
                    break;
                }
            }*/
            //3、伪随机探测再散列：使用random函数
        }else ht[h].key=key;
        scanf("%d",&key);
    }
}
/*2、再哈希法：同时构造多个不同的哈希函数，然后冲突时用另一个哈希函数*/
/*3、链地址法*/

// void CreateHash(HashTable ht){
//     for(int i=0;i<m;i++)ht[i].data=NULL;
//     printf("输入一组数值：");
//     int key,h;
//     scanf("%d",&key);
//     while(key!=NULLKEY){
//         h=hash(key);
//         if(ht[h].data!=NULL){
//             Node *p=(Node*)malloc(sizeof(Node));
//             Node *q;
//             p->key=key;
//             p->next=NULL;
//             for(q=ht[h].data;q->next!=NULL;q=q->next);
//             q->next=p;
//         }else{
//             ht[h].data=(Node*)malloc(sizeof(Node));
//             ht[h].data->key=key;
//         }
//         scanf("%d",&key);
//     }
// }
/*4、建立公共溢出区法：将哈希表分为基本表和溢出表，与基本表发生冲突的一律填入溢出表*/

//哈希表的查找算法
int HashSearch(HashTable ht,KeyType key){
    int h0=hash(key);//通过哈希算法找到地址
    if(ht[h0].key==NULLKEY) return -1;
    else if(ht[h0].key=key) return h0;
    else{//如果有同义词
        for(int i=0;i<=m-1;i++){//使用线性探测再散列解决冲突
            int hi=(h0+i)%m;
            if(ht[hi].key==NULLKEY) return -1;
            else if(ht[hi].key==key) return hi;
        }
        return -1;
    }
}

/*哈希表的性能分析，装填因子α=哈希表中的元素个数/哈希表的长度，asls查找成功平均长度，asluns查找失败平均长度
线性探测再散列：asls=1/2(1+1/(1-α)),asluns=1/2(1+1/(1-α)²)
伪随机，二次探测，再哈希法：asls=-1/α㏑(1-α),asluns=1/(1-α)
链地址法：asls=1+α/2,asluns=α+e的-α次方
*/

//哈希表中有26个关键字1~26
void printword(HashTable ht){//打印所有关键字
    printf("\n打印所有关键字");
    int i,j;
    for(i=1;i<=26;i++){
        j=i;
        while(ht[j].key!=NULLKEY){
            if(hash(ht[j].key)==i) {
                printf("%d\n",ht[j].key);//序号相同就打印
                break;
            }
            j=(j+1)%m;//再探测序列
        }
    }
}
float unsuncclength(HashTable ht){//模拟手工计算，等概率情况下哈希表不成功的平均查找长度算法
    int i,j;
    int count;
    int asl=0;
    float unasl;
    for(i=0;i<=26;i++){
        j=i;
        count=1;
        while(ht[j].key!=NULLKEY){
            count++;
            j=(j+1)%m;
        }
        asl=asl+count;//计算不成功查找长度总和
    }
    unasl=(float)asl/26;//求得平均
    return unasl;
}

int main(){
    HashTable ht;
    p=sushu(m);
    CreateHash(ht);
    printf("地址：%d",HashSearch(ht,25));
    printword(ht);
    printf("查找不成功平均长度:%f",unsuncclength(ht));
}