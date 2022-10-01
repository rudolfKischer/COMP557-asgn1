//
//  Frame.h
//  L01
//
//  Created by Rudolf Kischer on 2022-09-29.
//

#pragma once
#ifndef Frame_h
#define Frame_h


#include <string>
#include <vector>
#include <memory>
#include "GLSL.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Program;
class MatrixStack;

void drawAxis(const std::shared_ptr<Program> prog,
              const std::shared_ptr<MatrixStack> P,
              const std::shared_ptr<MatrixStack> MV);
//void drawAxis(Program *prog, MatrixStack *P, MatrixStack *MV);

#endif /* Frame_h */
