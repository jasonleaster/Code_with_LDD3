/*************************************************
code writer : EOF
code date : 2014.08.14
e-mail:	jasonleaster@gmail.com
code purpose:
	just a demo for how to use structure--utsname

	If you find something wrong with my code, 
please touch me by e-mail. Thank you.
 
*************************************************/
#include <stdio.h>
#include <sys/utsname.h>

int main()
{
	struct utsname demo;

	uname(&demo);

	printf("sysname: %s\nnodename: %s\nrelease :%s\nmachine: %s\n",
		demo.sysname,demo.nodename,demo.release,demo.machine);
#ifdef __USE_GNU
	printf("domainname: %s\n",demo.domainname);
#else
	printf("__domainname: %s\n",demo.__domainname);
#endif

	return 0;
}
