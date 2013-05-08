// *********************************************************
// Ray Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Ray.h"

using namespace std;

static const unsigned int NUMDIM = 3, RIGHT = 0, LEFT = 1, MIDDLE = 2;

bool Ray::intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const {
    const Vec3Df & minBb = bbox.getMin ();
    const Vec3Df & maxBb = bbox.getMax ();
    bool inside = true;
    unsigned int  quadrant[NUMDIM];
    register unsigned int i;
    unsigned int whichPlane;
    Vec3Df maxT;
    Vec3Df candidatePlane;
    
    for (i=0; i<NUMDIM; i++)
        if (origin[i] < minBb[i]) {
            quadrant[i] = LEFT;
            candidatePlane[i] = minBb[i];
            inside = false;
        } else if (origin[i] > maxBb[i]) {
            quadrant[i] = RIGHT;
            candidatePlane[i] = maxBb[i];
            inside = false;
        } else	{
            quadrant[i] = MIDDLE;
        }

    if (inside)	{
        intersectionPoint = origin;
        return (true);
    }

    for (i = 0; i < NUMDIM; i++)
        if (quadrant[i] != MIDDLE && direction[i] !=0.)
            maxT[i] = (candidatePlane[i]-origin[i]) / direction[i];
        else
            maxT[i] = -1.;

    whichPlane = 0;
    for (i = 1; i < NUMDIM; i++)
        if (maxT[whichPlane] < maxT[i])
            whichPlane = i;

    if (maxT[whichPlane] < 0.) return (false);
    for (i = 0; i < NUMDIM; i++)
        if (whichPlane != i) {
            intersectionPoint[i] = origin[i] + maxT[whichPlane] *direction[i];
            if (intersectionPoint[i] < minBb[i] || intersectionPoint[i] > maxBb[i])
                return (false);
        } else {
            intersectionPoint[i] = candidatePlane[i];
        }
    return (true);			
}

bool Ray::intersect (const Vertex & v0, const Vertex & v1, const Vertex & v2, Vec3Df & intersectionPoint) const {
    // TODO(rmoutard) put inline.
    return intersect(v0.getPos(), v1.getPos(), v2.getPos(), intersectionPoint);
}

/**
 * @brief Ray::intersect
 * @param Vec3Df that corresponds to each point of the triangles.
 * @param intersectionPoint
 * @return true if there is an intersection between a ray and a triangle.
 */
bool Ray::intersect (const Vec3Df & v0, const Vec3Df & v1, const Vec3Df & v2, Vec3Df & intersectionPoint) const {
    // See more http://geomalgorithms.com/a06-_intersect-2.html
    // u and v are 2 vectors defined by the 3 vertex.
    Vec3Df u = v1 - v0;
    Vec3Df v = v2 - v0;
    // n is the normal of the plan P defined by u and v.
    Vec3Df n = Vec3Df::crossProduct(u,v);

    if(Vec3Df::dotProduct(n, direction) == 0){
        // The plane induced by the triangle is parallel to the ray.
        return false;
    } else {
        // P_i is the intersection point between the plane induced by the triangle and the ray.
        // r_i the coordinate induced by the base of the ray.
        float r_i = Vec3Df::dotProduct(n, v0 - origin) / Vec3Df::dotProduct(n, direction);
        // P_i intersection point between the ray and the plane.
        Vec3Df P_i = origin + r_i*direction;
        intersectionPoint = P_i; // copy operator
        if(r_i < 0) {
            // The intersection is behind the origin.
            return false;
        } else {
            Vec3Df w = P_i - v0;
            // s_i and t_i are coordinates of P_i in the base u, v.
            float denominator = Vec3Df::dotProduct(u, v)*Vec3Df::dotProduct(u, v) - Vec3Df::dotProduct(u, u)*Vec3Df::dotProduct(v, v);
            float s_i = (Vec3Df::dotProduct(u, v)*Vec3Df::dotProduct(w, v) - Vec3Df::dotProduct(v, v)*Vec3Df::dotProduct(w, u)) / denominator;
            float t_i = (Vec3Df::dotProduct(u, v)*Vec3Df::dotProduct(w, u) - Vec3Df::dotProduct(u, u)*Vec3Df::dotProduct(w, v)) / denominator;
            // P_i is in the triangle if it's coordinates in the base induced by the triangle verify:
            return (0 <= s_i && 0 <= t_i && 0 <= s_i + t_i && s_i + t_i <= 1);
        }
    }
    return false;
}

bool Ray::intersect (const Mesh & mesh, Vec3Df & intersectionPoint) const {
    Vec3Df closestIntersectionPoint, tempIntersectionPoint;
    int min_distance=-1, temp_distance;
    Vertex a, b, c;
    for(unsigned int i = 0; i < mesh.getTriangles().size(); i++) {
        Triangle t = mesh.getTriangles()[i];
        // TODO(rmoutard): is it better to have a temp vector?
        a = mesh.getVertices()[t.getVertex(0)];
        b = mesh.getVertices()[t.getVertex(1)];
        c = mesh.getVertices()[t.getVertex(2)];

        if(intersect(a, b, c, tempIntersectionPoint)) {
            Vec3Df distance = tempIntersectionPoint - origin;
            temp_distance = distance.getSquaredLength();
            if(min_distance == -1 || min_distance > temp_distance) {
                min_distance = temp_distance;
                closestIntersectionPoint = tempIntersectionPoint;
            }
        }
    }
    return (min_distance != -1);
};

bool Ray::intersect(const Object &object, Vec3Df &intersectionPoint) const {
    return intersect(object.getMesh(), intersectionPoint);
};

bool Ray::intersect(const Scene *scene, Vec3Df &intersectionPoint) {
    Object object;
    Vec3Df closestIntersectionPoint, tempIntersectionPoint;
    int min_distance = -1, temp_distance;

    for(unsigned int i = 0; i < scene->getObjects().size(); i++){
        object = scene->getObjects()[i];
        if(intersect(object, tempIntersectionPoint)) {
            Vec3Df distance = tempIntersectionPoint - origin;
            temp_distance = distance.getSquaredLength();
            if(min_distance == -1 || min_distance > temp_distance) {
                min_distance = temp_distance;
                closestIntersectionPoint = tempIntersectionPoint;
            }
        }
    }
    intersectionPoint = closestIntersectionPoint;
    return (min_distance!=-1);
};
