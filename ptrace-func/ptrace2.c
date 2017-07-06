#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <stdio.h>

int main()
{
	pid_t child;
	long orig_eax,eax,ebx,ecx,edx;
	long params[3];
	int status;
	int insyscall=0;
	child=fork();
	if(child==0)
	{
		ptrace(PTRACE_TRACEME,0,NULL,NULL);
		execl("/bin/ls","ls",NULL);
	}
	else
	{
		while(1)
		{
			wait(&status);
			if(WIFEXITED(status))
				break;
			orig_eax=ptrace(PTRACE_PEEKUSER,child,4*orig_eax,NULL);
			if(orig_eax==SYS_write)
			{
				if(insyscall==0)
				{
					insyscall=1;
					params[0]=ptrace(PTRACE_PEEKUSER,child,4*ebx,NULL);
					params[1]=ptrace(PTRACE_PEEKUSER,child,4*ecx,NULL);
					params[2]=ptrace(PTRACE_PEEKUSER,child,4*edx,NULL);
					printf("Write called with %ld,%ld,%ld",params[0],params[1],params[2]);
				}
				else
				{
					eax=ptrace(PTRACE_PEEKUSER,child,4*eax,NULL);
					printf("Write returned with %ld",eax);
					insyscall=0;
				}
			}
			ptrace(PTRACE_SYSCALL,child,NULL,NULL);
		}
	}
	return 0;
}
