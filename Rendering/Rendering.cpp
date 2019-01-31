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
#include <optional>
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

auto Vec3f::operator*(const float& number)const{
    return Vec3f{x*number,y*number,z*number};
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

auto Vec3f::operator-()const{
    return Vec3f{-x,-y,-z};
}
//_______________________


//Geometry
auto Sphere::interactionWithSphere(const Vec3f& direction,const Vec3f& origin)const{
    auto fromOriginToCenter = origin-center;
    auto distance = fromOriginToCenter.norm();
    auto currentCos = std::abs((direction*fromOriginToCenter))/(distance*direction.norm());
    auto minSin = radius/distance;
    auto minCos = sqrt(1-minSin*minSin);
    auto distanceFromOriginToInterectionPoint = cosTheorem(distance, radius, currentCos);
    auto interactionPoint = direction.normilizedVec()*distanceFromOriginToInterectionPoint;
    auto normal = (fromOriginToCenter+interactionPoint).normilizedVec();
    struct Result{
        const Vec3f normal;
        const Vec3f interactionPoint;
        const float distance;
        const bool isInteraction;};
    return Result{
        std::move(normal),
        std::move(interactionPoint),
        std::move(distance),
        currentCos >= minCos};
}
//_______________________




//Rendering
Render::Render(const size_t width,const size_t height):
pixels(height,Vector(width)),
width(width),
height(height){}

auto Render::colorForArea(const Spheres& spheres,const Vec3f& direction,
                          const Vec3f& origin,Lightings lightings){
    auto nearlyDistance = std::numeric_limits<float>::max();
    const Material* pMaterial = nullptr;
    std::optional<Vec3f> point;
    std::optional<Vec3f> normal;
    for(const auto& sphere:spheres){
        auto [normalToPoint,interactionPoint,distance,isInteraction] = sphere.interactionWithSphere(direction, origin);
        if(isInteraction &&
           distance < nearlyDistance){
            nearlyDistance = distance;
            pMaterial = &sphere.material;
            point = std::move(interactionPoint);
            normal = std::move(normalToPoint);
        }
    }
    
    float lightIntensity = 0;
    for(const auto& light:lightings)
        if(point && normal){
            auto lightDirection = (light.position-*point).normilizedVec();
            lightIntensity += light.intensity*std::max(0.f,lightDirection * (*normal));
        }
    return   pMaterial ? pMaterial->color*lightIntensity : Colors::background;
}

void  Graphic::Render::defaultFill(const Spheres& spheres,Lightings lightings,const Vec3f& origin){
    for(size_t i = 0;i<height;++i)
        for(size_t j = 0;j<width;++j){
            float x =  (2*(j + 0.5)/(float)width  - 1)*(float)width/height;
            float y = -(2*(i + 0.5)/(float)height  - 1);
            auto direction = Vec3f{x, y, -1}.normilizedVec();
            pixels[i][j] = colorForArea(spheres, direction, origin,lightings);
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







