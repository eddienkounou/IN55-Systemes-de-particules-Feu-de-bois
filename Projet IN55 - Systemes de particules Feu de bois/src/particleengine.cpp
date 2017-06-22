#include "particleengine.h"
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <QImage>
#include <QGLWidget>
#include <ctime>
#include "particule.h"


struct VertexDataPart
{
    QVector3D position;
    QVector3D color;
};


VertexDataPart verticesPart[] = {
    {QVector3D(-0.05f, 0.85f, 0.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(-0.05f, 0.95f, 0.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(0.05f, 0.85f, 0.0f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(0.05f, 0.95f, 0.0f), QVector3D(1.0f, 0.0f,0.0f)},

};



const int nbrVerticesPart = 4;

GLushort indicesPart[] = {
    0,1,2,3
};

const int nbrIndicesPart = 4;



//! [0]
ParticleEngine::ParticleEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    Particule part;
    srand(time(NULL));

    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initParticle(part);

}

ParticleEngine::~ParticleEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();

}
//! [0]

void ParticleEngine::initParticle(Particule part)
{
////! [1]
    // Transfer vertex data to VBO 0

    //Particule part;

    arrayBuf.bind();
    arrayBuf.allocate(part.vertPart, nbrVerticesPart * sizeof(VertexDataPart));

    // Transfer index data to VBO 1
    indexBuf.bind();

    indexBuf.allocate(indicesPart, nbrIndicesPart * sizeof(GLushort));


//! [1]
}

//! [2]
void ParticleEngine::drawParticle(QOpenGLShaderProgram *program)
{

    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();


    // Offset for position
    quintptr offset = 0;



    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, 24);

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, 24);


    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);




}

void ParticleEngine::Update(QOpenGLShaderProgram *program, Particule part)
{

    int nbAlea = generAlea(3); // On génére un nombre aléatoire pour avoir la direction de la particule
    double depAleaVertical = generAlea(5)/100.0;
    cout << depAleaVertical << endl;
    double depAleaHorizontal = generAlea(8)/100.0;
    cout << depAleaHorizontal << endl;

    if(nbAlea==0) // Haut gauche
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            part.vertPart[i].Position = {QVector3D(part.vertPart[i].Position.x()-depAleaHorizontal,part.vertPart[i].Position.y()+depAleaVertical,part.vertPart[i].Position.z())};

        }
    }
    else if(nbAlea==1) // Haut
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            part.vertPart[i].Position = {QVector3D(part.vertPart[i].Position.x(),part.vertPart[i].Position.y()+depAleaVertical,part.vertPart[i].Position.z())};
        }
    }
    else if(nbAlea == 2) // Haut droite
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            part.vertPart[i].Position = {QVector3D(part.vertPart[i].Position.x()+depAleaHorizontal,part.vertPart[i].Position.y()+depAleaVertical,part.vertPart[i].Position.z())};
        }

    }

    if(part.vertPart[3].Position.y()>1.1 && part.vertPart[3].Position.y()<1.3)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            part.vertPart[j].Color = {QVector3D(1.0f,0.5f,0.0f)};
        }
    }
    else if(part.vertPart[3].Position.y()>1.3 )
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            part.vertPart[j].Color = {QVector3D(1.0f,1.0f,0.0f)};
        }
    }

    arrayBuf.bind();
    arrayBuf.allocate(part.vertPart, nbrVerticesPart * sizeof(VertexDataPart));

    // Transfer index data to VBO 1
    indexBuf.bind();

    indexBuf.allocate(indicesPart, nbrIndicesPart * sizeof(GLushort));

    drawParticle(program);


}

int ParticleEngine::generAlea(int borne)
{
     int nbgen=rand()%borne;
     return nbgen;
}

