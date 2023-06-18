#include "ms.h"

#ifndef UTD
#define UTD 0
#endif

//Add mok
static void	test(char *input, char *expected)
{
	int debug = UTD || getenv("UTD") != NULL;
	static int	n = 0; n++;
	char	*mine = ft_strdup(input);
	replace_env_variables(mine, &mine);
	if (strcmp(mine, expected) == 0)
	{
		printf(" %d.[%sx%s]", n, BGREEN, RESET);//, '?');
		if (debug) printf(" \"%s\"\n",input);
	}
	else
	{
		if (!debug)
			printf("\n %s%d.[x%c]%s \"%s\"", BRED, n, '?', RESET, input);
		if (debug)
		{
			printf(" %s%d.[x%c]%s ", BRED, n, '?', RESET);
			printf("TEST: \"%s\"\n", input);
			printf(" expected: \"%s\"\n", expected);
			printf("      got: \"%s\"\n", mine);
		}	
	}
}

//add debug + add statsd 5 out 10

int	main(void)
{
	printf("ENVIRONEMENT VARIABLE: \n");
	setenv("T1", "Hello", 1);
	setenv("T2", "World", 1);
	setenv("T3", "??", 1);
	unsetenv("T");
	unsetenv("none");
	
	test("$T1", "Hello");
	test("$T1?", "Hello?");
	test("$T1 Mr.$", "Hello Mr.$");
	test("$T1 $T2 $T3", "Hello World ??");
	test("..$T1$T2$T3..", "..HelloWorld??..");
	test("$T shoosh", " shoosh");
	test("$T$ xd", "$ xd");
	test("$", "$");
	test("$none", "");
	char pid[30] = "NaN"; 
	sprintf(pid, "%d", getpid());
	test("$$", pid);
	char pid2[500] = "";
	sprintf(pid2, "%s$ %s%s %s%s$ %s%s%s!",pid,pid,pid,pid,pid,pid,pid,pid);
	test("$$$ $$$$ $$$$$ $$$$$$!", pid2);
	char all[256];
	for (int i=-127; i<128; i++)
	       all[127+i] = (i != 0 && i != '$') ? i : 'x';	
	test(all, all);
	unsetenv("T1");
	unsetenv("T2");
	unsetenv("T3");

	printf("\n");
}
