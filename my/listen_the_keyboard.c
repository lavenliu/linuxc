#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <fcntl.h>
int main ()
{
	int keys_fd;
	int pipes[2];
	struct input_event t;
	char buf[100];
	int pid,pid1;
	int nread;
	int key_code;
	if(pipe(pipes) < 0)
		{
			printf("%s\n","pipes error!" );
			exit(EXIT_FAILURE);
		}
	pid = fork();
	if(pid < 0 )
		{
			printf("%s\n","fork() function error!" );;
			exit(EXIT_FAILURE);
		}
	else if(pid == 0)
		{
			keys_fd = open ("/dev/input/event4", O_RDONLY);
			if (keys_fd <= 0)
				{
					printf ("open /dev/input/event4 device error!\n");
				}
			close(pipes[0]);
			while (1)
				{
					if (read (keys_fd, &t, sizeof (t)) == sizeof (t))
						{
							if (t.type == EV_KEY)
								{
									if ( t.value == 0)
										{
											printf ("key %d \n", t.code);
											//sprintf(buf,"key %d \n\0", t.code);
											key_code = t.code;
											write(pipes[1],&key_code,sizeof(key_code));
											if(t.code==KEY_ESC)
												break;
										}
								}
						}
				}
			close (keys_fd);
			close(pipes[1]);
			exit(EXIT_SUCCESS);
		}
	else
		{
			pid1 = fork();
			if(pid1 < 0 )
				{
					printf("%s\n"," fork function error" );
					exit(EXIT_FAILURE);
				}
			if(pid1 == 0)
				{
					FILE * fp;
					close(pipes[1]);
					//int writefd;
					fp = fopen("data.out","w+");
					//writefd = open("data.out", O_WRONLY | O_CREAT);
					while(1)
						{
							read(pipes[0],&key_code,sizeof(key_code));
							//write(writefd,&key_code,sizeof(key_code));
							fprintf( fp,"%d    ",key_code);
							if(key_code == 1)
								break;
						}
					close(pipes[0]);
					exit(EXIT_SUCCESS);
				}
			else
				{
					exit(EXIT_SUCCESS);
				}
		}
	return 0;
}
