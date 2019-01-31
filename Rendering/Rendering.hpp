//
//  Rendering.hpp
//  Rendering
//
//  Created by vlad on 30.01.2019.
//  Copyright © 2019 vlad. All rights reserved.
//

#ifndef Rendering_hpp
#define Rendering_hpp

#include <stdio.h>
#include <vector>
#include <cmath>


namespace Utilities {
    void openFile(std::string file);
}



namespace Graphic{
    class Render;
    struct Vec3f{
        float x,y,z;
        Vec3f(float x,float y,float z):x(x),y(y),z(z){}
        Vec3f():x{0},y(0),z(0){}
        auto operator[](const short index)const;
        auto operator*(const Vec3f& rhs)const;
        auto operator-(const Vec3f& rhs)const;
        auto operator+(const Vec3f& rhs)const;
        auto operator/(const float& number)const;
        auto normilizedVec()const;
        auto norm()const;
        auto normSqure()const;
    };
    
    
    struct Material{
        Vec3f color;
    };
    
    
    class Geometry{
        Geometry() = default;
    public:
        struct Sphere{
            friend Geometry;
            friend Render;
            using Spheres = std::vector<Sphere>;
        private:
            Vec3f center;
            float radius;
            Material material;
        public:
            Sphere(const Vec3f& center,const float& radious,const Material& material):
            center(center),
            radius(radious),
            material(material){}
            
            Sphere(Vec3f&& center,float&& radious,Material&& material):
            center(center),
            radius(radious),
            material(material){}
            
            auto interactionWithSphere(const Vec3f& direction,const Vec3f& origin)const;
        };
        

    };
    
    
    
    class Render{
        using Vector = std::vector<Vec3f>;
        using Matrix = std::vector<Vector>;
        using Sphere = Geometry::Sphere;
        using Spheres = std::vector<Sphere>;
        const size_t pallete = 255;
        const uint8_t colorDimension = 3;
    public:
        Render(const size_t width,const size_t height);
        
        void defaultFill(const Spheres& spheres);
        void createFile(const std::string& name);
    private:
        auto colorForArea(const Spheres& spheres,const Vec3f& direction,const Vec3f& origin);
    private:
        float viewingAngle = M_PI/2;
        Matrix pixels;
        size_t width;
        size_t height;
    };
    
    
    struct Colors{
        Colors() = delete;
        static const Vec3f background;
        static const Vec3f redRubber;
        static const Vec3f orange;
        static const Vec3f blue;
        static const Vec3f yellow;
    };
    
}
#endif /* Rendering_hpp */
