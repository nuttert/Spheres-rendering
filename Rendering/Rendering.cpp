//
//  Rendering.cpp
//  Rendering
//
//  Created by vlad on 30.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#include "Rendering.hpp"
#include <cmath>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include "Errors/Errors.hpp"
using Render = Graphic::Render;
using Vec3f = Graphic::Vec3f;
using Geometry = Graphic::Geometry;
using Sphere = Geometry::Sphere;
//Vector
auto Vec3f:: operator[](const short index)const{
    assert(index<3);
    switch(index){
        case 0:return x;
        case 1:return y;
        case 2:return z;
        default:return 0.f;
    }
}

auto Vec3f::operator*(const Vec3f& rhs)const{
    auto mult =
    x*rhs.x+
    y*rhs.y+
    z*rhs.z;
    return mult;
}

auto Vec3f::operator-(const Vec3f& rhs)const{
    Vec3f subtraction {x-rhs.x,y-rhs.y,z-rhs.z};
    return subtraction;
}

auto Vec3f::operator+(const Vec3f& rhs)const{
    Vec3f sum {x+rhs.x,y+rhs.y,z+rhs.z};
    return sum;
}
auto Vec3f::operator/(const float& number)const{
    return Vec3f{x/number,y/number,z/number};
}
auto Vec3f::norm()const{
    return sqrt(x*x+y*y+z*z);
}

auto Vec3f::normSqure()const{
    return x*x+y*y+z*z;
}

auto Vec3f::normilizedVec()const{
    return *this/norm();
}
//_______________________






//Rendering
Render::Render(const size_t width,const size_t height):
pixels(height,Vector(width)),
width(width),
height(height){}

auto Render::colorForArea(const Sphere& sphere,const Vec3f& direction,const Vec3f& origin){
    if(sphere.interactionWithSphere(direction, origin))
        return Vec3f{0.4, 0.4, 0.3};
    return Vec3f{0.2, 0.7, 0.8};
}

void  Graphic::Render::defaultFill(const Sphere& sphere){
    for(size_t i = 0;i<height;++i)
        for(size_t j = 0;j<width;++j){
            auto origin = Vec3f{0,0,0};
            float x =  (2*(j + 0.5)/(float)width  - 1)*(float)width/height;
            float y = -(2*(i + 0.5)/(float)height  - 1);
            auto direction = Vec3f{x, y, -1}.normilizedVec();
            pixels[i][j] = colorForArea(sphere, direction, origin);
        }
}

void  Render::createFile(const std::string& name){
    std::ofstream file;
    file.open(name+".ppm");
    if(!file.is_open()){
        fileError(fileNotExists);
        return;
    }
    file << "P6\n"<< width << " "<< height << "\n"<<pallete<<"\n";
    for(size_t i = 0;i<height;++i)
        for(size_t j = 0;j<width;++j)
            for(size_t color = 0;color<colorDimension;++color){
                auto pixel = std::max(0.f,std::min(1.0f,pixels[i][j][color]));
                file << (char)(pallete*pixel);
            }
    file.close();
    Utilities::openFile(name);
}




//_______________________




//Utilities
void  Utilities::openFile(std::string file){
    if(fork()==0){
        const char* command = "open";
        file += ".ppm";
        if(execlp(command,command,file.c_str(),NULL) == -1)fileError(fileNotExists);
        exit(1);
    }
}
//_______________________




//Geometry
bool Sphere::interactionWithSphere(const Vec3f& direction,const Vec3f& origin)const{
    auto fromOriginToCenter = origin-center;
    auto distance = fromOriginToCenter.norm();
    auto currentCos = std::abs((direction*fromOriginToCenter))/(distance*direction.norm());
    auto minSin = radius/distance;
    auto minCos = sqrt(1-minSin*minSin);
    return currentCos < minCos;
}
//_______________________


