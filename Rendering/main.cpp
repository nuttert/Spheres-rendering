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

const Vec3f Colors::background{0.4, 0.4, 0.3};
const Vec3f Colors::redRubber{0.3, 0.1, 0.1};


int main(int argc, const char * argv[]) {
    Render engine(1024,768);
    Geometry::Sphere sphere{Vec3f{0, 3, -5}, 1,Material{Colors::redRubber}};
    
    engine.defaultFill(sphere);
    engine.createFile("myFile");
    std::cout << "Hello, World!\n";
    return 0;
}
