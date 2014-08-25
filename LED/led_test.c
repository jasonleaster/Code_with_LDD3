/*
code writer	: EOF
code date	: 2014.08.19.com
code file	: led_by_EOF.c
e-mail		: jasonleaster@gmail.com

code purpos:

	This code is a demo for test my led-device.

	If you find there is something wrong with my code
and change it into a better version , please touch me 
by e-mail. Thank you.

*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	int fd = 0;
	int ret = 0;

	if((fd = open("/dev/led_by_EOF",O_RDWR)) < 0)
	{
		printf("line %d open failed\n",__LINE__);
		return 0;
	}

	int buf = 0;
	int time = 0;

	buf = 0x0;

	for(time = 0,buf = 0;time < 5;time++)
	{
		if((ret = write(fd,&buf,sizeof(buf))) < 0)
		{
			printf("write error!\n ret : %d\n",ret);
			
			//goto failed;
		}
		else
		{
			printf("write successful! ret %d,buf:%d &buf:%p\n",ret,buf,&buf);
		}

		buf = ~buf;

		sleep(2);
	}
	

failed:
	close(fd);
	
	return 0;
}
