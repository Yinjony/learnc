#include <stdio.h>
#include <stdlib.h>
int win_or_lost(int sum)
{
    switch(sum)
    {
        case 7:
        case 11:return 1;
        case 2:
        case 3:
        case 12:return 0;
        default:puts("You need to keep rolling the dice to win!");
        if(try_again(sum)) return 1;
        else return 0;
    }
}
int try_again(int sum)
{
    for(;;)
        {
            int sum_again;
            char choose[4];
            puts("Hei,gambler,again?(yes/no):");
            scanf("%s",choose);
            if(strcmp("yes",choose)==0)
            {
                int bet_a,bet_b;
                srand(time(NULL));
                bet_a=(rand()%6)+1,bet_b=(rand()%6)+1;
                sum_again=bet_a+bet_b;
                printf("Your outcome is:%d %d\nYour sum is:%d\n",bet_a,bet_b,sum_again);
                if(sum_again==sum) return 1;
                if(sum_again==7) return 0;
            }
            else return 0; 
        }
}
int main ()
{
    int bet_a,bet_b,sum;
    char count[4];
    srand(time(NULL));
    bet_a=(rand()%6)+1,bet_b=(rand()%6)+1;
    sum=bet_a+bet_b;
    puts("The rule:If the sum is 7 or 11,you will win.\nIf it is 2,3 or 12,you will lost.\nIf it is others,you need try again.\nIf the sum is the same as before,you will win.\nIf it is 7,you will lost.\nOf course,you can try it again forever utill you win or lost.");
    puts("Do you want to play Craps?(yes/no):");
    scanf("%s",count);
    if(strcmp(count,"yes")==0)
      {
        printf("Your outcome is:%d %d\nYour sum is :%d\n",bet_a,bet_b,sum);
        if(win_or_lost(sum)) puts(" You Win!");
        else puts("You Lost.");
      }
    else puts("OK,you don't want.");
    return 0;
}