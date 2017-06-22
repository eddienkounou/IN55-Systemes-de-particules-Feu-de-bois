#include "objloader.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

using namespace std;

Objloader::Objloader()
{

}


bool Objloader::loadObj(vector < glm::vec3 > & temp_vertices,vector <unsigned int> & vertexIndices)
{
    char lineHeader[64];

    vector< unsigned int > uvIndices, normalIndices;

    vector< glm::vec3 > temp_normals;
    vector< glm::vec2 > temp_uvs;
    unsigned int x=0;


    FILE * file_obj = fopen("C:/Users/Eddie/Desktop/12_NKOUNOU_SORON_HU/Projet IN55 - Systemes de particules Feu de bois/ModeleBlender/buche.obj", "r");

    if( file_obj == NULL ){
        printf("Impossible d'ouvrir le fichier obj !\n");
        return false;
    }

    while( 1 ){


        // read the first word of the line
        int res = fscanf(file_obj, "%s", lineHeader);

        if (res == EOF)
            break;
      // On récupère les vertices
        if ( strcmp( lineHeader, "v" ) == 0 ){
                glm::vec3 vertex;
                fscanf(file_obj, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
                temp_vertices.push_back(vertex);

        }
      // On récupère les coordonnées de texture
        else if ( strcmp( lineHeader, "vt" ) == 0 ){
                glm::vec2 uv;
                fscanf(file_obj, "%f %f\n", &uv.x, &uv.y );
                temp_uvs.push_back(uv);
                x++;
        }
        // On récupère les coordonnées des normales
        else if ( strcmp( lineHeader, "vn" ) == 0 ){

            glm::vec3 normal;
            fscanf(file_obj, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);

        }
        // On récupère les indices
        else if ( strcmp( lineHeader, "f" ) == 0 ){
                string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file_obj, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                if (matches != 9){
                    printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                    return false;
                }
                vertexIndices.push_back(vertexIndex[0]-1);
                vertexIndices.push_back(vertexIndex[1]-1);
                vertexIndices.push_back(vertexIndex[2]-1);
                uvIndices    .push_back(uvIndex[0]-1);
                uvIndices    .push_back(uvIndex[1]-1);
                uvIndices    .push_back(uvIndex[2]-1);
                normalIndices.push_back(normalIndex[0]-1);
                normalIndices.push_back(normalIndex[1]-1);
                normalIndices.push_back(normalIndex[2]-1);

        }


    }

    return true;
}

