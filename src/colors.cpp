#include "colors.h"

// Construit la couleur (r, g, b)
ColorRGB createColor(float r, float g, float b){
    ColorRGB color;

    color.r = r;
    color.g = g;
    color.b = b;

    return color;
};

// Addition, soustraction et multiplication des couleurs C1 et C2
ColorRGB addColors(ColorRGB c1, ColorRGB c2){
    return createColor(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b);
};

ColorRGB subColors(ColorRGB c1, ColorRGB c2){
    return createColor(c1.r-c2.r, c1.g-c2.g, c1.b-c2.b);
};

ColorRGB multColors(ColorRGB c1, ColorRGB c2){
    return createColor(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b);
};

// Multiplication et division d une couleur C par un scalaire a
ColorRGB multColor(ColorRGB c, float a){
    return createColor(c.r*a, c.g*a, c.b*a);
};

ColorRGB divColor(ColorRGB c, float a){
    return createColor(c.r/a, c.g/a, c.b/a);
};

ColorRGB clampColor(ColorRGB c){
    if(c.r>1) c.r = 1;
    else if (c.r < 0) c.r=0;
    
    if(c.g>1) c.g = 1;
    else if (c.g < 0) c.g=0;
    
    if(c.b>1) c.b = 1;
    else if (c.b < 0) c.b=0;

    return c;
};