#ifndef PARTICULE_H
#define PARTICULE_H
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QImage>
#include <glm/vec3.hpp>

using namespace std;

class Particule : protected QOpenGLFunctions
{
public:
    int a;
    Particule();
    virtual ~Particule();
    float Life;
    struct VertDataPart{
        QVector3D Position;
        QVector3D Color;
    };
    VertDataPart vertPart[4];
    void drawParticle(QOpenGLShaderProgram *program);
    void Update(QOpenGLShaderProgram *program);
    int generAlea(int borne);
    int generAleaControl();
    int generAleaProfondeur();
    int suicide();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    GLuint texId[10];
};

#endif // PARTICULE_H
