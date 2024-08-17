#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

char maze[0x32*0x32];

void genmaze(int param_1,int param_2)
{
  int iVar1;
  int iVar2;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  for (local_14 = 0; local_14 < param_1; local_14 = local_14 + 1) {
    for (local_18 = 0; local_18 < param_2; local_18 = local_18 + 1) {
      maze[(long)local_18 + (long)local_14 * 0x32] = 0x20;
    }
  }
  for (local_1c = 0; local_1c < param_1; local_1c = local_1c + 1) {
    maze[(long)local_1c * 0x32] = 0x23;
    maze[(long)(param_2 + -1) + (long)local_1c * 0x32] = 0x23;
  }
  for (local_20 = 0; local_20 < param_2; local_20 = local_20 + 1) {
    maze[local_20] = 0x23;
    maze[(long)local_20 + (long)(param_1 + -1) * 0x32] = 0x23;
  }
  for (local_24 = 0; local_24 < 0xfa; local_24 = local_24 + 1) {
    iVar1 = rand();
    iVar2 = rand();
    maze[(long)(iVar2 % (param_2 + -2) + 1) + (long)(iVar1 % (param_1 + -2) + 1) * 0x32] = 0x23;
  }
  do {
    iVar1 = rand();
    iVar2 = iVar1 % (param_1 + -2) + 1;
    iVar1 = rand();
    iVar1 = iVar1 % (param_2 + -2) + 1;
  } while (maze[(long)iVar1 + (long)iVar2 * 0x32] != ' ');
  maze[(long)iVar1 + (long)iVar2 * 0x32] = 0x45;
  return;
}

void printmaze(int param_1,int param_2,int param_3,int param_4)
{
  int local_20;
  int local_1c;
  
  for (local_1c = 0; local_1c < param_1; local_1c = local_1c + 1) {
    for (local_20 = 0; local_20 < param_2; local_20 = local_20 + 1) {
      if ((local_1c == param_3) && (local_20 == param_4)) {
        printf("P");
      }
      else {
        printf("%c",(ulong)(uint)(int)(char)maze[(long)local_20 + (long)local_1c * 0x32]);
      }
    }
    printf("\n");
  }
  return;
}


int main(void)
{
  int random;
  time_t time_now;
  FILE *__stream;
  long in_FS_OFFSET;
  int y;
  int x;
  char local_79;
  char local_78 [104];
  long local_10;
  
  time_now = time((time_t *)0x0);
  srand((uint)time_now);
  genmaze(0x32, 0x32);
	do {
    random = rand();
    x = random % 0x30 + 1;
    random = rand();
    y = random % 0x30 + 1;
  } while (maze[(long)y + (long)x * 0x32] != ' ');
	printmaze(0x32, 0x32, x, y);
  /*
LABEL_INPUT_LOOP_START:
  do {
    scanf(" %c",&local_79);
    if (local_79 == 'w') {
      x = x + -1;
    }
    else if (local_79 == 's') {
      x = x + 1;
    }
    else if (local_79 == 'a') {
      y = y + -1;
    }
    else {
      if (local_79 != 'd') goto LABEL_INPUT_LOOP_START;
      y = y + 1;
    }
    if (maze[(long)y + (long)x * 0x32] == '#') goto LABEL_INPUT_LOOP_END;
    if (maze[(long)y + (long)x * 0x32] == 'E') {
      __stream = fopen("flag.txt","r");
      fgets(local_78,100,__stream);
      fclose(__stream);
      printf("%s",local_78);
LABEL_INPUT_LOOP_END:
      return 0;
    }
  } while( true );
	*/
}
