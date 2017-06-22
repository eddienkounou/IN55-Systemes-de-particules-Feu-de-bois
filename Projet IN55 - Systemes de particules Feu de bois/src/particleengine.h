#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QImage>
#include "particule.h"

using namespace std;


class ParticleEngine : protected QOpenGLFunctions
{
public:
    ParticleEngine();
    virtual ~ParticleEngine();

    void drawParticle(QOpenGLShaderProgram *program);
    void Update(QOpenGLShaderProgram *program, Particule part);
    int generAlea(int borne);


private:
    void initParticle(Particule part);

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    GLuint texId[10];


};

#endif // PARTICLEENGINE_H
