#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "array.h"

#define ARRAY_DEFAULT_SIZE 8

Array array_create(size_t element_size)
{
	Array s;

	s.array = (void*) malloc(ARRAY_DEFAULT_SIZE * element_size);
	s.logical_size = 0;
	s.physical_size = ARRAY_DEFAULT_SIZE;
	s.element_size = element_size;

	assert(s.array);

	return s;
}

void array_free(Array* s)
{
	free(s->array);

	s->logical_size = 0;
	s->physical_size = 0;
	s->element_size = 0;
}

void array_push(Array* s, void* elt_ptr)
{
	if(s->logical_size >= s->physical_size) {
		s->physical_size = 2*s->logical_size;
		s->array = realloc(s->array, s->physical_size * s->element_size);
	}

	memcpy((char*) s->array + (s->logical_size * s->element_size), elt_ptr, s->element_size);
	s->logical_size ++;
}

size_t array_size(Array* s)
{ return s->logical_size; }

void array_first_pop(Array* s, void* elt_ptr)
{
	if(elt_ptr)
    	memcpy(elt_ptr, s->array, s->element_size);
		
    s->logical_size --;
    memmove(
        s->array, (char*) s->array + s->element_size,
        s->logical_size * s->element_size
    );
}
