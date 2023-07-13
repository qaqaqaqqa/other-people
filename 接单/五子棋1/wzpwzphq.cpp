#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ROW 15
#define MAX_COL 15
#define WHITE -1
#define BLACK 1
#define BLANK 0

void draw_chessboardn(int row, int col, int chessboard[][MAX_COL]);
void draw_chessman(int type, char *tableline);
void draw_menu(void);
void person_person(void);
int is_full(int chessboard[][MAX_COL], int row, int col);
int is_win(int chessboard[][MAX_COL], int row, int col);
void save_chess(int chessboard[][MAX_COL], int row, int col);
void replay_chess(void);
void undo_move(int chessboard[][MAX_COL], int row, int col, int step);

int main() {
    int choice;
    draw_menu();
    while (1) {
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                person_person();
            case 2:
                replay_chess();
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("输入错误，请重新选择\n");
        }
    }
    return 0;
}

// 绘制棋盘
void draw_chessboardn(int row, int col, int chessboard[][MAX_COL]) {
    for (int i = 0; i < row; i++) {
        if (i == 0) {
            for (int j = 0; j < col; j++) {
                if (j == 0)
                    draw_chessman(chessboard[i][j], "┌ ");
                else if (j == 14)
                    draw_chessman(chessboard[i][j], "┐");
                else
                    draw_chessman(chessboard[i][j], "┬ ");
            }
            printf("\n");
        } else if (i == 14) {
            for (int j = 0; j < col; j++) {
                if (j == 0)
                    draw_chessman(chessboard[i][j], "└ ");
                else if (j == 14)
                    draw_chessman(chessboard[i][j], "┘ ");
                else
                    draw_chessman(chessboard[i][j], "┴ ");
            }
            printf("\n");
        } else {
            for (int j = 0; j < col; j++) {
                if (j == 0)
                    draw_chessman(chessboard[i][j], "├ ");
                else if (j == 14)
                    draw_chessman(chessboard[i][j], "┤");
                else
                    draw_chessman(chessboard[i][j], "┼ ");
            }
            printf("\n");
        }
    }
}

// 绘制棋子
void draw_chessman(int type, char *tableline) {
    if (type == WHITE)
        printf("● ");
    if (type == BLACK)
        printf("○ ");
    if (type == BLANK)
        printf("%s", tableline);
}

// 绘制主菜单
void draw_menu(void) {
    printf("******************************\n");
    printf("******* 欢迎使用五子棋 *******\n");
    printf("***     研发者：名字名字     ***\n");
    printf("***     请选择对战方式     ***\n");
    printf("*      1.人-人对战           *\n");
    printf("*      2.复盘                *\n");
    printf("*      3.退出                *\n");
    printf("******************************\n");
    printf("请选择：");
}

// 人人对战
void person_person(void) {
    int chessboard[MAX_ROW][MAX_COL] = {BLANK};
    int chess_history[MAX_ROW * MAX_COL][MAX_ROW][MAX_COL] = {0};  // 用于保存每一步的棋盘状态
    int step = 0;  // 记录当前步数
    int i, j;
    char key;
    draw_chessboardn(MAX_ROW, MAX_COL, chessboard);
    for (step = 1; step <= MAX_ROW * MAX_COL; step++) {  // 黑子先行，然后双方轮流下棋
        if (step % 2 == 1) {  // 当前步数为单数，黑棋落子。
            printf("请黑棋落子:");
            while (1) {
                scanf("%d %d", &i, &j);
                if (chessboard[i][j] != BLANK) {
                    printf("该位置已有棋子，请重新输入\n");  // 棋子只能落在空白处
                    continue;
                }
                if (i >= MAX_ROW || j >= MAX_COL || i < 0 || j < 0) {
                    printf("输入超出棋盘范围，请重新输入\n");  // 棋子坐标不可超出棋盘
                    continue;
                }
                break;
            }
            chessboard[i][j] = BLACK;
            draw_chessboardn(MAX_ROW, MAX_COL, chessboard);
            if (is_win(chessboard, MAX_ROW, MAX_COL) == BLACK) {
                printf("黑棋胜\n");
                save_chess(chessboard, MAX_ROW, MAX_COL);
            // 保存当前棋盘状态
                return;
            }
            save_chess(chessboard, MAX_ROW, MAX_COL);
            // 保存当前棋盘状态
            for (int row = 0; row < MAX_ROW; row++) {
                for (int col = 0; col < MAX_COL; col++) {
                    chess_history[step][row][col] = chessboard[row][col];
                }
            }
        } else if (step % 2 == 0) {  // 当前步数为双数，则白棋落子
            printf("请白棋落子:");
            while (1) {
                scanf("%d %d", &i, &j);
                if (chessboard[i][j] != BLANK) {
                    printf("该位置已有棋子，请重新输入\n");  // 棋子只能落在空白处
                    continue;
                }
                if (i >= MAX_ROW || j >= MAX_COL || i < 0 || j < 0) {
                    printf("输入超出棋盘范围，请重新输入\n");  // 棋子坐标不可超出棋盘
                    continue;
                }
                break;
            }
            chessboard[i][j] = WHITE;
            draw_chessboardn(MAX_ROW, MAX_COL, chessboard);
            if (is_win(chessboard, MAX_ROW, MAX_COL) == WHITE) {
                printf("白棋胜\n");
                save_chess(chessboard, MAX_ROW, MAX_COL);
            // 保存当前棋盘状态
                return;
            }
            save_chess(chessboard, MAX_ROW, MAX_COL);
            // 保存当前棋盘状态
            for (int row = 0; row < MAX_ROW; row++) {
                for (int col = 0; col < MAX_COL; col++) {
                    chess_history[step][row][col] = chessboard[row][col];
                }
            }
        }

        if (is_full(chessboard, MAX_ROW, MAX_COL) == 1) {
            printf("棋盘已满");
            exit(0);
        }

        // 悔棋操作
        printf("是否悔棋(y/n): ");
        scanf(" %c", &key);
        if (key == 'y' || key == 'Y') {
            if (step <= 1) {
                printf("无法悔棋\n");
                continue;
            }
            step -= 2;  // 回退两步
            // 恢复棋盘状态
            for (int row = 0; row < MAX_ROW; row++) {
                for (int col = 0; col < MAX_COL; col++) {
                    chessboard[row][col] = chess_history[step][row][col];
                }
            }
            draw_chessboardn(MAX_ROW, MAX_COL, chessboard);
        }
    }
}

// 判断棋盘是否已满
int is_full(int chessboard[][MAX_COL], int row, int col) {
    int ret = 1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (chessboard[i][j] == BLANK) {
                ret = 0;  // 存在空白位置，棋盘未满
                break;
            }
        }
    }
    return ret;
}

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
    // 左上到右下判断
    for (i = 0; i < row - 4; i++) {
        for (j = 0; j < col - 4; j++) {
            if (chessboard[i][j] != BLANK && chessboard[i][j] == chessboard[i + 1][j + 1] && chessboard[i][j] == chessboard[i + 2][j + 2] && chessboard[i][j] == chessboard[i + 3][j + 3] && chessboard[i][j] == chessboard[i + 4][j + 4]) {
                return chessboard[i][j];
            }
        }
    }
    // 右上到左下判断
    for (i = 0; i < row - 4; i++) {
        for (j = 4; j < col; j++) {
            if (chessboard[i][j] != BLANK && chessboard[i][j] == chessboard[i + 1][j - 1] && chessboard[i][j] == chessboard[i + 2][j - 2] && chessboard[i][j] == chessboard[i + 3][j - 3] && chessboard[i][j] == chessboard[i + 4][j - 4]) {
                return chessboard[i][j];
            }
        }
    }
    return 0;
}

// 保存棋盘状态
void save_chess(int chessboard[][MAX_COL], int row, int col) {
    FILE *fp;
    fp = fopen("chess.txt", "w");
    if (fp == NULL) {
        printf("保存失败\n");
        return;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fprintf(fp, "%d ", chessboard[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("保存成功\n");
}

// 复盘功能
void replay_chess(void) {
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

