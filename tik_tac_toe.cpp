#include <bits/stdc++.h>
using namespace std;

void botPlay(char board[3][3]);

void humanPlay(char board[3][3]);

char checkWin(char board[3][3]);

void resetGame(char board[3][3]);

void renderBoard(char board[3][3]);

char checkContinueGame();

int main()
{
    char board[3][3];
    bool quit = false;
    bool humanTurn = true;

    resetGame(board);
    renderBoard(board);
    while (!quit) {
        if (checkWin(board) == 'N') {
            if (humanTurn) {
                humanPlay(board);
                humanTurn = false;
            } else {
                botPlay(board);
                humanTurn = true;
            }
            renderBoard(board);
        } else {
            if (checkWin(board) == 'D') cout << "DRAW!" << "\n\n\n\n";
            else if (checkWin(board) == 'X') cout << "You Win!" << "\n\n\n\n";
            else cout << "You Lose!" << "\n\n\n\n";

            char answer = checkContinueGame();
            
            if (answer == 'Y' || answer == 'y') {
                resetGame(board);
                humanTurn = true;
                renderBoard(board);
            } else quit =true;
        }
    }
    return 0;
}







void botPlay(char board[3][3]) {
    if (board[1][1] == '-') {
        board[1][1] = 'O';
        return;
    }


    int bestScore = -1;
    int bestX, bestY;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-')
            {
                board[i][j] = 'O';
                if (checkWin(board) == 'O') return; // bot thắng được thì đánh luôn
                int score = 0;
                for (int x = 0; x < 3; x++)
                    for (int y = 0; y < 3; y++)
                        if (board[x][y] == '-')
                        {
                            board[x][y] = 'O';
                            if (checkWin(board) == 'O')
                                score++;
                            board[x][y] = '-';
                        }
                if (score > bestScore)
                {
                    bestScore = score;
                    bestX = i;
                    bestY = j;
                }
                board[i][j] = '-';
            }
        }
    }


    int bestScore_human = -1;
    int bestX_human, bestY_human;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-')
            {
                board[i][j] = 'X';
                if (checkWin(board) == 'X') {
                    board[i][j] = 'O'; // nguời thắng được thì chặn luôn
                    return;
                }
                int score_human = 0;
                for (int x = 0; x < 3; x++)
                    for (int y = 0; y < 3; y++)
                        if (board[x][y] == '-')
                        {
                            board[x][y] = 'X';
                            if (checkWin(board) == 'X')
                                score_human++;
                            board[x][y] = '-';
                        }
                if (score_human > bestScore_human)
                {
                    bestScore_human = score_human;
                    bestX_human = i;
                    bestY_human = j;
                }
                board[i][j] = '-';
            }
        }
    }
    if (bestScore >= bestScore_human) board[bestX][bestY] = 'O';
    else board[bestX_human][bestY_human] = 'O';
}


void humanPlay(char board[3][3]) {
    bool invalid;
    int x, y;
    cout << "ban muon tich o nao (nhap toa do x va y) : ";
    cin >> x >> y;
    while (x > 3 || x < 1 || y > 3 || y < 1 || board[y-1][x-1] != '-') {
        cout << "o ban vua nhap khong hop le, hay nhap lai : ";
        cin >> x;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << '-';
        cin >> y;
    }
    
    board[y-1][x-1] = 'X';
}


char checkWin(char board[3][3]) {
    bool checkFull = true;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[y][x] == '-') checkFull = false;
        }
    }

    for (int y = 0; y < 3; y ++) {
        if (board[y][0] == board[y][1] && board[y][1] == board[y][2] && board[y][0] != '-') return board[y][0];
    }
    for (int x = 0; x < 3; x ++) {
        if (board[0][x] == board[1][x] && board[1][x] == board[2][x] && board[0][x] != '-') return board[0][x];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-') return board[0][0];
    if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[2][0] != '-') return board[2][0];

    // Hòa hoặc chưa ai thắng
    if (checkFull) return 'D'; // Hòa
    return 'N'; // chưa ai thắng
}


void resetGame(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) board[i][j] = '-';
    }
}


void renderBoard(char board[3][3]) {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "0 1 2 3" << endl;
    int y = 1;
    for (int i = 0; i < 3; i++) {
        cout << y << ' '; 
        for (int j = 0; j < 3; j++) cout << board[i][j] << ' ';
        cout << endl;
        y++;
    }
}


char checkContinueGame() {
    cout << "Ban co muon choi tiep khong? (Y/N) : ";
    char answer;
    cin >> answer;
    while (!(answer == 'Y' || answer == 'N' || answer == 'y' || answer == 'n'))
    {
        cout << "Error! Vui long nhap lai (Y/N) : ";
        cin >> answer;
    }
    return answer;
}