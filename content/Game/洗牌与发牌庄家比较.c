#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SUITS 4
#define FACES 13
#define CARDS 52
struct duizi{
    int quantity;
    int gard;
}target;
struct duizi duizi_(int dface[5])//判断有几个对子并计算分数
{
    int m=0;
    int num[2]={0};
    struct duizi target;
    for(int i=0;i<4;i++){
        for(int j=i+1;j<5;j++){
            if(dface[i]==dface[j]){
                for(int k=j+1;k<5;k++){
                    if(dface[k]==dface[i]){
                        target.gard=0;
                        target.quantity=0;
                        return target;
                    }
                }
                num[m++]=dface[i];
            }
        }
    }
    target.gard=num[0]*2+num[1]*2;
    target.quantity=m;
    return target;
}
int three_card(int dface[5])//判断是否有三张相同的牌并计算分数
{
    for(int i=0;i<3;i++){
        for(int j=i+1;j<4;j++){
            if(dface[j]==dface[i]){
                for(int k=j+1;k<5;k++){
                    if(dface[k]==dface[i]){
                        for(int m=k+1;m<5;m++){
                            if(dface[m]==dface[i]){
                                return 0;
                            }
                        }
                        return dface[i]*3;
                    }
                }
            }
        }
    }
    return 0;
}
int four_card(int dface[5])//判断是否有相同的四张牌并计算分数
{
    //一层一层的去判断检查是否有x张相同的牌。
    for(int i=0;i<2;i++){
        for(int j=i+1;j<3;j++){
            if(dface[i]==dface[j]){
                for(int k=j+1;k<4;k++){
                    if(dface[k]==dface[i]){
                        for(int l=k+1;l<5;l++){
                            if(dface[l]==dface[i]){
                                return dface[i]*4;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
int tonghua(int dsuit[5])//判断是否有同花
{
    for(int i=0;i<4;i++){
        if(dsuit[i]!=dsuit[i+1]){
            return 0;
        }
    }
    return 3;
}
int shunzi(int dface[5])//判断是否有顺子
{
    int order[5],num;
    for(int i=0;i<5;i++){
        order[i]=dface[i];
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4-i;j++){
            if(order[j]>order[j+1]){
                int t;
                t=order[j];
                order[j]=order[j+1];
                order[j+1]=t;
            }
        }
    }
    for(int i=0;i<4;i++){
        if((order[i]+1)!=order[i+1]){
            return 0;
        }
        num+=order[i];
    }
    num+=order[4];
    return num;
}
/*void panduanpai(int dface[5],int dsuit[5])//对牌型进行判断并打印分析结果
{
    target=duizi_(dface);
    puts("\n结果分析：");
    if(target.quantity==1){
        puts("包含一个对子。");
    }
    else {
        puts("不包含一个对子。");
    }
    if(target.quantity==2){
        puts("包含俩个对子。");
    }
    else {
        puts("不包含俩个对子。");
    }
    if(three_card(dface)){
        puts("包含三张同级的牌。");
    }
    else {
        puts("不包含三张同级的牌。");
    }
    if(four_card(dface)){
        puts("包含四张同级的牌。");
    }
    else {
        puts("不包含四张同级的牌。");
    }
    if(tonghua(dsuit)){
        puts("是同花。");
    }
    else {
        puts("不是同花。");
    }
    if(shunzi(dface)){
        puts("是顺子。");
    }
    else {
        puts("不是顺子。");
    }
}*/
int bijiao(int dface1[5],int dsuit1[5],int dface2[5],int dsuit2[5])//将庄家的牌和玩家的牌进行比较
{
    int sum1=0,sum2=0;
    int duizi1=duizi_(dface1).gard,duizi2=duizi_(dface2).gard;
    sum1=duizi1+three_card(dface1)+four_card(dface1)+tonghua(dsuit1)+shunzi(dface1);
    sum2=duizi2+three_card(dface2)+four_card(dface2)+tonghua(dsuit2)+shunzi(dface2);
    if(sum1>sum2){
        return 1;
    }
    else if(sum1<sum2){
        return -1;
    }
    else {
        return 0;
    }
}
void anxiangcaozuo(int dface[5],int dsuit[5],int mp,char *suit[],char *face[],int deck[][FACES])//庄家摸牌换牌
{
    int newdface[5],newdsuit[5];
    int card=11;
    switch(mp){
        case 0:puts("庄家不摸了。");return;
        case 1:puts("庄家摸了一张牌。");break;
        case 2:puts("庄家摸了两张牌。");break;
        case 3:puts("庄家摸了三张牌。");break;
        case 5:puts("庄家摸了五张牌。");break;
    }
    for(int i=0;i<5;i++){
        int num=0;
        for(int j=0;j<5;j++){
            if(dface[j]==dface[i]){
                num++;
            }
        }//如果有相同的牌num便加一，一手牌一张单牌顶多重复一次。
        if(num==1){
            for(int ii=0;ii<SUITS;ii++){
                for(int jj=0;jj<FACES;jj++){
                    if(deck[ii][jj]==card){
                        newdface[i]=jj+1;
                        newdsuit[i]=ii;
                    }//不用dface是因为那是一边改一边找有的牌可能不会被换，但我们想要的是全扔全换。
                }
            }
            card++;
        }
    }
    for(int i=0;i<5;i++){
        dface[i]=newdface[i];
        dsuit[i]=newdsuit[i];
    }//换牌。
    /*for(int t=0;t<5;t++){
        printf("%5s of %-8s",face[dface[t]-1],suit[dsuit[t]]);
        if(t!=4){
            printf("%c",'\t');
        }
        else printf("%c",'\n');
    }*///打印换牌之后的牌型。
}
int zhuangjiajueze(int dface1[5],int dsuit1[5],int dface2[5],int dsuit2[5])//庄家判断牌的好坏
{
    int mp=0;
    int duizi=duizi_(dface1).quantity;
    if(bijiao(dface1,dsuit1,dface2,dsuit2)<=0){
        puts("狡猾的庄家选择摸一次牌。");
        if(shunzi(dface1)){
            return 0;
        }
            else if(four_card(dface1)){
                return 1;
            }
                    else if(three_card(dface1)){
                        if(duizi==1){
                            return 0;
                        }
                        else {
                            return 2;
                        }
                    }
                            else if(duizi==2){
                                return 1;
                            }
                                    else if(duizi==1){
                                        return 3;
                                    }
                                            else {
                                                return 5;
                                            } 
    }
    else {
        puts("好像什么也没有发生");
    }
}
void printfbijiao(int dface1[5],int dsuit1[5],int dface2[5],int dsuit2[5])//打印最终的比较结果
{
    printf("比较结果：");
    if(bijiao(dface1,dsuit1,dface2,dsuit2)>0){
        puts("庄家的牌好。");
    }
    else if(bijiao(dface1,dsuit1,dface2,dsuit2)<0){
        puts("玩家的牌好。");
    }
    else {
        puts("同等实力。");
    }
}

void shuffle(int deck[][FACES])//洗牌
{
    int card=1;
    for(int i=0;i<SUITS;i++){
        for(int j=0;j<FACES;j++){
            deck[i][j]=card++;
        }
    }
    int i1=0,j1=0,i2=0,j2=0,t;
    srand(time(NULL));
    for(;i1<SUITS;i1++){
        for(;j1<FACES;j1++){
        i2=rand()%SUITS;
        j2=rand()%FACES;
        t=deck[i1][j1];
        deck[i1][j1]=deck[i2][j2];
        deck[i2][j2]=t;
    }
   }
}
void printf_cards(char *suit[],char *face[],int deck[][FACES],int dface1[5],int dsuit1[5],int dface2[5],int dsuit2[5])//发牌并打印牌
{
    int mp;
    for(int card=1;card<=CARDS;card++){
      for(int i=0;i<SUITS;i++){
         for(int j=0;j<FACES;j++){
            if(deck[i][j]==card){
               printf("%5s of %-8s%c",face[j],suit[i],card%2==0?'\n':'\t');
            }
         }
      }
    }//打印所有的牌型用于检验是不是按着顺序进行的。
    puts("庄家：");
    for(int card=1;card<=5;card++){
      for(int i=0;i<SUITS;i++){
         for(int j=0;j<FACES;j++){
            if(deck[i][j]==card){
                dface1[card-1]=j+1;
                dsuit1[card-1]=i;
                printf("未知%c",card!=5?'\t':'\n');
                //printf("%5s of %-8s%c",face[j],suit[i],card!=5?'\t':'\n');//用于打印庄家最初的手牌与之后的改变形成比较。
            }
         }
       } 
    }
    //panduanpai(dface1,dsuit1);
    puts("玩家：");
    for(int card=6;card<=10;card++){
      for(int i=0;i<SUITS;i++){
         for(int j=0;j<FACES;j++){
            if(deck[i][j]==card){
                dface2[card-6]=j+1;
                dsuit2[card-6]=i;
                printf("%5s of %-8s%c",face[j],suit[i],card!=10?'\t':'\n');
            }
         }
       } 
    }
    //panduanpai(dface2,dsuit2);
    mp=zhuangjiajueze(dface1,dsuit1,dface2,dsuit2);
    anxiangcaozuo(dface1,dsuit1,mp,suit,face,deck);
    printfbijiao(dface1,dsuit1,dface2,dsuit2);
}

int main()
{
    int dface1[5],dface2[5];
    int dsuit1[5],dsuit2[5];
    char *suit[SUITS]={"Hearts","Diamonds","Clubs","Spades"};
    char *face[FACES]={"Ace","Deuce","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
    int deck[SUITS][FACES]={0};
    shuffle(deck);//可以多次调用直至洗出满意的牌。
    printf_cards(suit,face,deck,dface1,dsuit1,dface2,dsuit2);
    return 0;
}
