#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SUITS 4
#define FACES 13
#define CARDS 52
void shuffle(int deck[][FACES])
{
   int i,j;
   int card=1;
   srand(time(NULL));
   for(;card<=CARDS;card++){
      do{
         i=rand()%SUITS;
         j=rand()%FACES;
      }while(deck[i][j]!=0);
      deck[i][j]=card;
   }
}
void printf_cards(char *suit[],char *face[],int deck[][FACES])
{
   for(int card=1;card<=CARDS;card++){
      for(int i=0;i<SUITS;i++){
         for(int j=0;j<FACES;j++){
            if(deck[i][j]==card){
               printf("%5s of %-8s%c",face[j],suit[i],card%2==0?'\n':'\t');
            }
         }
      }
   }
}
int main()
{
   char *suit[SUITS]={"Hearts","Diamonds","Clubs","Spades"};
   char *face[FACES]={"Ace","Deuce","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
   int deck[SUITS][FACES]={0};
   shuffle(deck);
   printf_cards(suit,face,deck);
   return 0;
}
