#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 50
typedef struct 
{
    char data[SIZE];
    int top;
}Stack;

void Init(Stack *S){
    S->top=-1;
}
bool Push(Stack *S,char x){
    if(S->top==SIZE-1){
        return false;
    }
    S->top++;
    S->data[S->top]=x;
    return true;
}
bool Pop(Stack *S,char *x){
    if (S->top==-1){
        return false;
    }
    else {
        *x=S->data[S->top];
        S->top--;
        return true;
    }
}
bool GetTop(Stack *S,char *x){
    if(S->top==-1){
        return false;
    }
    else {
        *x=S->data[S->top];
        return true;
    }
}
void ClearStack(Stack *S){
    S->top=-1;
}
bool Match(char a,char b){
    if(b=='('){
        if(a==')'){
            return true;
        }
        else {
            return false;
        }
    }
    if(b=='['){
        if(a==']'){
            return true;
        }
        else {
            return false;
        }
    }
    if(b=='{'){
        if(a=='}'){
            return true;
        }
        else {
            return false;
        }
    }
}

void BracketMatch(char *str){
    Stack S;int i;char ch;
    Init(&S);
    for(i=0;str[i]!='\0';i++){
        switch(str[i]){
        case '(':
        case '[':
        case '{':
            Push(&S,str[i]);
            break;
        case ')':
        case ']':
        case '}':
            if(S.top==-1){
                printf("\n 右括号多余！");
                return;
            }
            else {
                GetTop(&S,&ch);
                if(Match(ch,str[i])){
                    Pop(&S,&ch);
                }
                else{
                    printf("\n对应的左右括号不同类！");
                    return ;
                }
            }
        }
    }
    if(S.top==-1){
        printf("\n括号匹配！");
    }
    else{
        printf("\n左括号多余！");
    }
}

int main(){
    printf("输入长度:");
    int d;
    scanf("%d",&d);
    printf("输入字符:");
    char chars[d];
    scanf("%s",chars);
    BracketMatch(chars);
}