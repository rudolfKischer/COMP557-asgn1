#include "DAGNode.h"
#include "MatrixStack.h"
#include "Program.h"

#include <iostream>
#include <cassert>
#include <cmath>

#include "GLSL.h"
#include "Frame.h"
#include "Shape.h"

using namespace std;

class Shape;

DAGNode::DAGNode()
{
}

DAGNode::~DAGNode()
{
}

void DAGNode::init()
{
}

double toRad(double degrees)
{
    return degrees * M_PI / 180.0f;
}


void DAGNode::draw(const std::shared_ptr<Program> prog,
                   const std::shared_ptr<MatrixStack> P,
                   const std::shared_ptr<MatrixStack> MV,
                   const shared_ptr<Shape> shape,
                   float* frameData,
                   GLint fCount,
                   GLint numChannels) const
{
	// DONE: implemented this!
    
    MV->pushMatrix();
    MV->translate(this->offset);
    
    //make sure this node is not an endpoint
    if( this->name.compare("EndSite") != 0 ){
        
        GLuint thisVertexPosition =  (numChannels) * fCount + this->channelDataStartIndex ;
        
        //apply rotation and translation channnels
        
        for(int i=0; i<this->channels.size(); i++){
            if(this->channels[i].compare("Xposition") == 0){
                GLfloat xpos = frameData[thisVertexPosition + i];
                MV->translate(xpos,0.0f,0.0f);
            }
            if(this->channels[i].compare("Yposition") == 0){
                GLfloat ypos = frameData[thisVertexPosition + i];
                MV->translate(0.0f,ypos,0.0f);
            }
            if(this->channels[i].compare("Zposition") == 0){
                GLfloat zpos = frameData[thisVertexPosition + i];
                MV->translate(0.0f,0.0f,zpos);
            }
            if(this->channels[i].compare("Xrotation") == 0){
                GLfloat xrot = toRad(frameData[thisVertexPosition + i]);
                MV->rotate(xrot, glm::vec3(1, 0, 0));
            }
            if(this->channels[i].compare("Yrotation") == 0){
                GLfloat yrot = toRad(frameData[thisVertexPosition + i]);
                MV->rotate(yrot, glm::vec3(0, 1, 0));
            }
            if(this->channels[i].compare("Zrotation") == 0){
                GLfloat zrot = toRad(frameData[thisVertexPosition + i]);
                MV->rotate(zrot, glm::vec3(0, 0, 1));
            }
        }
        
        //draw reference frame
        MV->pushMatrix();
        MV->scale(40,40,40);
        drawAxis(prog, P, MV);
        MV->popMatrix();
        
        //draw teapots at joints
        prog->bind();
        MV->pushMatrix();
        
        //different scaling for diffeerent joints
        if(this->name.compare("Chest") == 0 ){
            MV->scale(1.5,1.5,1.5);
        }
        if(this->name.compare("Head") == 0 ){
            MV->scale(1.3,1.3,1.3);
        }
        
        MV->scale(30,30,30);
        glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
        glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV->topMatrix()[0][0]);
        shape->draw(prog);
        MV->popMatrix();
        prog->unbind();
        GLuint numChild = this->children.size();
        for(int i = 0;i < numChild; i++){
            this->children[i]->draw(prog, P, MV, shape, frameData, fCount, numChannels);
            
        }
        
        
        
    }else{
        
        
        
        prog->bind();
        MV->pushMatrix();
        MV->scale(30,30,30);
        
//        MV->rotate(1, 1, 0, 0);
        glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P->topMatrix()[0][0]);
        glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &MV->topMatrix()[0][0]);
        shape->draw(prog);
        MV->popMatrix();
        prog->unbind();
        
        
    }
    MV->popMatrix();
    
    
}
