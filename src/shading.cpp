#include "shading.h"

Material createMaterial(ColorRGB diffuse, ColorRGB specular, float shininess){
    Material myMaterial;

    myMaterial.diffuse = diffuse;
    myMaterial.specular = specular;
    myMaterial.shininess = shininess;

    return myMaterial;
};