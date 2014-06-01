// *********************************************************
// Object Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <iostream>
#include <vector>

#include "mesh.h"
#include "material.h"
#include "bounding_box.h"

class Object {
public:
    inline Object () {}
    inline Object (const Mesh & mesh, const Material & mat) :mesh (mesh), mat (mat) {
        updateBoundingBox ();
    }
    virtual ~Object () {}

    inline const Mesh & getMesh () const { return mesh; }
    inline Mesh & getMesh () { return mesh; }

    inline const Material & getMaterial () const { return mat; }
    inline Material & getMaterial () { return mat; }

    inline const BoundingBox & getBoundingBox () const { return bbox; }
    void updateBoundingBox ();

private:
    Mesh mesh;
    Material mat;
    BoundingBox bbox;
};


#endif // OBJECT3D_H
