// *********************************************************
// Scene Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Scene.h"
#include <iostream>

using namespace std;

static Scene * instance = NULL;

Scene * Scene::getInstance () {
    if (instance == NULL) {
        cout << "getInstance create a new scene. " << endl;
        instance = new Scene ();
    }
    return instance;
}

void Scene::destroyInstance () {
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

Scene::Scene () {
    buildDefaultScene (false);
    updateBoundingBox ();
}

Scene::~Scene () {
}

void Scene::updateBoundingBox () {
    if (objects.empty ())
        bbox = BoundingBox ();
    else {
        bbox = objects[0].getBoundingBox ();
        for (unsigned int i = 1; i < objects.size (); i++)
            bbox.extendTo (objects[i].getBoundingBox ());
    }
}

// Changer ce code pour créer des scènes originales
/**
 * @brief Scene::buildDefaultScene
 * @param HD : specify if the scene used HD mesh or not.
 *
 * Create a default scene using 2 objects:
 * - Ground : mesh + default Material
 * - Ram : mesh + specific Material to give him a specific color.
 *
 * Add one light.
 */
void Scene::buildDefaultScene (bool HD) {
    cout << "scene buildDefaultScene" << endl;

    // Load all the Mesh.
    Mesh groundMesh;
    if (HD)
        groundMesh.loadOFF ("models/ground_HD.off");
    else
        groundMesh.loadOFF ("models/ground.off");
    cout << "ground mesh loaded" << endl;

    // Create an Object using a Mesh and a Material.
    Material groundMat;
    Object ground (groundMesh, groundMat);    
    objects.push_back (ground);
    Mesh ramMesh;
    if (HD)
        ramMesh.loadOFF ("models/ram_HD.off");
    else
        ramMesh.loadOFF ("models/ram.off");
    cout << "ram mesh loaded" << endl;

    // Give a color to the Ram using a specific material.
    Material ramMat (1.f, 1.f, Vec3Df (1.f, .6f, .2f));
    Object ram (ramMesh, ramMat);
    objects.push_back (ram);

    // Add one light.
    Light l (Vec3Df (3.0f, 3.0f, 3.0f), Vec3Df (1.0f, 1.0f, 1.0f), 1.0f);
    lights.push_back (l);
}
