// ----------------------------------------------------------------------------
// This file contains source code from the following tutorial:
// https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Introduction
// ----------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>

#include "GL/glew.h"
#include "SDL2/SDL.h"

GLuint program;
GLuint attribute_coord2d;

bool init_resources() {
  GLint compile_ok = GL_FALSE;
  GLint link_ok = GL_FALSE;

  // Colors
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  const char* vs_source =
      "#version 120\n"
      "attribute vec2 coord2d;                  "
      "void main(void) {                        "
      "  gl_Position = vec4(coord2d, 0.0, 1.0); "
      "}";
  glShaderSource(vs, 1, &vs_source, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
  if (!compile_ok) {
    std::cerr << "Error in vertex shader\n";
    return false;
  }

  // Pixels
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  const char* fs_source =
      "#version 120\n"
      "void main(void) {        "
      "  gl_FragColor[0] = 0.0; "
      "  gl_FragColor[1] = 0.0; "
      "  gl_FragColor[2] = 1.0; "
      "}";
  glShaderSource(fs, 1, &fs_source, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
  if (!compile_ok) {
    std::cerr << "Error in fragment shader\n";
    return false;
  }

  // Link shaders with program
  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    std::cerr << "Error in glLinkProgram\n";
    return false;
  }

  return true;
}

void render(SDL_Window* window) {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(program);

  glEnableVertexAttribArray(attribute_coord2d);
  GLfloat triangle[]{.0, .8, -.8, -.8, .8, -.8};
  glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, triangle);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(attribute_coord2d);

  SDL_GL_SwapWindow(window);
}

void main_loop(SDL_Window* window) {
  while (true) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return;
      }
    }

    render(window);
  }
}

void free_resources() {
  // ...
}

int main(int argv, char** args) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow(
      "My First Triangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,
      480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(window);

  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    std::cerr << "Error: glewInit " << glewGetErrorString(glew_status);
    return EXIT_FAILURE;
  }

  if (!init_resources()) {
    return EXIT_FAILURE;
  }

  main_loop(window);

  free_resources();

  return EXIT_SUCCESS;
}
