/*块链串，字符ch部分储存字符，但可以是任意数量的字符，也就是把一个串切成几个块储存，
用链表串起来，BLOCK_SIZE大小为1的时候，存储密度很低，但要是大于1，就大了*/

//操作方法与链表相同


#define BLOCK_SIZE 4

typedef struct Block{
    char ch[BLOCK_SIZE];
    struct Block *next;
} Block;

typedef struct BLString{
    Block *head;
    Block *tail;
    int len;
}BLString;
