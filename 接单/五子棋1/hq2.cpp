#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 15
#define MAX_COL 15
#define BLANK 0
#define PLAYER1 1
#define PLAYER2 2

// 判断是否获胜
int is_win(int chessboard[][MAX_COL], int row, int col) {
    int i, j;
    
    // 横向判断
    for (i = 0; i < row; i++) {
        for (j = 0; j < col - 4; j++) {
            if (chessboard[i][j] != BLANK && chessboard[i][j] == chessboard[i][j + 1] && chessboard[i][j] == chessboard[i][j + 2] && chessboard[i][j] == chessboard[i][j + 3] && chessboard[i][j] == chessboard[i][j + 4]) {
                return chessboard[i][j];
            }
        }
    }
    
    // 纵向判断
    for (i = 0; i < row - 4; i++) {
        for (j = 0; j < col; j++) {
            if (chessboard[i][j] != BLANK && chessboard[i][j] == chessboard[i + 1][j] && chessboard[i][j] == chessboard[i + 2][j] && chessboard[i][j] == chessboard[i + 3][j] && chessboard[i][j] == chessboard[i + 4][j]) {
                return chessboard[i][j];
            }
        }
    }
    
    // 斜向（左上到右下）判断
    for (i = 0; i < row - 4; i++) {
        for (j = 0; j < col - 4; j++) {
            if (chessboard[i][j] != BLANK && chessboard[i][j] == chessboard[i + 1][j + 1] && chessboard[i][j] == chessboard[i + 2][j + 2] && chessboard[i][j] == chessboard[i + 3][j + 3] && chessboard[i][j] == chessboard[i + 4][j + 4]) {
                return chessboard[i][j];
            }
        }
    }
    
    // 斜向（右上到左下）判断
    for (i = 4; i < row; i++) {
        for (j = 0; j < col - 4; j++) {
            if (chessboard[i][j] != BLANK && chessboard[i][j] == chessboard[i - 1][j + 1] && chessboard[i][j] == chessboard[i - 2][j + 2] && chessboard[i][j] == chessboard[i - 3][j + 3] && chessboard[i][j] == chessboard[i - 4][j + 4]) {
                return chessboard[i][j];
            }
        }
    }
    
    return 0;  // 无人获胜
}

// 判断棋盘是否已满
int is_draw(int chessboard[][MAX_COL], int row, int col) {
    int i, j;
    int ret = 1;  // 假设棋盘已满
    
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (chessboard[i][j] == BLANK) {
                ret = 0;  // 存在空白位置，棋盘未满
                break;
            }
        }
    }
    return ret;
}



void draw_menu(void) {
    printf("===== 五子棋游戏 =====\n");
    printf("1. 人人对战\n");
    printf("2. 复盘\n");
    printf("3. 退出\n");
    printf("=====================\n");
    printf("请选择：");
}

// 游戏主循环
void person_person(void) {
    int chessboard[MAX_ROW][MAX_COL] = {0};
    int currentPlayer = PLAYER1;
    int row, col;
    
    while (1) {
        printf("当前玩家：玩家%d\n", currentPlayer);
        printf("请输入要落子的位置（行 列）：");
        scanf("%d %d", &row, &col);
        
        // 检查位置是否合法
        if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL || chessboard[row][col] != BLANK) {
            printf("位置不合法，请重新输入\n");
            continue;
        }
        
        // 落子
        chessboard[row][col] = currentPlayer;
        
        // 检查是否获胜
        if (is_win(chessboard, MAX_ROW, MAX_COL)) {
            printf("玩家%d获胜！\n", currentPlayer);
            break;
        }
        
        // 检查是否平局
        if (is_draw(chessboard, MAX_ROW, MAX_COL)) {
            printf("平局！\n");
            break;
        }
        
        // 切换玩家
        currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    }
}




// 保存棋局记录
void save_chess(int chessboard[][MAX_COL], int row, int col) {
    FILE *fp;
    int i, j;
    
    fp = fopen("chess.txt", "w");
    if (fp == NULL) {
        printf("保存失败\n");
        return;
    }
    
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            fprintf(fp, "%d ", chessboard[i][j]);
        }
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    printf("保存成功\n");
}

// 复盘功能
void review_chess(void) {
    FILE *fp;
    char ch;
    
    fp = fopen("chess.txt", "r");
    if (fp == NULL) {
        printf("暂无复盘记录\n");
        return;
    }
    
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    
    fclose(fp);
}

int main(void) {
    int choice;
    draw_menu();
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            person_person();
            break;
        case 2:
            review_chess();
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("选择错误，请重新选择\n");
            break;
    }
    
    return 0;
}
