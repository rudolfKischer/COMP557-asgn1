//
//  Frame.cpp
//  L01
//
//  Created by Rudolf Kischer on 2022-09-29.
//


#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Shape.h"
#include "Motion.h"
#include "DAGNode.h"
#include "Frame.h"

#include <stdio.h>

using namespace std;



void drawAxis(const std::shared_ptr<Program> prog,
              const std::shared_ptr<MatrixStack> P,
              const std::shared_ptr<MatrixStack> MV)
{
    GLuint vao;
    GLuint posBufID; // position buffer for drawing a line loop
    GLuint aPosLocation = 0; // location set in col_vert.glsl (or can be queried)
    const GLuint TotNumVertices = 6;
    GLfloat vertices[TotNumVertices][3] = {
                                        { 0, 0,  0 },
                                        {  1, 0,  0 },
                                        {  0,  0,  0 },
                                        {  0, 1,  0 },
                                        {  0,  0,  0 },
                                        { 0,  0,  1 }};
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &posBufID);
    glBindBuffer(GL_ARRAY_BUFFER, posBufID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),    vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(aPosLocation);
    glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //draw axis
    prog->bind();
    glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
    glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV->topMatrix()[0][0]);
    glUniform3f(prog->getUniform("col"), 1, 0, 0);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 2);
    glUniform3f(prog->getUniform("col"), 0, 1, 0);
    glDrawArrays(GL_LINES, 2, 2);
    glUniform3f(prog->getUniform("col"), 0, 0, 1);
    glDrawArrays(GL_LINES, 4, 2);
    prog->unbind();
}
