#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "geometry.h"
#include "colors.h"
#include "shape.h"
#include "shading.h"

typedef struct Ray
{
    Point3D origine;
    Vector3D direction;
} Ray;

typedef struct Intersection
{
    Point3D position;
    Material couleur;
    Vector3D normale;
} Intersection;

typedef struct Light{
    Point3D position;
    ColorRGB couleur;
} Light;

typedef struct Scene
{
    Sphere mesSpheres[5];
    int nbSphere;
    Light mesLights[10];
    int nbLight;
} Scene;


Ray createRay(Point3D origine, Vector3D direction);

int intersectsSphere(Ray r, Sphere s, Intersection* intersection, float* t);

Scene createScene();

void addSphereToScene(Scene* scene, Sphere s);

void addLightToScene(Scene* scene, Light l);

int throwRayThroughScene(Ray r, Scene scene, Intersection* intersectionNearest);

void simpleRaytracing(const Scene* scene, SDL_Surface* framebuffer);

Light createLight(Point3D position, ColorRGB couleur);

void lambertRaytracing(Scene scene, SDL_Surface* framebuffer);

#endif