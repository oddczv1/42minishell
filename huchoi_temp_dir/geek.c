#include "../minishell.h"

int main(void)
{
    pid_t pid = fork();
    //char **cmd = ft_split("")
    if ( pid == 0 )
    {
       /* The pathname of the file passed to execl()
          is not defined   */
       execl("  /bin/sh", "bin/sh", "-c", "./nopath", "NULL");
    }
  
    int status;
      
    waitpid(pid, &status, 0);
  
    if ( WIFEXITED(status) )
    {
        int exit_status = WEXITSTATUS(status);        
        printf("Exit status of the child was %d\n", 
                                     exit_status);
    }
    return 0;
}