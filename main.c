#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>
//#include "test.vert"
int main( void ) {
  // Start OpenGL context and OS window using the GLFW helper library.
  if ( !glfwInit() ) {
    fprintf( stderr, "ERROR: could not start GLFW3.\n" );
    return 1;
  }

  // Request an OpenGL 4.1, core, context from GLFW.
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

  // Create a window on the operating system, then tie the OpenGL context to it.
  GLFWwindow* window = glfwCreateWindow( 800, 600, "Hello Triangle", NULL, NULL );
  if ( !window ) {
    fprintf( stderr, "ERROR: Could not open window with GLFW3.\n" );
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent( window );
                                  
  // Start Glad, so we can call OpenGL functions.
  int version_glad = gladLoadGL(glfwGetProcAddress);
  if ( version_glad == 0 ) {
    fprintf( stderr, "ERROR: Failed to initialize OpenGL context.\n" );
    return 1;
  }
  printf( "Loaded OpenGL %i.%i\n", GLAD_VERSION_MAJOR( version_glad ), GLAD_VERSION_MINOR( version_glad ) );

  // Try to call some OpenGL functions, and print some more version info.
  printf( "Renderer: %s.\n", glGetString( GL_RENDERER ) );
  printf( "OpenGL version supported %s.\n", glGetString( GL_VERSION ) );

  /* OTHER STUFF GOES HERE NEXT */
  float points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f 
  };

  // Create buffer object (goes onto graphics card memory), 
  GLuint vbo = 0;
  glGenBuffers( 1, &vbo );
  glBindBuffer( GL_ARRAY_BUFFER, vbo );
  glBufferData( GL_ARRAY_BUFFER, 9 * sizeof( float ), points, GL_STATIC_DRAW );

  // create vertex array object to hold current and all future vbos
  GLuint vao = 0;
  glGenVertexArrays( 1, &vao );
  // bring VA into focus of openGL state machine
  glBindVertexArray( vao );
  glEnableVertexAttribArray( 0 );
  glBindBuffer( GL_ARRAY_BUFFER, vbo );
  // second parameter implies we are describing vertices in only 3 dimensions
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  
  // using GLSL 4.10.6, take vec3 input and store in var vp (each vertex shader invocation gets 3 floats as input)
  // output expects vec4 type so use 1.0 to denote lack of perspective (4th dimension) calculation
  

  //fgets( buf, sizeof buf, vert_shader_ptr )
  const char* vertex_shader = "#version 410 core\n"
  "in vec3 vp;"
  "void main() {"
  "  gl_Position = vec4( vp, 1.0 );"
  "}";
  // fragment = piece of triangle covered by a specific pixel within the shape determined by the vertices
  const char* fragment_shader = "#version 410 core\n"
  "out vec4 frag_colour;"
  "void main() {"
  "  frag_colour = vec4( 0.5, 0.0, 0.5, 1.0 );"
  "}";

  // find glshader source output, make fopen output into data type needed, pass in address
  // glshadersource takes in AN ARRAY OF POINTERS TO STRINGS [*ptr1 -> string, ...]

  // load shaders into OpenGL shader object
  GLuint vs = glCreateShader( GL_VERTEX_SHADER);
  glShaderSource( vs, 1, &vertex_shader, NULL );
  glCompileShader( vs );
  GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
  glShaderSource( fs, 1, &fragment_shader, NULL );
  glCompileShader( fs );

  // after shaders have been compiled, link them together
  GLuint shader_program = glCreateProgram();
  glAttachShader( shader_program, fs );
  glAttachShader( shader_program, vs );
  glLinkProgram( shader_program );

  while ( !glfwWindowShouldClose( window ) ) {
    // update window events (like key-presses)
    glfwPollEvents();

    // clear drawing surface (window currently in context)
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // focus state machine on created shader program and vao that has vertex data
    glUseProgram( shader_program );
    glBindVertexArray( vao );

    // vao data starts at 0 and there are 3 vertices to be drawn per shader call, draw in triangle mode
    glDrawArrays( GL_TRIANGLES, 0, 3 );

    // data was drawn onto back buffer so place back buffer data to front buffer to view triangle on screen
    glfwSwapBuffers( window );
  }

  // fclose( vert_shader_ptr );
  // fclose( frag_shader_ptr );
  // Close OpenGL window, context, and any other GLFW resources.
  glfwTerminate();
  return 0;
}