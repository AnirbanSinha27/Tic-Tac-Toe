#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define GAME_NAME "TIC-TAC-TOE"
#define VERSION "0.0.1"
#define COPYRIGHT_INFO "Copyright (c) 2023 Anirban Sinha and Shahibur Rahaman"

typedef enum { FALSE = 0, TRUE = 1 } bool;
typedef enum { WIN = 2, DRAW = 3, NORMAL = 1 } GameState;

#define MAX_POSITIONS 9

void displayMenu(void);
char* createBoard(void);
void resetBoard(char *board);
char swapPlayer(char player);
void multiPlayer(char *board);
void showBoard(const char *board);
GameState getGameState(char *board);
int getPosition(char player_symbol, const char *board);
void playMove(int move, char player_symbol, char *board);

int main(void) {
  displayMenu();

  while (TRUE) {
    char mode;
    do {
      printf("\nMODE (A/B): ");
      fflush(stdin);
      scanf(" %c", &mode);
      mode = toupper(mode);
      if (mode != 'A' && mode != 'B') {
        printf("\nPlease enter values from the given options!\n");
        continue;
      }
    } while (mode != 'A' && mode != 'B');

    int no_of_rounds;
    do {
      printf("NO. OF ROUND(S): ");
      fflush(stdin);
      scanf("%d", &no_of_rounds);
      if (no_of_rounds < 1 || no_of_rounds > 5) {
        printf("\nPlease enter a value between 1 and 5\n");
        continue;
      }
    } while (no_of_rounds < 1 || no_of_rounds > 5);

    char board[MAX_POSITIONS + 1];
    resetBoard(board);

    showBoard(board);

    if (mode == 'A') {
      printf("\nUnder Development!\n");
      exit(EXIT_SUCCESS);
    } else if (mode == 'B') {
      for (int round = 1; round <= no_of_rounds; round++) {
        multiPlayer(board);

        if (round < no_of_rounds) {
          printf("\n===============\n");
          printf("ROUND %d BEGINS!\n", round + 1);
          printf("===============\n");
          resetBoard(board);
          showBoard(board);
        } else if (round == no_of_rounds) {
          printf("\n=============\n");
          printf("END OF MATCH!\n");
          printf("=============\n");
        }
      }
    }

    char is_new_game;
    printf("Wanna play more? (Y/N) ");
    fflush(stdin);
    scanf(" %c", &is_new_game);
    is_new_game = toupper(is_new_game);
    if (is_new_game == 'N') {
      break;
    }
  }

  return 0;
}

void showBoard(const char *board) {
  printf("\n+===========+\n");
  for (int i = 0; i < MAX_POSITIONS; i++) {
    printf("| %c ", board[i]);
    if ((i + 1) % 3 == 0) {
      printf("|\n");
    }
  }
  printf("+===========+\n");
}

void resetBoard(char *board) {
  for (int i = 0; i < MAX_POSITIONS; i++) {
    board[i] = '-';
  }
  board[MAX_POSITIONS] = '\0';
}

void displayMenu(void) {
  printf("%s\n", GAME_NAME);
  printf("Version: %s\n", VERSION);
  printf("\n%s\n\n", COPYRIGHT_INFO);
  printf("This program comes with NO WARRANTY\n\n");
  printf("+==========================+\n");
  printf("|           MODES          |\n");
  printf("+==========================+\n");
  printf("| A) Single Player         |\n");
  printf("| B) Multiplayer           |\n"); 
  printf("+==========================+\n");
}

int getPosition(char player_symbol, const char *board) {
  int pos;
  int is_valid = FALSE;

  do {
    printf("\n| %c | POSITION: ", player_symbol);

    char input[10];
    scanf(" %s", input);

    int valid_input = TRUE;
    for (int i = 0; input[i] != '\0'; i++) {
      if (!isdigit(input[i])) {
        valid_input = FALSE;
        break;
      }
    }

    if (valid_input) {
      pos = atoi(input);

      if (pos < 1 || pos > 9) {
        printf("Please enter a valid position (1-9)!\n");
      } else if (board[pos - 1] != '-') {
        printf("This position is already occupied!\n");
      } else {
        is_valid = TRUE;
        pos--;
      }
    } else {
      printf("Please enter a numeric value (1-9)!\n");
    }
  } while (!is_valid);

  return pos;
}

char swapPlayer(char player) {
  return (player == 'X') ? 'O' : 'X';
}

void playMove(int move, char player_symbol, char *board) {
  board[move] = player_symbol;
}

void multiPlayer(char *board) {
  char current_player = 'X';

  do {
    printf("\nFirst move symbol (X/O): ");
    fflush(stdin);
    scanf("%c", &current_player);
    current_player = toupper(current_player);
    if ((current_player != 'X') && (current_player != 'O')) {
      printf("\nPlease enter values from the given options!\n");
      continue;
    }
  } while ((current_player != 'X') && (current_player != 'O'));

  current_player = swapPlayer(toupper(current_player));

  for (int i = 0; i < MAX_POSITIONS; i++) {
    current_player = swapPlayer(current_player);
    int move = getPosition(current_player, board);
    playMove(move, current_player, board);
    showBoard(board);

    GameState game_state = getGameState(board);
    if (game_state == NORMAL) {
      continue;
    } else if (game_state == WIN) {
      printf("\n==============================\n");
      printf("Player '%c' has won this round!\n", current_player);
      printf("==============================\n");
      break;
    } else if (game_state == DRAW) {
      printf("\n==============================\n");
      printf("           MATCH DRAW!");
      printf("\n==============================\n");
      break;
    }
  }
}

GameState getGameState(char *board) {
  char *b = board;

  // Declare all the possible win positions for any player
  char hor1[3] = {b[0], b[1], b[2]};
  char hor2[3] = {b[3], b[4], b[5]};
  char hor3[3] = {b[6], b[7], b[8]};
  char ver1[3] = {b[0], b[3], b[6]};
  char ver2[3] = {b[1], b[4], b[7]};
  char ver3[3] = {b[2], b[5], b[8]};
  char dia1[3] = {b[0], b[4], b[8]};
  char dia2[3] = {b[6], b[4], b[2]};

  // Store the arrays for all winning positions
  char *win_positions[8] = {
    hor1, hor2, hor3,
    ver1, ver2, ver3,
    dia1, dia2
  };

  // Determine Win state
  for (int i = 0; i < 8; i++) {
    if (win_positions[i][0] == 'X' && win_positions[i][1] == 'X' && win_positions[i][2] == 'X') {
      return WIN; // Player X wins
    }
    if (win_positions[i][0] == 'O' && win_positions[i][1] == 'O' && win_positions[i][2] == 'O') {
      return WIN; // Player O wins
    }
  }

  // Determine Normal state
  for (int i = 0; i < MAX_POSITIONS; i++) {
    if (board[i] == '-') {
      return NORMAL; // Game continues
    }
  }

  // Return Draw state value as other states are not occurring.
  return DRAW; // Draw
}
