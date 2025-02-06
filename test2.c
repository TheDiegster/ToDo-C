#include <stdio.h>
#include <stdlib.h>
#define LOWER 1024
#define UPPER 1024*64
int main ( int argc, char *argv[] ) {
  FILE *vert_shader_ptr;
  FILE *frag_shader_ptr;

  if ( argc != 3 ) {
    printf( "ERROR: Invalid Number of Arguments\n" );
    return 1;
  }
  // open both files and handle errrors in doing so appropriately
  if (( vert_shader_ptr = fopen( argv[1], "r" )) == NULL ) {
    printf( "Error opening test.vert" );
    return 1;
  }
  if (( frag_shader_ptr = fopen( argv[2], "r" )) == NULL ) {
    printf( "Error opening test.frag" );
    return 1;
  }
  
  // increase by multiples of 1024 and pre-allocate 1024 bytes of on heap to start off with
  size_t increase = LOWER;
  size_t allocated = increase;
  char *vertString = malloc( increase );
  char *fragString = malloc( increase );
  
  // read entire file while allocating appropriate amounts of memory for vert
  size_t total = 0;
  while ( !ferror( vert_shader_ptr ) && !feof( vert_shader_ptr ) ) {
    vertString[total] = fgetc( vert_shader_ptr );
    total++;
    // increase memory allocation when total file size has exceeded current allocated capacity
    if ( total >= allocated ) {
        // ensure memory allocated cannot increase more than the specified upper bound
        if ( increase >= UPPER ) increase = UPPER;
        allocated += increase;
        vertString = realloc( vertString, allocated );
        // Exponentially increase the rate at which memory is allocated to call realloc as little as possible
        increase *= 2;
    }
  }
  if ( ferror( vert_shader_ptr ) ) {
    printf( "Error opening test.vert\n" );
    return 1;
  }
  // shrink allocated memory to exactly the amount of bytes necessary
  vertString = realloc( vertString, total );
  vertString[total - 1] = '\0';

  // NOW SAME FOR FRAG

  // reset filesize in counter
  total = 0;
  while ( !ferror( frag_shader_ptr ) && !feof( frag_shader_ptr ) ) {
    fragString[total] = fgetc( frag_shader_ptr );
    total++;
    if ( total >= allocated ) {
        if ( increase >= UPPER ) increase = UPPER;
        allocated += increase;
        fragString = realloc( fragString, allocated );
        increase *= 2;
    }
  }
  if ( ferror( frag_shader_ptr ) ) {
    printf( "Error opening test.frag\n" );
    return 1;
  }
  fragString = realloc( fragString, total );
  fragString[total - 1] = '\0';

  fclose( vert_shader_ptr );
  fclose( frag_shader_ptr );
  printf( "%s\n", vertString);
  printf( "%s\n", fragString);
  free( vertString );
  free( fragString );
  return 0;
}