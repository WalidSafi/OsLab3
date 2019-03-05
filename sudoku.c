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

int main(int argc, char const *argv[]) {

  int Puzzle[9][9];

  puts("Initial Puzzle obainted from the file puzzle.txt");
  readfile(Puzzle);
//  printpuzzle(Puzzle);

  vars * row_columns = (vars *) malloc(sizeof(vars));

  row_columns->row = 0;
  row_columns->column = 0;
  row_columns->Puzzle = Puzzle;

  pthread_t thread_rowCheck;
  pthread_t thread_columnCheck;

  pthread_create(&thread_rowCheck,NULL,rows_check,(void *) row_columns);
  pthread_create(&thread_columnCheck,NULL,column_check,(void *) row_columns);

  void *returnRow;
  void *returnCol;

  pthread_join(thread_rowCheck,&returnRow);
  pthread_join(thread_columnCheck,&returnCol);

  if( (int) returnRow == 1){
    puts("all rows are complete");
  }else {
    puts("invalid solution to puzzle");
  }

  if ( (int) returnCol == 1) {
    puts("all colums are complete");
  }

  printpuzzle(Puzzle);
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
    sum = 0; marker = 0; markerCheck=0;
 }
  return (void *) 1;
}

void * sqaure_check(void * params){

}
