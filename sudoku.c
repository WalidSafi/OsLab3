#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
  int row;
  int column;
  int (* Puzzle)[9];
} vars;

void * rows_check(void * params);
void * column_check(void * params);
void * sqaure_check(void * params);

void readfile(int Puzzle[9][9]){

  FILE *fp;

  fp = fopen("puzzleSolution.txt","r");

  if (fp == NULL) {
    puts("error opening the file");
  }else{
    for (int i = 0; i < 9; i++) {
      for (int k = 0; k < 9; k++) {
          fscanf(fp,"%d", &Puzzle[i][k]);
      }
    }
  }
  fclose(fp);
}

void printpuzzle(int Puzzle[9][9]){

  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 9; k++) {
      printf("%d",Puzzle[i][k]);
      printf(" ");
    }
    printf("\n");
  }

}

int sudokuCheck(int Puzzle[9][9]){

    for (int i = 0; i < 9; i++) {
      for (int k = 0; k < 9; k++) {
        int cellValue = Puzzle[i][k];
        if (cellValue == 0) {
          return 0;
        }
      }
    }
    return 1;

}

int main(int argc, char const *argv[]) {

  int Puzzle[9][9];

  puts("Initial Puzzle obainted from the file puzzle.txt");
  readfile(Puzzle);
  printpuzzle(Puzzle);
  puts("-------------------------------------");

  vars * row_columns = (vars *) malloc(sizeof(vars));

  row_columns->row = 0;
  row_columns->column = 0;
  row_columns->Puzzle = Puzzle;

  vars * G_one = (vars *) malloc(sizeof(vars));
  G_one->row = 0;
  G_one->column = 0;
  G_one->Puzzle = Puzzle;

  vars * G_Two = (vars *) malloc(sizeof(vars));
  G_Two->row = 0;
  G_Two->column = 3;
  G_Two->Puzzle = Puzzle;

  vars * G_Three = (vars *) malloc(sizeof(vars));
  G_Three->row = 0;
  G_Three->column = 6;
  G_Three->Puzzle = Puzzle;

  vars * G_Four = (vars *) malloc(sizeof(vars));
  G_Four->row = 3;
  G_Four->column = 0;
  G_Four->Puzzle = Puzzle;

  vars * G_Five = (vars *) malloc(sizeof(vars));
  G_Five->row = 3;
  G_Five->column = 3;
  G_Five->Puzzle = Puzzle;

  vars * G_Six = (vars *) malloc(sizeof(vars));
  G_Six->row = 3;
  G_Six->column = 6;
  G_Six->Puzzle = Puzzle;

  vars * G_Seven = (vars *) malloc(sizeof(vars));
  G_Seven->row = 6;
  G_Seven->column = 0;
  G_Seven->Puzzle = Puzzle;

  vars * G_Eight = (vars *) malloc(sizeof(vars));
  G_Eight->row = 6;
  G_Eight->column = 3;
  G_Eight->Puzzle = Puzzle;

  vars * G_Nine = (vars *) malloc(sizeof(vars));
  G_Nine->row = 6;
  G_Nine->column = 6;
  G_Nine->Puzzle = Puzzle;

  pthread_t thread_rowCheck;
  pthread_t thread_columnCheck;
  pthread_t thread_gridOne;
  pthread_t thread_gridTwo;
  pthread_t thread_gridThree;
  pthread_t thread_gridFour;
  pthread_t thread_gridFive;
  pthread_t thread_gridSix;
  pthread_t thread_gridSeven;
  pthread_t thread_gridEight;
  pthread_t thread_gridNine;

  pthread_create(&thread_rowCheck,NULL,rows_check,(void *) row_columns);
  pthread_create(&thread_columnCheck,NULL,column_check,(void *) row_columns);
  pthread_create(&thread_gridOne,NULL,sqaure_check,(void *) G_one);
  pthread_create(&thread_gridTwo,NULL,sqaure_check,(void *) G_Two);
  pthread_create(&thread_gridThree,NULL,sqaure_check,(void *) G_Three);
  pthread_create(&thread_gridFour,NULL,sqaure_check,(void *) G_Four);
  pthread_create(&thread_gridFive,NULL,sqaure_check,(void *) G_Five);
  pthread_create(&thread_gridSix,NULL,sqaure_check,(void *) G_Six);
  pthread_create(&thread_gridSeven,NULL,sqaure_check,(void *) G_Seven);
  pthread_create(&thread_gridEight,NULL,sqaure_check,(void *) G_Eight);
  pthread_create(&thread_gridNine,NULL,sqaure_check,(void *) G_Nine);

  void *returnRow;
  void *returnCol;
  void *returnG_one;
  void *returnG_Two;
  void *returnG_Three;
  void *returnG_Four;
  void *returnG_Five;
  void *returnG_Six;
  void *returnG_Seven;
  void *returnG_Eight;
  void *returnG_Nine;

    pthread_join(thread_columnCheck,&returnCol);
    pthread_join(thread_rowCheck,&returnRow);
    pthread_join(thread_gridOne,&returnG_one);
    pthread_join(thread_gridTwo,&returnG_Two);
    pthread_join(thread_gridThree,&returnG_Three);
    pthread_join(thread_gridFour,&returnG_Four);
    pthread_join(thread_gridFive,&returnG_Five);
    pthread_join(thread_gridSix,&returnG_Six);
    pthread_join(thread_gridSeven,&returnG_Seven);
    pthread_join(thread_gridEight,&returnG_Eight);
    pthread_join(thread_gridNine,&returnG_Nine);

  puts("Puzzle After multithreading");
  printpuzzle(Puzzle);
/*if( returnRow == 1 && returnCol == 1 && returnG_one == 1 && returnG_Two == 1 && returnG_Three == 1 && returnG_Four == 1 && returnG_Five == 1 & returnG_Seven == 1 &&  // Works but gives warnings
 returnG_Six == 1 && returnG_Eight ==1 && returnG_Nine == 1){ */
  if(sudokuCheck(Puzzle) == 1){
    puts("puzzle has been solved");
  } else {
    puts(" Puzzle has not been solved, Not enough information provided");
    }
  //}
}

void * rows_check(void * params){

vars *local = (vars *) params;

int start = local->row;
int col = local->column;
int sum = 0;
int marker;
int markerCheck = 0;

for (int i = start; i < 9; i++) {
    for  (int k = col; k < 9; k++) {
      int cellValue = local->Puzzle[i][k];
    if(cellValue != 0){
        sum = cellValue + sum;
    } else {
      marker = k; markerCheck++;
    }
  }
    if(markerCheck == 1){
        local->Puzzle[i][marker] = 45 - sum;
    }
    sum = 0; marker = 0; markerCheck=0;
  }
  return (void *) 1;
}

void * column_check(void * params){

vars *local = (vars *) params;

int start = local->row;
int col = local->column;
int sum = 0;
int marker;
int markerCheck = 0;

for (int i = col; i < 9; ++i) {
    for  (int k = start; k < 9; ++k) {
      int cellValue = local->Puzzle[k][i];
      if(cellValue != 0){
          sum = cellValue + sum;
      } else {
        marker = k; markerCheck++;
      }
    }
    if(markerCheck == 1){
        local->Puzzle[marker][i] = 45 - sum;
    }
    sum = 0; marker = 0; markerCheck = 0;
 }
  return (void *) 1;
}

void * sqaure_check(void * params){

  vars *local = (vars *) params;

  int start = local->row;
  int col = local->column;
  int sum = 0;
  int r = 0;
  int c = 0;
  int marker= 0;

  for (int i = start; i < start + 3; ++i) {
    for (int k = col; k < col + 3; ++k) {
        int cellValue = local->Puzzle[i][k];
          if(cellValue != 0){
            sum += cellValue;
          } else {
            r = i; c = k;
            marker++;
          }
      }
  }
if (marker == 1) {
  local->Puzzle[r][c+0] = 45 - sum;
}

return (void *) 1;
}
