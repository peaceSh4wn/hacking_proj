#include <stdio.h>
#include <unistd.h>

int main()
{   
  int i;
  printf ("PID: %d\n", (int)getpid());
  for(i = 0; i < 10; i++) 
    {
      write (1, "Hello World\n", 12);
      sleep(2);
  }
  getchar();

  return 0;
}
