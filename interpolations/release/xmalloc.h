#ifndef H_XMA_H
#define H_XMA_H

#include <stdlib.h>
#include <stdio.h>

void* malloc_or_exit(size_t nbytes, const char *file, int line)
{
	void *x;
	if(nbytes <= 0 || (x = malloc(nbytes)) == NULL)
	{
		fprintf(stderr, "%s: line %d : malloc() of %zu bytes failed\n",
					file, line, nbytes);

		exit(EXIT_FAILURE);
	}
	else
	{
		//fprintf(stdout, "Successfully allocated %zu bytes\n", nbytes);
		return x;
	}
}

#define xmalloc(nbytes) malloc_or_exit((nbytes), __FILE__, __LINE__)

#endif
