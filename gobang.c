#include <stdio.h>
#include <stdlib.h>
#define N 15
#define CHESSBOARD_LIM (i >= 1 && i <= N && j >= 1 && j <= N)

int chessboard[N + 1][N + 1] = { 0 };

int whoseTurn = 0;

void initGame(void);
void printChessboard(void);
void playChess(void);
int judge(int, int);

int main(void)
{
    initGame();
    
    while (1)
    {
        whoseTurn++;
        
        playChess();
    }
    
    return 0;
}

void initGame(void)
{
    char ch;
    
    printf("Enter \'y\' to start the game: ");
    ch = getchar();
    if (ch != 'y' && ch != 'Y')
        exit(0);
    
    system("clear");    /* 清屏 */
    printChessboard();
}

void printChessboard(void)
{
    int i, j;
    
    for (i = 0; i <= N; i++)
    {
        for (j = 0; j <= N; j++)
        {
            if (i == 0)
                printf("%3d", j);
            else if (j == 0)
                printf("%3d", i);
            else if (chessboard[i][j] == 1)
                printf("  O");
            else if (chessboard[i][j] == 2)
                printf("  X");
            else
                printf("  *");
        }
        printf("\n");
    }
}

void playChess(void)
{
    int i, j;
    
    printf("Turn to player %c, please enter the position: ", whoseTurn % 2 == 1? '1': '2');
    scanf("%d %d", &i, &j);
    
    /* 检查输入范围 */
    while (!CHESSBOARD_LIM)
    {
        fprintf(stderr, "Exceed the size of the chessboard, try again: ");
        scanf("%d %d", &i, &j);
    }
    while (chessboard[i][j] != 0)
    {
        printf("This position has been occupied, please enter the position again:");
        scanf("%d %d", &i, &j);
    }
    
    /* 储存棋子 */
    chessboard[i][j] = whoseTurn % 2 == 1? 1: 2;
    
    /* 显示棋盘 */
    system("clear");
    printChessboard();
    
    /* 检验胜利条件 */
    if (judge(i, j))
    {
        printf("Winner is player %c!\n", whoseTurn % 2 == 1? '1': '2');
        exit(EXIT_SUCCESS);
    }
}

int judge(int x, int y)
{
    int i,  /* 行坐标 */
        j,  /* 纵坐标 */
        r;  /* 连续棋子数量 */
    int t = 2 - whoseTurn % 2;  /* 当前棋子种类 */

    /* 纵向胜利 */
    for (r = 1, i = x, j = y; chessboard[++i][j] == t && CHESSBOARD_LIM && r <= 5; r++)
        continue;
    for (i = x, j = y; chessboard[--i][j] == t && CHESSBOARD_LIM && r <= 5; r++)
        continue;
    if (r >= 5)     /* 处理连成五子以上的情况 */
        return 1;

    /* 横向胜利 */
    for (r = 1, i = x, j = y; chessboard[i][++j] == t && CHESSBOARD_LIM && r <= 5; r++)
        continue;
    for (i = x, j = y; chessboard[i][--j] == t && CHESSBOARD_LIM && r <= 5; r++)
        continue;
    if (r >= 5)
        return 1;

    /* "/"型斜向胜利 */
    for (r = 1, i = x, j = y; chessboard[++i][--j] == t && CHESSBOARD_LIM && r <= 5; r++)
        continue;
    for (i = x, j = y; chessboard[--i][++j] == t && CHESSBOARD_LIM && r <= 5; r++)
        continue;
    if (r >= 5)
        return 1;

    /* "\"型斜向胜利 */
    for (r = 1, i = x, j = y; chessboard[++i][++j] == t && CHESSBOARD_LIM && r <= 5; r++)
        continue;
    for (i = x, j = y; chessboard[--i][--j] == t && CHESSBOARD_LIM && r <= 5; r++)
        continue;
    if (r >= 5)
        return 1;

    /* 未触发胜利条件 */
    return 0;
}

/*
 int judge(int x, int y)     //原算法
 {
 int i, j;
 int t = 2 - whoseTurn % 2;
 
 for (i = x - 4, j = y; i <= x; i++)
 {
 if (i >= 1 && i <= N - 4 && t == chessboard[i][j] && t == chessboard[i + 1][j] && t == chessboard[i + 2][j] && t == chessboard[i + 3][j] && t == chessboard[i + 4][j])
 return 1;
 }
 for (i = x, j = y - 4; j <= y; j++)
 {
 if (j >= 1 && j <= N - 4 && t == chessboard[i][j] && t == chessboard[i][j + 1] && t == chessboard[i][j + 2] && t == chessboard[i][j + 3] && t == chessboard[i][j + 4])
 return 1;
 }
 for (i = x - 4, j = y - 4; i <= x && j <= y; i++, j++)
 {
 if (i >= 1 && i <= N - 4 && j >= 1 && j <= N - 4 && t == chessboard[i][j] && t == chessboard[i + 1][j + 1] && t == chessboard[i + 2][j + 2] && t == chessboard[i + 3][j + 3] && t == chessboard[i + 4][j + 4])
 return 1;
 }
 for (i = x + 4, j = y - 4; i >= 1 && j <= y; i--, j++)
 {
 if (i >= 1 && i <= N - 4 && j >= 1 && j <= N - 4 && t == chessboard[i][j] && t == chessboard[i - 1][j + 1] && t == chessboard[i - 2][j + 2] && t == chessboard[i - 3][j + 3] && t == chessboard[i - 4][j + 4])
 return 1;
 }
 
 return 0;
 }
 */
