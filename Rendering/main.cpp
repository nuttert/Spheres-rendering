//
//  main.cpp
//  Rendering
//
//  Created by vlad on 30.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <optional>
#include "Rendering.hpp"
using namespace Graphic;
using Sphere = Graphic::Geometry::Sphere;
const Vec3f Colors::background{(float)254/255, (float)156/255, (float)143/255};
const Vec3f Colors::redRubber{0.3, 0.1, 0.1};
const Vec3f Colors::orange{(float)254/255, (float)74/255, (float)73/255};
const Vec3f Colors::blue{(float)42/255, (float)183/255, (float)202/255};
const Vec3f Colors::yellow{(float)254/255, (float)215/255, (float)102/255};

int main(int argc, const char * argv[]) {
    Render engine(1024,768);
//    Geometry::Sphere sphere1{Vec3f{0, 3, -5}, 1,Material{Colors::redRubber}};
//    Geometry::Sphere sphere2{Vec3f{0, 0, -4}, 1,Material{Colors::blue}};
   

    Geometry::Sphere::Spheres spheres;
    spheres.push_back(Sphere(Vec3f(-3,    0,   -16), 2,Material{Colors::redRubber}));
    spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2, Material{Colors::blue}));
    spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, Material{Colors::yellow}));
    spheres.push_back(Sphere(Vec3f( 7,    5,   -18), 4, Material{Colors::orange}));
    engine.defaultFill(spheres);
    engine.createFile("myFile");
    std::cout << "Hello, World!\n";
    return 0;
}
