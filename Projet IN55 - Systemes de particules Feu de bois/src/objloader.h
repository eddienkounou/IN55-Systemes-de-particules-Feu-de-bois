#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <vector>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>

using namespace std;

class Objloader
{
public:
    Objloader();
    bool loadObj(vector < glm::vec3 > & temp_vertices,vector <unsigned int> & vertexIndices);

};

#endif // OBJLOADER_H
