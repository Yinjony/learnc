#include <stdio.h>
#define SIZE 50
typedef struct 
{
    char data[SIZE];
    int top;
}Stack;

void Init(Stack *S){
    S->top=-1;
}
int Push(Stack *S,char x){
    if(S->top==SIZE-1){
        return 0;
    }
    S->top++;
    S->data[S->top]=x;
    return 1;
}
int Pop(Stack *S,char *x){
    if (S->top==-1){
        return 0;
    }
    else {
        *x=S->data[S->top];
        S->top--;
        return 1;
    }
}
int GetTop(Stack *S,char *x){
    if(S->top==-1){
        return 0;
    }
    else {
        *x=S->data[S->top];
        return 1;
    }
}
void ClearStack(Stack *S){
    S->top=-1;
}
int Match(char a,char b){
    if(b=='('){
        if(a==')'){
            return 1;
        }
        else {
            return 0;
        }
    }
    if(b=='['){
        if(a==']'){
            return 1;
        }
        else {
            return 0;
        }
    }
    if(b=='{'){
        if(a=='}'){
            return 1;
        }
        else {
            return 0;
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