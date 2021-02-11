#pragma once
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const float coord = 0.015625f;

int compileAndLinkShaders();
const char* getVertexShaderSource();
const char* getFragmentShaderSource();
private int createFloorArrayObject();
public void drawFloor();
