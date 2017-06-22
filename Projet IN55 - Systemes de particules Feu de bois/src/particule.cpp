#include "particule.h"
#include "particleengine.h"
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <QImage>
#include <QGLWidget>
#include <ctime>
#include "particule.h"
#include "mainwidget.h"

const int nbrVerticesPart = 4;

GLushort indicesPart[] = {
    0,1,2,3
};

const int nbrIndicesPart = 4;



//! [0]
Particule::Particule()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    // Coordonnées de départ de la Particule
    vertPart[0].Position= {QVector3D(-0.01f, 0.45f, 0.0f)};
    vertPart[1].Position= {QVector3D(-0.01f, 0.47f, 0.0f)};
    vertPart[2].Position= {QVector3D(0.01f, 0.45f, 0.0f)};
    vertPart[3].Position= {QVector3D(0.01f, 0.47f, 0.0f)};
    // Couleur de départ de la Particule (rouge)
    vertPart[0].Color= {QVector3D(1.0f, 0.0f,0.0f)};
    vertPart[1].Color= {QVector3D(1.0f, 0.0f,0.0f)};
    vertPart[2].Color= {QVector3D(1.0f, 0.0f,0.0f)};
    vertPart[3].Color= {QVector3D(1.0f, 0.0f,0.0f)};

    // Vie de la particule
    Life = 1;
    srand(time(NULL));

    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    arrayBuf.bind();
    arrayBuf.allocate(vertPart, nbrVerticesPart * 24);

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indicesPart, nbrIndicesPart * sizeof(GLushort));
}

Particule::~Particule()
{
    arrayBuf.destroy();
    indexBuf.destroy();

}
//! [0]

//! [2]
void Particule::drawParticle(QOpenGLShaderProgram *program)
{

    // Tell OpenGL which VBOs to use
    this->arrayBuf.bind();

    this->indexBuf.bind();

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

void Particule::Update(QOpenGLShaderProgram *program)
{
    // Met à jours les données des particules


    int nbAlea;
    int probaSuicide = generAlea(10);

    Life -=0.01; // On décrémente la vie de la particule de 0.01 à chaque passage dans Update

    if(vertPart[3].Position.y()>0.95) // Si la particule est au dessus du seuil orange
    {
        nbAlea = generAleaControl(); // On génère un nombre aléatoire contrôler afin d'avoir une direction optimale
        if(vertPart[3].Position.y()<1.15) // Si la particule est en dessous du seuil jaune
        {
            if(probaSuicide>=0&&probaSuicide<6) // La particule a 70% de chance d'être détruite
            {
            Life = 0;
            }
        }
        else if(vertPart[3].Position.y()<1.33) // Si la particule est dans la partie inférieure de la partie jaune
        {
            if(probaSuicide>=0&&probaSuicide<1) //La particule a 10% de chance d'être détruite
            {
            Life = 0;
            }
        }
        else // Si la particule est dans la partie supérieure de la partie jaune ou au dessus
        {
            if((probaSuicide>=0&&probaSuicide<8)||(vertPart[0].Position.x()<-0.05 || vertPart[2].Position.x()>0.05)) // La particule a 80% de chance d'être détruite ou est automatiquement détruite si elle est trop loin du centre
            {
            Life = 0;
            }
        }
    }

    else
    {
        nbAlea = generAlea(3); // On génére un nombre aléatoire pour avoir la direction de la particule
    }

    if((vertPart[3].Position.y()>0.65)&&(vertPart[0].Position.x()<-0.25 || vertPart[2].Position.x()>0.25)) // À partir d'une certaine hauteur, la particule est supprimée si elle est trop loin du centre
    {
        Life = 0;
    }

    double depAleaVertical = generAlea(15)/100.0; // Distance de déplacement effectuée à la verticale

    double depAleaHorizontal = generAlea(15)/100.0; // Distance de déplacement effectuée à l'horizontale

    double depZ = generAleaProfondeur()*((generAlea(11))/100.0); // Distance de déplacement en profondeur



    if(nbAlea==0) // La particule va dans une direction Haut-Gauche
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            vertPart[i].Position = {QVector3D(vertPart[i].Position.x()-depAleaHorizontal,vertPart[i].Position.y()+depAleaVertical,vertPart[i].Position.z()+depZ)};


        }
    }
    else if(nbAlea==1) // La particule va dans une direction Haut
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            vertPart[i].Position = {QVector3D(vertPart[i].Position.x(),vertPart[i].Position.y()+depAleaVertical,vertPart[i].Position.z()+depZ)};
        }
    }
    else if(nbAlea == 2) // La particule va dans une direction Haut-Droite
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            vertPart[i].Position = {QVector3D(vertPart[i].Position.x()+depAleaHorizontal,vertPart[i].Position.y()+depAleaVertical,vertPart[i].Position.z()+depZ)};
        }

    }

    if(vertPart[3].Position.y()>0.75 && vertPart[3].Position.y()<0.95) //La couleur de la particule devient mi-rouge-orange à une certaine hauteur
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            vertPart[j].Color = {QVector3D(1.0f,0.25f,0.0f)};
        }
    }
    else if(vertPart[3].Position.y()>0.95 && vertPart[3].Position.y()<1.15) //La couleur de la particule devient orange à une certaine hauteur
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            vertPart[j].Color = {QVector3D(1.0f,0.5f,0.0f)};
        }
    }
    else if(vertPart[3].Position.y()>1.15 && vertPart[3].Position.y()<=1.33) //La couleur de la particule devient mi-orange-jaune à une certaine hauteur
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            vertPart[j].Color = {QVector3D(1.0f,0.75f,0.0f)};
        }
    }
    else if(vertPart[3].Position.y()>1.33 && vertPart[3].Position.y()<=1.50) //La couleur de la particule devient jaune à une certaine hauteur
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            vertPart[j].Color = {QVector3D(1.0f,1.0f,0.0f)};
        }
    }
    else if(vertPart[3].Position.y()>1.50) //La couleur de la particule devient noire à une certaine hauteur
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            vertPart[j].Color = {QVector3D(0.5f,0.5f,0.5f)};

        }
    }
    if(Life <=  0) // Si la particule est détruite, elle revient à sa position initiale, prend la couleur rouge, et récupère toute sa vie
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            vertPart[j].Color = {QVector3D(1.0f,0.0f,0.0f)};
        }
        vertPart[0].Position= {QVector3D(-0.01f, 0.59f, 0.0f)};
        vertPart[1].Position= {QVector3D(-0.01f, 0.61f, 0.0f)};
        vertPart[2].Position= {QVector3D(0.01f, 0.59f, 0.0f)};
        vertPart[3].Position= {QVector3D(0.01f, 0.61f, 0.0f)};
        Life = 1;
    }



    this->arrayBuf.bind();
    this->arrayBuf.allocate(vertPart, nbrVerticesPart *24);

    // Transfer index data to VBO 1
    this->indexBuf.bind();

    this->indexBuf.allocate(indicesPart, nbrIndicesPart * sizeof(GLushort));

    drawParticle(program);



}



int Particule::generAlea(int borne)
// Génère un simple nombre aléatoire borné
{
     int nbgen=rand()%borne;
     return nbgen;
}

int Particule::generAleaControl()
// Permet de mieux contrôler la direction et de rester dans le domaine aléatoire
{
     float midPart = (this->vertPart[0].Position.x()+this->vertPart[2].Position.x())/2; // Milieu de la particule
     int nbgen=rand()%100+1;

     if (this->vertPart[3].Position.y()<1.15) // Si la particule est en dessous du seuil jaune
     {
         // Si le centre de la particule est trop éloigné du centre, elle a 70% de chance de revenir vers le centre, 20% de monter en haut et 10% de s'en éloigner encore
         if (midPart < -0.2)
         {
             if(nbgen<=70)
             {
                 return 2;
             }
             else if(nbgen>70&&nbgen<=90)
             {
                 return 1;
             }
             else
             {
                 return 0;
             }
         }
         else if (midPart > 0.2)
         {
             if(nbgen<=70)
             {
                 return 0;
             }
             else if(nbgen>70&&nbgen<=90)
             {
                 return 1;
             }
             else
             {
                 return 2;
             }
         }
         // Si elle est à une distance raisonnable du centre, les probabilités de direction sont presque équivalentes, avec une préférence pour la montée verticale seule
         else
         {
             if(nbgen<=30)
             {
                 return 0;
             }
             else if(nbgen>30&&nbgen<=70)
             {
                 return 1;
             }
             else
             {
                 return 2;
             }
         }
     }
     else // Si la particule est au dessus du seuil jaune
     {
         // Si le centre de la particule est trop éloigné du centre, elle a 99% de chance de revenir vers le centre et 1% de chance de garder une direction verticale seule

             if (midPart <-0.05)
             {
                 if(nbgen<=99)
                 {
                     return 2;
                 }
                 else if(nbgen>99)
                 {
                     return 1;
                 }

             }
             if (midPart >0.05)
             {
                 if(nbgen<=99)
                 {
                     return 0;
                 }
                 else if(nbgen>99)
                 {
                     return 1;
                 }

             }

             else
             {
                 return 1;
             }
     }

}

int Particule::generAleaProfondeur()
{
    // Contrôle du déplacement en profondeur
    // Si on retourne 1, la particule se déplacera vers l'avant sur l'axe Z
    // Si on retourne -1, la particule se déplacera vers l'arrière sur l'axe Z
    // Si on retourne 0, la particule ne se déplacera pas l'axe Z

   int resultat;
   int nbgen=rand()%2;
   if(this->vertPart[3].Position.y()<0.8)
   {
       if(nbgen==1)
       {
           resultat = 1;
       }
       else
       {
           resultat = -1;
       }
   }

    else if (this->vertPart[3].Position.y()>=0.8&&this->vertPart[3].Position.y()>1.2)
    {
        if (this->vertPart[3].Position.z()>0.5)
        {
            resultat = -1;
        }
        else if (this->vertPart[3].Position.z()<-0.5)
        {
            resultat = 1;
        }
        else
        {
            resultat = 0;
        }
    }
    else
    {
           if (this->vertPart[3].Position.z()>0.1)
           {
               resultat = -1;
           }
           else if (this->vertPart[3].Position.z()<-0.1)
           {
               resultat = 1;
           }
           else
           {
               resultat = 0;
           }

    }
       return resultat;
}
