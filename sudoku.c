#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>


int check_row=0;//the index of position is being tested
int check_col=0;//the index of position is being tested
char ch;//a char wait to be checked
bool valid=1;
void *runnerC_row(); /*the  thread check char sudoku row*/
void *runnerC_col(); /*the thread check char sudoku colum*/
void *runnerC_sq(); /*the thread check char sudoku square*/
int index;//the type user choose
int maxInt;//the maximum number of colum at each row
char* p[25][25];

char str1[] = {'1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G'};
char str2[] = {'A','B','C','D','E','F','G','H','I','G','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y'};


int isAvailableC( int row, int col, char c)
{
    check_row = row;
    check_col = col;
    ch = c;
    //check if it is work
    //create threat to solve and verify the answer
    pthread_t tid1; 
    pthread_t tid2; 
    pthread_t tid3; 
    pthread_attr_t attr1, attr2, attr3; 

    pthread_attr_init(&attr1); 
    pthread_attr_init(&attr2); 
    pthread_attr_init(&attr3); 
    pthread_create(&tid1,&attr1,runnerC_row,NULL);
    pthread_create(&tid2,&attr2,runnerC_col,NULL);
    pthread_create(&tid3,&attr3,runnerC_sq,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    if(valid) 
       return 1;
    else 
       return 0;
}

int fillSudokuC(int row, int col)
{
    int i;
    if(row<maxInt && col<maxInt)
    {
        if(p[row][col] != '0')
        {
            if((col+1)<maxInt) return fillSudokuC(row, col+1);
            else if((row+1)<maxInt) return fillSudokuC(row+1, 0);
            else return 1;
        }
        else
        {
            for(i=0; i<maxInt; i++)
            {
		valid = 1;
		if(index == 5){
                if(isAvailableC(row, col, str2[i]))
                {
                    p[row][col] = str2[i];
                    if(fillSudokuC(row, col)) return 1;
                    else p[row][col] = '0';
                }}
		else{
		if(isAvailableC(row, col, str1[i]))
                {
                    p[row][col] = str1[i];
                    if(fillSudokuC(row, col)) return 1;
                    else p[row][col] = '0';
                }}
            }
        }
        return 0;
    }
    else return 1;
}






int main(int argc, char *argv[])
{   
    char puzzle2[4][4] = {{'0','3','4','0'},
			 {'4','0','0','2'},
			 {'1','0','0','3'},
			 {'0','2','1','0'}};
    char puzzle3[9][9] = {{'6','0','0','0','0','0','8','0','3'},
			 {'0','0','4','0','0','7','0','9','0'},
			 {'3','0','0','0','5','0','1','0','0'},
			 {'2','0','0','0','9','0','3','0','0'},
			 {'1','0','7','8','0','0','2','0','4'},
			 {'0','5','0','1','0','0','0','8','0'},
			 {'0','8','0','0','3','6','4','0','5'},
			 {'0','0','0','2','1','0','0','0','0'},
			 {'0','0','0','0','0','9','7','6','2'}};
    char puzzle4[16][16] = {{'2','A','F','5','6','3','1','0','E','0','0','0','0','4','B','C'},
			    {'G','7','0','9','0','4','E','0','3','0','B','6','0','0','8','0'},
			    {'1','B','0','0','0','0','0','0','C','5','0','0','0','G','0','0'},
			    {'0','0','8','D','0','A','0','0','0','0','1','F','3','0','5','7'},
			    {'0','D','B','0','E','0','3','0','2','0','0','0','5','0','A','0'},
			    {'0','3','6','0','0','0','7','0','1','8','5','0','C','2','4','0'},
			    {'E','0','9','1','0','2','C','5','7','D','F','0','8','3','6','0'},
			    {'0','G','0','0','0','1','8','9','B','A','0','0','0','0','F','E'},
			    {'F','0','0','2','0','0','0','E','0','0','0','0','0','B','1','5'},
			    {'B','E','0','4','0','5','6','A','0','F','G','2','0','0','0','3'},
		 	    {'C','0','7','6','1','D','4','0','A','0','0','0','2','0','G','0'},
			    {'0','0','D','G','2','7','F','B','0','0','0','5','A','0','0','0'},
			    {'0','1','0','8','D','0','B','0','0','6','0','0','0','0','0','0'},
			    {'6','0','0','0','8','E','A','0','0','B','0','0','F','0','7','4'},
			    {'7','0','4','A','0','G','0','1','D','0','8','C','0','6','0','0'},
			    {'0','0','0','0','0','0','9','0','G','4','3','A','E','0','C','0'}};
   char puzzle5[25][25] = {{'N','C','W','0','0','0','F','0','0','A','0','0','0','0','0','B','0','0','0','O','0','0','K','R','S'},
			   {'0','M','0','O','0','0','T','0','V','W','X','R','0','0','K','0','A','U','0','0','0','0','0','P','0'},
 			   {'L','0','0','B','G','0','0','0','0','R','S','0','0','0','0','0','H','C','X','I','J','T','0','0','M'},
			   {'A','0','0','0','V','0','J','X','M','0','0','U','0','0','0','F','S','0','0','0','0','Y','L','D','C'},
			   {'S','0','R','0','0','0','L','0','0','0','0','0','0','F','0','W','0','N','0','0','0','X','V','Q','O'},
			   {'0','0','I','W','A','C','R','0','0','0','0','0','N','L','0','H','0','K','0','0','0','D','0','0','0'},
			   {'0','Q','F','0','J','0','X','0','0','E','0','S','0','M','0','G','0','0','0','0','P','U','0','0','W'},
			   {'0','0','0','L','K','N','0','0','G','D','Q','T','X','0','0','0','0','I','0','P','S','0','0','0','H'},
			   {'U','P','0','E','0','J','0','0','0','V','0','A','C','0','I','O','0','0','0','0','N','K','Q','F','0'},
			   {'V','N','B','S','0','0','Y','0','0','0','0','K','0','0','0','0','Q','0','W','C','T','0','0','0','I'},
			   {'0','0','S','P','C','Y','K','U','0','O','0','0','0','R','D','0','W','0','L','0','0','0','0','0','N'},
			   {'0','0','0','Y','E','0','0','I','0','0','0','X','K','S','B','J','R','0','C','0','O','L','0','H','P'},
			   {'H','0','0','N','0','F','E','C','0','P','0','0','0','0','0','S','0','Y','T','X','0','A','0','0','D'},
 			   {'B','J','0','A','W','0','G','0','X','Q','V','C','U','N','0','0','0','M','0','0','R','F','0','0','0'},
			   {'I','0','0','0','0','0','M','0','R','0','W','O','0','0','0','N','0','B','V','D','Q','C','U','0','0'},
			   {'D','0','0','0','O','Q','I','0','A','0','0','0','0','V','0','0','0','0','B','0','0','S','X','C','F'},
			   {'0','T','L','Q','N','0','0','0','0','C','R','0','B','X','0','U','0','0','0','A','0','V','0','G','K'},
			   {'E','0','0','0','S','U','0','R','0','0','0','0','Q','K','C','P','F','0','0','Y','M','B','0','0','0'},
			   {'F','0','0','C','R','0','0','0','0','T','0','Y','0','O','0','L','0','0','I','0','D','0','N','U','0'},
			   {'0','0','0','M','0','0','0','F','0','X','0','N','J','0','0','0','0','0','H','T','L','E','P','0','0'},
			   {'Y','A','T','K','0','0','0','S','0','H','0','D','0','0','0','0','0','0','N','0','0','0','M','0','X'},
			   {'G','S','Q','J','0','0','0','0','N','L','0','0','0','E','0','0','I','O','Y','0','A','0','0','0','V'},
			   {'O','0','0','X','L','R','A','K','E','0','0','0','0','0','T','V','0','0','0','0','B','P','0','0','U'},
			   {'0','W','0','0','0','0','0','V','J','0','K','0','0','B','O','T','M','0','U','0','0','H','0','Y','0'},
			   {'M','E','U','0','0','O','0','0','0','Y','0','0','0','0','0','C','0','0','Q','0','0','0','J','N','T'}};
    for(int i=0;i<25;i++){
    for(int j=0;j<25;j++){
	p[i][j]='*';}}
    
    printf("I have 4 sudoku. Which one would you ask me to solve? \n");
    //print the 4*4 sudoku
    printf("This is a 4*4 sudoku  Its index is 2\n");
    for(int i=0; i<4; i++)
    {
      if(i%2 == 0) printf("+---+---+\n");
      for(int j=0; j<4; j++) printf("|%c", puzzle2[i][j]);
      printf("|\n"); 
    }
    printf("\n+---+---+\n");
    //print the 9*9 sudoku
    printf("This is a 9*9 sudoku  Its index is 3\n");
    for(int i=0; i<9; i++)
    {
      if(i%3 == 0) printf("+-----+-----+-----+\n");
      for(int j=0; j<9; j++) printf("|%c", puzzle3[i][j]);
      printf("|\n");    
    }
    printf("\n+-----+-----+-----+\n");
    //print the 16*16 sudoku
    printf("This is a 16*16 sudoku  Its index is 4\n");
    for(int i=0; i<16; i++)
    {
      if(i%4 == 0) printf("+-------+-------+-------+-------+\n");
      for(int j=0; j<16; j++) printf("|%c", puzzle4[i][j]);
      printf("|\n");    
    }
    printf("\n+-------+-------+-------+-------+\n");
    //print the 25*25 sudoku
    printf("This is a 25*25 sudoku  Its index is 5\n");
    for(int i=0; i<25; i++)
    {
      if(i%5 == 0) printf("+---------+---------+---------+---------+---------+\n");
      for(int j=0; j<25; j++) printf("|%c", puzzle5[i][j]);
      printf("|\n");    
    }
    printf("\n+---------+---------+---------+---------+---------+\n");
    //ask client to choose one
    printf("Please input the index:\n");
    scanf("%d",&index);
    maxInt = index*index;
    if(index==2){for(int i = 0;i<maxInt;i++){for(int j = 0;j<maxInt;j++){p[i][j]=puzzle2[i][j];}}}
    if(index==3){for(int i = 0;i<maxInt;i++){for(int j = 0;j<maxInt;j++){p[i][j]=puzzle3[i][j];}}}
    if(index==4){for(int i = 0;i<maxInt;i++){for(int j = 0;j<maxInt;j++){p[i][j]=puzzle4[i][j];}}}
    if(index==5){for(int i = 0;i<maxInt;i++){for(int j = 0;j<maxInt;j++){p[i][j]=puzzle5[i][j];}}}
   
    if(fillSudokuC(0,0)){
    //print the outcome
     printf("This sudoku has been solved. \n");
    for(int i=0; i<maxInt; i++)
    {
      for(int j=0; j<maxInt; j++) printf("|%c",p[i][j]);
      printf("|\n"); 
    }}
    else printf("\n\nNO SOLUTION\n\n");
   
    
    /* 
      terminate with exit code 0
    */
    return 0;
}



void *runnerC_row()
{
  //thread that check row
  for(int i=0;(i<maxInt)&&(valid);i++){
    //if we find a num same with current_num in same row and that is not itself, false and break
    if(p[i][check_col]== ch){valid=0;}}
 /*exit the thread with exit code 0*/
 pthread_exit(0);
}

void *runnerC_col()
{
  //thread that check column

  for(int i=0;(i<maxInt)&&(valid);i++){
    //if we find a num same with current_num in same column and that is not itself, false and break
    if(p[check_row][i]==ch){valid=0;}}
    /*exit the thread with exit code 0*/
    pthread_exit(0);	
}

void *runnerC_sq()
{
  //thread that check block
  //calculate where the block start and save at row_start and col_start.
  int row_start=(check_row/index)*index;
  int col_start=(check_col/index)*index;
  for(int i=0;(i<maxInt)&&(valid);i++){
    
   //if we find a num same with current_num in same block, false and break
   if(p[row_start+(i%index)][col_start+(i/index)]==ch){valid=0;}}
 /*exit the thread with exit code 0*/
 pthread_exit(0);
}


  




