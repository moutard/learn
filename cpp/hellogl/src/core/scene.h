// *********************************************************
// Scene Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>

#include "object3d.h"
#include "light.h"
#include "bounding_box.h"

class Scene {
public:
    static Scene * getInstance ();
    static void destroyInstance ();

    inline std::vector<Object> & getObjects () { return objects; }
    inline const std::vector<Object> & getObjects () const { return objects; }

    inline std::vector<Light> & getLights () { return lights; }
    inline const std::vector<Light> & getLights () const { return lights; }

    inline const BoundingBox & getBoundingBox () const { return bbox; }
    void updateBoundingBox ();

protected:
    Scene ();
    virtual ~Scene ();

private:
    void buildDefaultScene (bool HD);
    std::vector<Object> objects;
    std::vector<Light> lights;
    BoundingBox bbox;
};


#endif // SCENE_H
