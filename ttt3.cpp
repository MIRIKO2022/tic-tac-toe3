#include <iostream>
#include <ctime>
#include <windows.h>
using namespace std;

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer, char player);
void showMinimax(char *spaces, char computer, char player);
int minimax(char *spaces, bool isMaximizing, char player, char computer);
int evaluate(char *spaces, char player, char computer);
bool isMovesLeft(char *spaces);
bool checkWinner(char *spaces, char player, char computer);
bool checkTie(char *spaces);

int main()
{
    bool quit = false;
    while (!quit)
    {
        char spaces[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char player = 'X';
        char computer = 'O';
        bool running = true;

        drawBoard(spaces);

        while (running)
        {
            playerMove(spaces, player);
            drawBoard(spaces);
            if (checkWinner(spaces, player, computer) || checkTie(spaces))
            {
                running = false;
                break;
            }

            showMinimax(spaces, computer, player);
            computerMove(spaces, computer, player);
            drawBoard(spaces);
            if (checkWinner(spaces, player, computer) || checkTie(spaces))
            {
                running = false;
                break;
            }
        }

        cout << "Replay? (y/n): ";
        char answer;
        cin >> answer;
        if (answer == 'n' || answer == 'N')
        {
            quit = true;
        }
        else if (answer != 'y' && answer != 'Y')
        {
            cout << "Invalid input. Exiting...\n";
            quit = true;
        }
    }
}

void drawBoard(char *spaces)
{
    cout << '\n';
    cout << "     |     |     " << '\n';
    cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  " << '\n';
    cout << "_____|_____|_____" << '\n';
    cout << "     |     |     " << '\n';
    cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  " << '\n';
    cout << "_____|_____|_____" << '\n';
    cout << "     |     |     " << '\n';
    cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  " << '\n';
    cout << "     |     |     " << '\n';
    cout << '\n';
}

void playerMove(char *spaces, char player)
{
    int number;
    do
    {
        cout << "Enter a spot to place a marker (1-9): ";
        cin >> number;
        number--;
        if (number >= 0 && number <= 8 && spaces[number] != 'X' && spaces[number] != 'O')
        {
            spaces[number] = player;
            break;
        }
        else
        {
            cout << "Invalid move. Try again.\n";
        }
    } while (true);
}

void showMinimax(char *spaces, char computer, char player)
{
    cout << "Evaluating moves for the computer:\n";
    for (int i = 0; i < 9; i++)
    {
        if (spaces[i] != 'X' && spaces[i] != 'O')
        {
            spaces[i] = computer;
            int score = minimax(spaces, false, player, computer);
            spaces[i] = '1' + i;
            cout << "Move at position " << i + 1 << " has score: " << score << '\n';
            Sleep(1000);
        }
    }
    cout << '\n';
}

void computerMove(char *spaces, char computer, char player)
{
    int bestScore = -100;
    int bestMove = -1;

    for (int i = 0; i < 9; i++)
    {
        if (spaces[i] != 'X' && spaces[i] != 'O')
        {
            spaces[i] = computer;
            int score = minimax(spaces, false, player, computer);
            spaces[i] = '1' + i;
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    spaces[bestMove] = computer;
    cout << "Computer places marker at position " << bestMove + 1 << " with evaluation score: " << bestScore << '\n';
    Sleep(1000);
}

int minimax(char *spaces, bool isMaximizing, char player, char computer)
{
    int score = evaluate(spaces, player, computer);

    if (score == 1 || score == -1 || !isMovesLeft(spaces))
    {
        return score;
    }

    if (isMaximizing)
    {
        int best = -100;
        for (int i = 0; i < 9; i++)
        {
            if (spaces[i] != 'X' && spaces[i] != 'O')
            {
                spaces[i] = computer;
                best = max(best, minimax(spaces, false, player, computer));
                spaces[i] = '1' + i;
            }
        }
        return best;
    }
    else
    {
        int best = 100;
        for (int i = 0; i < 9; i++)
        {
            if (spaces[i] != 'X' && spaces[i] != 'O')
            {
                spaces[i] = player;
                best = min(best, minimax(spaces, true, player, computer));
                spaces[i] = '1' + i;
            }
        }
        return best;
    }
}

int evaluate(char *spaces, char player, char computer)
{
    for (int row = 0; row < 9; row += 3)
    {
        if (spaces[row] == spaces[row + 1] && spaces[row + 1] == spaces[row + 2])
        {
            if (spaces[row] == computer)
                return 1;
            else if (spaces[row] == player)
                return -1;
        }
    }

    for (int col = 0; col < 3; col++)
    {
        if (spaces[col] == spaces[col + 3] && spaces[col + 3] == spaces[col + 6])
        {
            if (spaces[col] == computer)
                return 1;
            else if (spaces[col] == player)
                return -1;
        }
    }

    if (spaces[0] == spaces[4] && spaces[4] == spaces[8])
    {
        if (spaces[0] == computer)
            return 1;
        else if (spaces[0] == player)
            return -1;
    }

    if (spaces[2] == spaces[4] && spaces[4] == spaces[6])
    {
        if (spaces[2] == computer)
            return 1;
        else if (spaces[2] == player)
            return -1;
    }

    return 0;
}

bool isMovesLeft(char *spaces)
{
    for (int i = 0; i < 9; i++)
    {
        if (spaces[i] != 'X' && spaces[i] != 'O')
            return true;
    }
    return false;
}

bool checkWinner(char *spaces, char player, char computer)
{
    if (evaluate(spaces, player, computer) == 1)
    {
        cout << "YOU LOSE!\n";
        return true;
    }
    if (evaluate(spaces, player, computer) == -1)
    {
        cout << "YOU WIN!\n";
        return true;
    }
    return false;
}

bool checkTie(char *spaces)
{
    if (!isMovesLeft(spaces))
    {
        cout << "IT'S A TIE!\n";
        return true;
    }
    return false;
}
