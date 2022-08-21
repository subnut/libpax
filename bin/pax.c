#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * stdio.h	- stdout
 * stdlib.h	- EXIT_FAILURE, EXIT_SUCCESS
 * unistd.h	- getopt
 */

int
main(int argc, const char *argv[])
{
	return EXIT_FAILURE;
}

/*
 * NOTES:
 * - For setting blocksize (-b) while in write mode (-w), we can use
 *   setbuf/setvbuf
 */
