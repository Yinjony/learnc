#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define SIZE 50
typedef struct 
{
    char datac[SIZE];
    int datai[SIZE];
    int top;
}Stack;

void Init(Stack *S){
    S->top=-1;
}
bool Pushc(Stack *S,char x){
    if(S->top==SIZE-1){
        printf("栈已满。");
        return false;
    }
    S->top++;
    S->datac[S->top]=x;
    return true;
}
bool Pushi(Stack *S,int x){
    if(S->top==SIZE-1){
        printf("栈已满。");
        return false;
    }
    S->top++;
    S->datai[S->top]=x;
    return true;
}
void Popc(Stack *S,char *x){
    if(S->top==-1){
        printf("栈为空。");
        return;
    }
    else {
        *x=S->datac[S->top];
        S->top--;
        return;
    }
}
void Popi(Stack *S,int *x){
    if(S->top==-1){
        printf("栈为空。");
        return;
    }
    else {
        *x=S->datai[S->top];
        S->top--;
        return;
    }
}
char GetTop(Stack S){
    if(S.top==-1){
        printf("栈为空。");
        return '0';
    }
    char x;
    x=S.datac[S.top];
    return x;
}
bool In(char x,char *OPSet){
    for(int i=0;OPSet[i]!='\0';i++){
        if(OPSet[i]==x){
            return false;
        }
    }
    return true;
}
int GetNum(char x){
    switch(x){
        case '0':
            return 0;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break;
        case '3':
            return 3;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 5;
            break;
        case '6':
            return 6;
            break;
        case '7':
            return 7;
            break;
        case '8':
            return 8;
            break;
        case '9':
            return 9;
            break;
        default:
            printf("输入错误。");
    }
}
char Compare(char a,char b){
    char k[2];
    k[0]=a;
    k[1]=b;
    int n[2];
    for(int i=0;i<2;i++){
        switch(k[i]){
            case '#':
                n[i]=0;
                break;
            case '-':
            case '+':
                n[i]=1;
                break;
            case '*':
            case '/':
                n[i]=2;
                break;
            case '^':
                n[i]=3;
                break;               
        }
    }
    if(n[0]>n[1]){
        return '>';
    }
    else if(n[0]==n[1]){
        return '=';
    }
    else {
        return '<';
    }
    
}
int Execute(int a,char op,int b){
    switch(op){
        case '-':
            return a-b;
            break;
        case '+':
            return a+b;
            break;
        case '*':
            return a*b;
            break;
        case '/':
            return a/b;
            break;
        case '^':
            return pow(a,b);
    }
}
int ExpEvaluation(){
    Stack OPTR;
    Stack OVS;
    char ch;
    char OPSet[6];
    OPSet[0]='+';OPSet[1]='-';OPSet[2]='*';OPSet[3]='/';OPSet[4]='^';OPSet[5]='\0';
    int n;
    int v;
    Init(&OPTR);
    Init(&OVS);
    Pushc(&OPTR,'#');
    ch=getchar();
    while(ch!='#'||GetTop(OPTR)!='#'){
        if(!In(ch,OPSet)){
            n=GetNum(ch);
            Pushi(&OVS,n);
            ch=getchar();
        }
        else{
            switch(Compare(ch,GetTop(OPTR))){
                case '>':
                    Pushc(&OPTR,ch);
                    ch=getchar();
                    break;
                case '=':
                case '<':
                    char op;
                    int a,b;
                    Popc(&OPTR,&op);
                    Popi(&OVS,&b);
                    Popi(&OVS,&a);
                    v=Execute(a,op,b);
                    Pushi(&OVS,v);
                    break;
            }
        }
    }
    v=GetTop(OVS);
    return v;
}

int main(){
    printf("输入：\n输出：%d",ExpEvaluation());
}