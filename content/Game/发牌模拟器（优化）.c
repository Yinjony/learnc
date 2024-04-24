#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CARDS 52
#define FACES 13
struct card {
     char *face;
     char *suit;
};
typedef struct card Card;

void fillDeck(Card *wDeck,char *wFace[],char *wSuit[])
{
    for(int i=0;i<CARDS;i++){
        wDeck[i].face=wFace[i%FACES];
        wDeck[i].suit=wSuit[i/FACES];
    }
}

void shuffle(Card *wDeck)
{
    for(int i=0;i<CARDS;i++){
        int j=rand()%CARDS;
        Card temp=wDeck[i];
        wDeck[i]=wDeck[j];
        wDeck[j]= temp;
    }
}

void deal(Card *wDeck)
{
    for(int i=0;i<CARDS;i++){
        printf("%5s of %-8s",wDeck[i].face,wDeck[i].suit);
        if((i+1)%4){
         printf(" ");
        }
        else printf("\n");
    }
}
int main()
{
    Card deck[CARDS];
    char *face[]={"Ace","Deuce","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
    char *suit[]={"Hearts","Diamonds","Clubs","Spades"};
    srand(time(NULL));
    fillDeck(deck,face,suit);
    shuffle(deck);
    deal(deck);
    return 0;
}