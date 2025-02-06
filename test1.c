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
    return 1;
  }
  while ( !ferror( frag_shader_ptr ) && !feof( frag_shader_ptr ) ) {
    fgetc( frag_shader_ptr );
    fragSize++;
  }
  if ( ferror( frag_shader_ptr )) {
    printf( "Error opening test.frag\n" );
    return 1;
  }

  rewind( vert_shader_ptr );
  rewind( frag_shader_ptr );

  // allocate memory on heap for output of both files after being read
  char *vertString = malloc( vertSize );
  char *fragString = malloc( fragSize );

  // write vert file to string

  // note size_t can't be negative
  size_t index = 0;
  while ( !ferror( vert_shader_ptr ) && !feof( vert_shader_ptr ) ) {
    // fgetc returns int containing char data, so when assigned to char, C only returns upper 8 bits discarding the remaining bits
    // EX: 00000000 00000000 00000000 01000001   (Binary for 65 in 32-bit int)
    vertString[index] = fgetc( vert_shader_ptr );
    // upon reading EOF index gets incremented again leading to index pointing at a random place in memory
    index++;   
  }
  if ( ferror( vert_shader_ptr ) ) {
    printf( "Error opening test.vert\n" );
    return 1;
  }
  // currently EOF is stored at index - 1 which WILL cause errors. Replace this EOF with null terminator character
  vertString[index - 1] = '\0';

  // write frag file to string

  index = 0;
  while ( !ferror( frag_shader_ptr ) && !feof( frag_shader_ptr ) ) {
    // fgetc returns int containing char data, so when assigned to char, C only returns upper 8 bits discarding the remaining bits
    // EX: 00000000 00000000 00000000 01000001   (Binary for 65 in 32-bit int)
    fragString[index] = fgetc( frag_shader_ptr );
    // upon reading EOF index gets incremented again leading to index pointing at a random place in memory
    index++;   
  }
  if ( ferror( frag_shader_ptr ) ) {
    printf( "Error opening test.frag\n" );
    return 1;
  }
  // currently EOF is stored at index - 1 which WILL cause errors. Replace this EOF with null terminator character
  fragString[index - 1] = '\0';

  fclose( vert_shader_ptr );
  fclose( frag_shader_ptr );
  // print boths strings to stdout
  printf( "%s\n", vertString);
  printf( "%s\n", fragString);

  free( vertString );
  free( fragString );
  return 0;
}