#include <SDL2/SDL.h>
#include "raytracer.h"
#include "sdl_tools.h"
#include <stdio.h>
#include <math.h>

Ray createRay(Point3D origine, Vector3D direction){
    Ray monR;
    monR.origine = origine;
    monR.direction = direction;
    return monR;
};

int intersectsSphere(Ray r, Sphere s, Intersection* intersection, float* t){
    float a, b, c;
    a = 1;
    Vector3D vecCO = createVectorFromPoints(s.centre, r.origine);
    b = 2*dot(vecCO, r.direction);
    c = dot(vecCO, vecCO)-s.rayon*s.rayon;

    float delta = b*b -4*a*c;
    if (delta<0)
    {
        return 0;
    } else {
        float t1, t2;
        t1 = (-b + sqrt(delta))/2*a;
        t2 = (-b - sqrt(delta))/2*a;

        if(t1<0 && t2 <0) return 0;
        if(t1<=0) *t = t2;
        if(t2<=0) *t = t1;
        else {
            if(t1<t2) *t = t1;
            else *t = t2;
        }

        //define intersection
        intersection->position = pointPlusVector(r.origine, multVector(r.direction, *t));
        intersection->couleur = s.couleur;

        Vector3D myVec = createVectorFromPoints(s.centre, intersection->position);
            intersection->normale = normalize(myVec);
        if(t1*t2<0){
            intersection->normale = multVector(myVec, -1);   
        }

        return 1;
    }    
};

Scene createScene(){
    Scene myScene;

    myScene.nbSphere = 0;
    myScene.nbSphere = 0;

    return myScene;
};

void addSphereToScene(Scene* scene, Sphere s){
    if(scene->nbSphere<5){
        scene->mesSpheres[scene->nbSphere]=s;
        scene->nbSphere+=1;
    } else {
        printf("Impossible d'ajouter la sphere a la scene !");
    }
};

void addLightToScene(Scene* scene, Light l){
    if(scene->nbSphere<10){
        scene->mesLights[scene->nbSphere]=l;
        scene->nbLight+=1;
    } else {
        printf("Impossible d'ajouter la lumiere a la scene !");
    }
};

int throwRayThroughScene(Ray r, Scene scene, Intersection* intersectionNearest){
    float t=-1;
    for(int i = 0; i<scene.nbSphere; i++){
        Intersection local;
        float tloc;

        if(intersectsSphere(r, scene.mesSpheres[i], &local, &tloc)){
            if(tloc<t || t<0){
                t=tloc;
                *intersectionNearest = local;
            }
        }
        
    }

    if(t>=0){
            // printf(" %f ",t);
        return 1;
    } else {
        return 0;
    }
};

void simpleRaytracing(const Scene* scene, SDL_Surface* framebuffer){
    Point3D origin = createPoint(0,0,0);
    for(int i = 0; i<framebuffer->w; i++){
        for(int j=0; j<framebuffer->h; j++){
            Point3D localPt =  createPoint(-1+2*((float)i/framebuffer->w), -(-1+2*((float)j/framebuffer->h)), -1);
            Vector3D localDir = createVectorFromPoints(origin, localPt);
            localDir = normalize(localDir);
            Ray localRay = createRay(origin, localDir);
            Intersection localIntersect;
            int intersect = throwRayThroughScene(localRay, *scene, &localIntersect);
            if(intersect!=0){
                int red = localIntersect.couleur.diffuse.r * 255;
                int green = localIntersect.couleur.diffuse.g * 255;
                int blue = localIntersect.couleur.diffuse.b * 255;
                unsigned int pixel = red<<16 | green<<8 | blue;
                putPixel(framebuffer, i, j, pixel);
            }
        }
    }
};

Light createLight(Point3D position, ColorRGB couleur){
    Light myLight;

    myLight.position = position;
    myLight.couleur = couleur;

    return myLight;
}

void lambertRaytracing(Scene scene, SDL_Surface* framebuffer){
    Point3D origin = createPoint(0,0,0);
    for(int i = 0; i<framebuffer->w; i++){
        for(int j=0; j<framebuffer->h; j++){
            Point3D localPt =  createPoint(-1+2*((float)i/framebuffer->w), -(-1+2*((float)j/framebuffer->h)), -1);
            Vector3D localDir = createVectorFromPoints(origin, localPt);
            localDir = normalize(localDir);
            Ray localRay = createRay(origin, localDir);
            Intersection localIntersect;
            int intersect = throwRayThroughScene(localRay, scene, &localIntersect);
            if(intersect!=0){
                ColorRGB newColor = createColor(0, 0, 0);
                for(int i = 0; i<10; i++){
                    Vector3D IL = createVectorFromPoints(localIntersect.position, scene.mesLights[i].position);
                    ColorRGB contrib = multColors(localIntersect.couleur.diffuse, multColor(scene.mesLights[i].couleur, dot(localIntersect.normale, normalize(IL))/dot(IL, IL)));

                    newColor = addColors(newColor, contrib);
                }

                newColor = clampColor(newColor);

                int red = newColor.r * 255;
                int green = newColor.g * 255;
                int blue = newColor.b * 255;
                unsigned int pixel = red<<16 | green<<8 | blue;
                putPixel(framebuffer, i, j, pixel);
            }
        }
    }
};