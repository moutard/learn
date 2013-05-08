// *********************************************************
// Ray Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef RAY_H
#define RAY_H

#include <iostream>
#include <vector>

#include "Vec3D.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Object.h"
#include "Scene.h"
#include "BoundingBox.h"

class Ray {
public:
    inline Ray () {}
    inline Ray (const Vec3Df & origin, const Vec3Df & direction)
        : origin (origin), direction (direction) {}
    inline virtual ~Ray () {}

    inline const Vec3Df & getOrigin () const { return origin; }
    inline Vec3Df & getOrigin () { return origin; }
    inline const Vec3Df & getDirection () const { return direction; }
    inline Vec3Df & getDirection () { return direction; }

    bool intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const;
    bool intersect (const Vertex & v1, const Vertex & v2, const Vertex & v3, Vec3Df & intersectionPoint) const;
    bool intersect (const Vec3Df & v1, const Vec3Df & v2, const Vec3Df & v3, Vec3Df & intersectionPoint) const;
    bool intersect (const Mesh & mesh, Vec3Df & intersectionPoint) const;
    bool intersect (const Object & object, Vec3Df & intersectionPoint) const;
    bool intersect (const Scene * scene, Vec3Df & intersectionPoint);
private:
    Vec3Df origin;
    Vec3Df direction;
};


#endif // RAY_H
