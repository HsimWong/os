# 实验二	进程创建与管道通信
## 1	实验描述
## 2	实验过程描述
### 2.1	进程间并发关系


我们发现，题目要求中所说的“创建两个子进程”是无法直接通过使用两次```fork()```函数直接得到的。```fork()```函数将当前环境中的变量复制给另外一个进程，同时，其下方的代码块会被父进程和子进程执行。这就带来一个问题：首先执行的的```fork()```函数生成的两个子进程均会执行下方的```fork()```函数，这样就会导致无论是父进程或子进程都生成了自己的子进程，也就是共有四个进程。

为了避免这种情况发生，我们应该考虑进程函数```fork()```的使用位置：应该在子进程执行期间再使用```fork()```函数，避免父进程再生成子进程。给予这样的考虑，我们有如下代码实现，其执行结果也一并附上。

*代码2-1	使用```fork()```函数进行两个子进程的创建*
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]){
	/* Here describes the father process
	 * Use getpid() to get current pid #.*/
	printf("MainProcess's getpid() = %d\n", getpid());

	/* Description of establishment of pipe.
	 * In this scope, field[0] is opened for reading
	 * while field[1] is opened for writing*/
	int field[2];			// pipe field[2] declaration
	pipe(field);			// pipe() for initialization
	char buf_read[200];

	/* Use fork() function to establish a new process.*/	
	int pid_1 = fork();
	
	/* What is known:
	 * 1. When a new process is forked, pid_1 of son's
	 * 	  process equals 0, which is false
	 * 2. Sub-process(son) is processed first*/
	if(pid_1){	
		/* Activity declaration of Father's process*/
		wait(pid_1);
		printf("Parent's getpid() = %d\n", getpid());
		printf("Parent's pid_1 = %d\n", pid_1);
		close(field[1]);
		read(field[0], buf_read, 24);
		printf("%s\n", buf_read);
	}

	else{
		int pid_2 = fork();		// Another process is established.
		/* Here declares what sons are doing */
		if(pid_2){
			/* Declaration of Son process*/
			printf("Son's getpid() = %d\n", getpid());
			printf("Son's pid_1 = %d\n", pid_1);
			printf("Son's pid_2 = %d\n", pid_2);
			close(field[0]);
			char * info = "Child 1 sends a message.";
			write(field[1], info, strlen(info));
		}
		else{
			/* Declaration of Grandson*/
			printf("Grandson's getpid = %d\n", getpid());
			printf("Grandson's pid_1 = %d\n", pid_1);
			printf("Grandson's pid_2 = %d\n", pid_2);
			close(field[0]);
			char * info = "Child 2 sends a message.";
			write(field[1], info, strlen(info));
		}
	}
	return 0;
}

/*
 * 	Conclusion: 
 *	Son is executed first
 *	son's pid = 0;
 *	Father's pid is greater than 0;
 *	Son's pid != getpid()
 */

```
*代码2-1  结束*

其运行结果如下所示：

*代码2-1-1	使用```fork()```函数进行子进程创建运行结果*
```

```
*代码2-1-1	结束*
----------
