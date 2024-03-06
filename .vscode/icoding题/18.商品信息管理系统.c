#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过
#define GOODS_FILE_NAME "goodsinfo.txt"

#define MAX_ID_LEN 30

#define MAX_NAME_LEN 30

#define MAX_PRICE_LEN 30

#define MAX_DISCOUNT_LEN 30
typedef struct {
char goods_id[MAX_ID_LEN];
char goods_name[MAX_NAME_LEN];
int goods_price;
char goods_discount[MAX_DISCOUNT_LEN];
int goods_amount;
int goods_remain;
} GoodsInfo;


typedef struct node
{
GoodsInfo data;
struct node *next;
} GoodsList;


 GoodsInfo read_goods_info();
 void init_list(GoodsList **pL);
 void destory_list(GoodsList **pL);
 void destory_list_and_file(GoodsList **pL);
 int save_to_file(GoodsList *L);
 void output_one_item(GoodsList *L);
 void output_all_items(GoodsList *L);
 bool insert_item(GoodsList *L, GoodsInfo item, int choice);
 bool delete_item(GoodsList *L, char* goods_id);
 GoodsList* search_item(GoodsList *L, char* goods_id);
 bool change_item(GoodsList *L, char* goods_id, GoodsInfo new_info);
 void bubble_sort(GoodsList *L);
 int read_line(char str[], int n);
//函数原型：void init_list(GoodsList **L)
//其中 *L 为指向链表头结点的指针，L为指向链表头结点指针的地址，init_list首先创建链表的头结点，之后读取goodsinfo.txt(示例文件下载)中的商品信息，并初始化链表，函数执行后，需确保 *L 为指向链表头结点的指针。
//init_list 实现商品信息链表的初始化，函数从已有的商品信息文件goodsinfo.txt(示例文件下载)中读入商品信息，并且分配内存保存至链表中。
//为了方便在表头插入和删除结点的操作，经常在表头结点（存储第一个元素的结点）的前面增加一个结点，称之为头结点或表头附加结点。这样原来的表头指针由指向第一个元素的结点改为指向头结点，头结点的数据域为空，头结点的指针域指向第一个元素的结点。
void init_list(GoodsList **L)
{
  CurrentCnt=0;
  (*L)=(GoodsList*)malloc(sizeof(GoodsList));
  if(*L==NULL)return;
  GoodsList *p;
  GoodsInfo data;
  p=*L;
  FILE *fp;
  if((fp=fopen(GOODS_FILE_NAME,"r"))==NULL)
  {
    printf("File could not be opened");
    return;
  }
  while(!feof(fp))
  {
    fscanf(fp,"%s",data.goods_id);
    fscanf(fp,"\t%s",data.goods_name);
    fscanf(fp,"\t%d",&data.goods_price);
    fscanf(fp,"\t%s",data.goods_discount);
    fscanf(fp,"\t%d",&data.goods_amount);
    fscanf(fp,"\t%d\n",&data.goods_remain);
    GoodsList *pnew=(GoodsList*)malloc(sizeof(GoodsList));
    if(pnew==NULL) continue;
    pnew->data=data;
    p->next=pnew;
    p=p->next;
    CurrentCnt++;
  }
  p->next=NULL;
  fclose(fp);
}
//函数原型：bool insert_item(GoodsList *L, GoodsInfo goodsInfo, int choice)，
//L为指向链表头结点的指针，函数根据choise的值，将goodsInfo插入到链表的指定位置，如果成功插入，函数返回true，如果未插入，函数返回false。
//分别实现头插法、尾插法，中间位置插入三种:
//用户输入0，将商品信息插入到链表尾部；
//用户输入1，将商品信息插入到链表头部；
//用户输入其它正整数i，将商品信息插入到链表中间第i号位置, 例如：输入3，应该在第二个节点后插入新节点
bool insert_item(GoodsList *L, GoodsInfo goodsInfo, int choice)
{
  int i;
  GoodsList *p=L,*tmp,*tp=(GoodsList*)malloc(sizeof(GoodsList));
  tp->data=goodsInfo;
  tp->next=NULL;
  switch(choice)
  {
    case 1:tmp=p->next;p->next=tp;tp->next=tmp;CurrentCnt++;return true;
    case 0:
           for(;p->next!=NULL;p=p->next);
           p->next=tp;CurrentCnt++;return true;
    default:
    if(choice<0||choice>CurrentCnt+1) return false;
    for(i=1;i<choice;i++)
    {
       p=p->next;
    }
    tmp=p->next;p->next=tp;tp->next=tmp;CurrentCnt++;return true;
  }
  return false;
}
//函数原型：bool delete_item(GoodsList *L, char* goods_id)
//其中L为指向链表头结点的指针，goods_id为要删除商品的ID；
//如果成功删除，函数返回true，否则返回false。
//delete_item 根据商品的ID来删除对应的商品信息，商品查找通过字符串比较的方式，查找到后释放对应指针指向的内存区域，完成删除。
bool delete_item(GoodsList *L, char* goods_id)
{
   GoodsList *p=L,*tmp,*tp=p->next;
   if(tp==NULL) return false;
   for(;strcmp(tp->data.goods_id,goods_id)!=0;)
   {
    p=p->next;
    tp=tp->next;
    if(tp==NULL) return false;
   }
   tmp=tp->next;
   p->next=tmp;
   free(tp);
   tp=NULL;
   CurrentCnt--;
   return true;
}
//函数原型：GoodsList* search_item(GoodsList *L, char* goods_id)
//其中L为指向链表头结点的指针，goods_id为要查找商品的ID；
//如果找到该商品，函数返回该商品对应的结点指针，否则返回 NULL.
//根据输入的商品 ID 来查找对应的商品信息，商品 ID 的判断用字符串比较的方式来实现，然后调用格式化显示查找到的商品信息.
GoodsList* search_item(GoodsList *L, char* goods_id)
{
  GoodsList *p=L,*tp=p->next;
  if(tp==NULL) return NULL;
  for(;strcmp(tp->data.goods_id,goods_id)!=0;)
  {
    if((tp->next)==NULL) return NULL;
    else tp=tp->next;
  }
  return tp;
}
//函数原型：bool change_item(GoodsList *L, char* goods_id, GoodsInfo new_info)
//其中 L 为指向链表头结点的指针，goods_id 为要修改的商品 ID，new_info 为该商品的最新数据。函数成功修改后返回true，否则返回 false。
bool change_item(GoodsList *L, char* goods_id, GoodsInfo new_info)
{
  GoodsList *p=L,*tp=p->next;
  if((tp==NULL)) return false;
  while(strcmp(tp->data.goods_id,goods_id)!=0)
  {
    if((tp->next)==NULL) return false;
    tp=tp->next;
  }
  tp->data=new_info;
  return true;
}
//函数原型：void output_one_item(GoodsList *p)，函数显示结点为 p 的商品信息。
void output_one_item(GoodsList *p)
{
  printf("%s\t%s\t%d\t%s\t%d\t%d\n",p->data.goods_id,p->data.goods_name,p->data.goods_price,p->data.goods_discount,p->data.goods_amount,p->data.goods_remain);
}
//函数原型：void output_all_items(GoodsList *L)，
//L为指针链表头结点的指针，output_all_items 调用 output_one_item 函数，将链表中所有的商品信息以格式化的方式打印输出到屏幕上。
void output_all_items(GoodsList *L)
{
  if(L->next==NULL) return;
  GoodsList *tp=L->next;
  for(;;)
  {
    output_one_item(tp);
    if((tp->next)==NULL) return;
    tp=tp->next;
  }
}
//函数原型：void destory_list(GoodsList **L)，
//该函数释放包括头结点在内的所有结点，完成后指向链表头结点的指针为NULL。
void destory_list(GoodsList **L)
{
  GoodsList *p=*L,*p1=p->next;
  for(;p1!=NULL;)
  {
    free(p);
    p=p1;
    p1=p1->next;
  }
  free(p);
  *L=NULL;
  CurrentCnt=0;
  return;
}
//函数原型：void destory_list_and_file(GoodsList **L)，
//该函数调用destory_list释放包括头结点在内的所有结点，将指向链表头结点的指针为NULL，最后删除存储商品信息的文件goodinfo.txt。
void destory_list_and_file(GoodsList **L)
{
  void destory_list(L);
}
//函数原型：int save_to_file(GoodsList *L)
//将当前链表所有的商品信息保存到文件 goodsinfo.txt 中，其中L为指向链表头结点的指针，保存成功后，该函数返回商品的数量。
int save_to_file(GoodsList *L)
{
   FILE *fp;
  if((fp=fopen(GOODS_FILE_NAME,"w"))==NULL)
  {
    printf("File could not be opened");
    return;
  }
  if((L->next)==NULL) return;
  GoodsList *p=L->next;
  for(;;)
  {
    fprintf(fp,"%s\t%s\t%d\t%s\t%d\t%d\n",p->data.goods_id,p->data.goods_name,p->data.goods_price,p->data.goods_discount,p->data.goods_amount,p->data.goods_remain);
    if((p->next)==NULL) return CurrentCnt;
    p=p->next;
  }
}
//函数原型：void bubble_sort(GoodsList *L)
//L为指向链表头结点的指针，该函数利用冒泡排序算法，按价格从低到高对商品进行排序。
void bubble_sort(GoodsList *L)
{
  if(CurrentCnt<=1) return;
  int j;
  for(j=1;j<CurrentCnt;j++)
  {
     GoodsList *p=L;
     for(;;)
     {
      GoodsList *p1=p->next,*p2=p->next->next,*tp=p2->next;
      if(p1->data.goods_price>p2->data.goods_price)
      {
        p->next=p2;
        p2->next=p1;
        p1->next=tp;
      }
      if(p->next->next->next==NULL) break;
      else p=p->next;
     }
  }
}
//函数原型：GoodsInfo read_goods_info()
//该函数调用read_line及scanf等函数，按“商品ID、商品名称、商品价格、商品折扣、商品数量、商品剩余数量”的顺序让用户输入，并将这些信息保存到 GoodsInfo 结构体中，函数最后返回该结构体。
GoodsInfo read_goods_info()
{
  GoodsInfo new_data;
  read_line(new_data.goods_id,MAX_ID_LEN);
  read_line(new_data.goods_name,MAX_NAME_LEN);
  scanf("%d",&new_data.goods_price);
  read_line(new_data.goods_discount,MAX_DISCOUNT_LEN);
  scanf("%d",&new_data.goods_amount);
  scanf("%d",&new_data.goods_remain);
  return new_data;
}
int main()
{
    int n,choice;
    GoodsList *L;
    GoodsInfo new_info,item;
    char goods_id[MAX_ID_LEN];
    init_list(&L);
    for(;;)
    {
         printf("1.显示所有商品的信息\n");
        printf("2.修改某个商品的信息\n");
        printf("3.插入某个商品的信息\n");
        printf("4.删除某个商品的信息\n");
        printf("5.查找某个商品的信息\n");
        printf("6.商品存盘并退出系统\n");
        printf("7.对商品价格进行排序\n");
        printf("8.(慎用)删除所有内容\n");
        printf("其他.不存盘并退出系统\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:output_all_items(L);break;
            case 2:printf("请输入你要修改的商品ID和信息:\n");
                   read_line(goods_id,MAX_ID_LEN);
                   new_info=read_goods_info();
                   if(change_item(L, goods_id, new_info)==true)
                   printf("修改成功");
                   else printf("修改失败");break;
            case 3:printf("请输入你要插入的信息:");
                   item=read_goods_info();
                   printf("请输入你要插入的位置:");
                   printf("提示:0:头插\n1:尾插\n其他:其他\n");
                   scanf("%d",&choice);
                   if(insert_item(L,item,choice)==true)
                       printf("插入成功");
                   else printf("插入失败");break;
            case 4:printf("请输入你要删除的商品ID:");
                   read_line(goods_id,MAX_ID_LEN);
                   if(delete_item(L,goods_id)==true)
                       printf("删除成功");
                   else printf("删除失败");break;
            case 5:printf("请输入你要查找的商品ID:");
                   read_line(goods_id,MAX_ID_LEN);
                   if((search_item(L,goods_id))!=NULL)
                    printf("查找成功");
                   else printf("查找失败");break;
            case 6:save_to_file(L);return 0;break;
            case 7:bubble_sort(L);break;
            case 8:destory_list_and_file(&L);break;
            default: destory_list(&L);return 0;break;
        }
    }
    return 0;
}