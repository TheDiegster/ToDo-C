#include <stdio.h>
#include <stdlib.h>
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
  
  // find required number of bytes for each text file
  size_t vertSize = 0;
  size_t fragSize = 0;
  while ( !ferror( vert_shader_ptr ) && !feof( vert_shader_ptr ) ) {
    fgetc( vert_shader_ptr );
    // EX: If file is "123\n" vertSize will be 5 because we increment once fgetc returns EOF and before feof is called again
    // this means our size is 4 bytes + 1 byte for the null termiantor char we will add later
    vertSize++;
  }
  if ( ferror( vert_shader_ptr ) ) {
    printf( "Error opening test.vert\n" );
  }
  while ( !ferror( frag_shader_ptr ) && !feof( frag_shader_ptr ) ) {
    fgetc( frag_shader_ptr );
    fragSize++;
  }
  if ( ferror( frag_shader_ptr )) {
    printf( "Error opening test.frag\n" );
  }

  // allocate memory on heap for output of both files after being read
  char *vertString = malloc(vertSize);
  char *fragString = malloc(fragSize);


  
  return 0;
}