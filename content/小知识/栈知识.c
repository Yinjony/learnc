//栈分为（1）初始化栈（2）压栈（3）出栈（4）获取栈顶元素（5）判断栈是否上溢或下溢
//实际上出栈的时候就可以取用栈顶元素
#include <stdio.h>
#define STACK_SIZE 100
int top=0;
int Stack[STACK_SIZE];
int is_full(void)
{
    if(top==STACK_SIZE) return 1;
    else return 0;
}
int is_empty(void)
{
    if(top==0) return 1;
    else return 0;
}
void make_empty(void)
{
    top=0;
}
void push(int num)
{
    if(is_full()) {
        printf("栈满");
        return;
    }
    else Stack[top++]=num;
}
int pop(void)
{
    if(is_empty()){
        printf("栈空");
        return;
    }
    else return Stack[top--];
}
int main()
{
    return 0;
}