#ifndef SHAPE_H
#define SHAPE_H

#include "geometry.h"
#include "colors.h"
#include "shading.h"

typedef struct Sphere
{
    Point3D centre;
    float rayon;
    Material couleur;
} Sphere ;

Sphere createSphere(Point3D centre, float rayon, Material couleur);

#endif