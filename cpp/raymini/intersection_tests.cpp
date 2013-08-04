#include <gtest/gtest.h>
#include "Ray.h"

TEST(Ray_intersect, ParalellRay) {
    Ray r0 = Ray(Vec3Df(0.0, 0.0, 0.0), Vec3Df(0.0, 1.0, -1.0));
    Vec3Df v0 = Vec3Df(1.0, 0.0, 0.0);
    Vec3Df v1 = Vec3Df(0.0, 1.0, 0.0);
    Vec3Df v2 = Vec3Df(0.0, 0.0, 1.0);
    Vec3Df intersectionPoint;
    ASSERT_FALSE(r0.intersect(v0, v1, v2, intersectionPoint));

    Ray r1 = Ray(Vec3Df(0.0, 0.0, 0.0), Vec3Df(1.0, 1.0, 0.0));
    Vec3Df v4 = Vec3Df(1.0, 0.0, 2.0);
    Vec3Df v5 = Vec3Df(0.0, 1.0, 2.0);
    Vec3Df v6 = Vec3Df(0.0, 0.0, 2.0);
    ASSERT_FALSE(r1.intersect(v4, v5, v6, intersectionPoint));
}

TEST(Ray_intersect, IntersectionInTheWrongDirection) {

    Vec3Df v0 = Vec3Df(0.0, 0.0, 0.0);
    Vec3Df v1 = Vec3Df(1.0, 0.0, 0.0);
    Vec3Df v2 = Vec3Df(0.0, 1.0, 0.0);
    Vec3Df intersectionPoint0, intersectionPoint1, intersectionPoint2;

    Vec3Df expectedIntersectionPoint0 = Vec3Df(-1.0, -1.0, 0.0);
    Ray r0 = Ray(Vec3Df(0.0, 0.0, 1.0), Vec3Df(1.0, 1.0, 1.0));
    ASSERT_FALSE(r0.intersect(v0, v1, v2, intersectionPoint0));
    ASSERT_EQ(expectedIntersectionPoint0, intersectionPoint0);

    Vec3Df expectedIntersectionPoint1 = Vec3Df(0.0, 0.0, 0.0);
    Ray r1 = Ray(Vec3Df(0.0, 0.0, 1.0), Vec3Df(0.0, 0.0, 1.0));
    ASSERT_FALSE(r1.intersect(v0, v1, v2, intersectionPoint1));
    ASSERT_EQ(expectedIntersectionPoint1, intersectionPoint1);

    Vec3Df expectedIntersectionPoint2 = Vec3Df(0.5, 0.5, 0.0);
    Ray r2 = Ray(Vec3Df(0.0, 0.0, 1.0), Vec3Df(-0.5, -0.5, 1.0));
    ASSERT_FALSE(r2.intersect(v0, v1, v2, intersectionPoint2));
    ASSERT_EQ(expectedIntersectionPoint2, intersectionPoint2);
}

TEST(Ray_intersect, IntersectionPointOutsideTheTriangle) {
    Vec3Df v0 = Vec3Df(0.0, 0.0, 0.0);
    Vec3Df v1 = Vec3Df(0.0, 1.0, 0.0);
    Vec3Df v2 = Vec3Df(1.0, 0.0, 0.0);

    Ray r0 = Ray(Vec3Df(0.0, 0.0, 1.0), Vec3Df(1.0, 1.0, -1.0));
    Vec3Df intersectionPoint0;
    Vec3Df expectedIntersectionPoint0 = Vec3Df(1.0, 1.0, 0.0);
    ASSERT_FALSE(r0.intersect(v0, v1, v2, intersectionPoint0));
    ASSERT_EQ(expectedIntersectionPoint0, intersectionPoint0);
}

TEST(Ray_intersect, IntersectionPointInsideTheTriangle) {
    Vec3Df v0 = Vec3Df(0.0, 0.0, 0.0);
    Vec3Df v1 = Vec3Df(0.0, 1.0, 0.0);
    Vec3Df v2 = Vec3Df(1.0, 0.0, 0.0);

    Ray r0 = Ray(Vec3Df(0.0, 0.0, 1.0), Vec3Df(0.5, 0.5, -1.0));
    Ray r1 = Ray(Vec3Df(0.0, 0.0, 1.0), Vec3Df(1.0, 0.0, -1.0));
    Ray r2 = Ray(Vec3Df(0.0, 0.0, 1.0), Vec3Df(0.25, 0.25, -0.5));

    Vec3Df intersectionPoint0, intersectionPoint1, intersectionPoint2;
    Vec3Df expectedIntersectionPoint0 = Vec3Df(0.5, 0.5, 0.0);
    ASSERT_TRUE(r0.intersect(v0, v1, v2, intersectionPoint0));
    ASSERT_TRUE(r1.intersect(v0, v1, v2, intersectionPoint1));
    ASSERT_TRUE(r2.intersect(v0, v1, v2, intersectionPoint2));

    ASSERT_EQ(expectedIntersectionPoint0, intersectionPoint0);
    ASSERT_EQ(expectedIntersectionPoint0, intersectionPoint2);

}

TEST(Ray_intersect, VerticeIntersection) {
    Ray r = Ray(Vec3Df(0.0, 0.0, 0.0), Vec3Df(1.0, 0.0, 0.0));
    Vec3Df v0 = Vec3Df(1.0, 0.0, 0.0);
    Vec3Df v1 = Vec3Df(0.0, 1.0, 0.0);
    Vec3Df v2 = Vec3Df(0.0, 0.0, 1.0);
    Vec3Df intersectionPoint;
    ASSERT_TRUE(r.intersect(v0, v1, v2, intersectionPoint));
}

TEST(Ray_intersect, EdgeIntersection) {
    Ray r = Ray(Vec3Df(0.0, 0.0, 0.0), Vec3Df(0.5, 0.5, 0.0));
    Vec3Df v0 = Vec3Df(1.0, 0.0, 0.0);
    Vec3Df v1 = Vec3Df(0.0, 1.0, 0.0);
    Vec3Df v2 = Vec3Df(0.0, 0.0, 1.0);
    Vec3Df intersectionPoint;
    ASSERT_TRUE(r.intersect(v0, v1, v2, intersectionPoint));
}

TEST(Ray_intersect_mesh, Intersection) {
    Vec3Df v0 = Vec3Df(1.95251, 1.95251, 0.0);
    Vec3Df v1 = Vec3Df(-1.95251, 1.95251, 0.0);
    Vec3Df v2 = Vec3Df(-1.95251, -1.95251, 0.0);
    Ray r0 = Ray(Vec3Df(0.0, 0.0, 7.94428), Vec3Df(0.0, 0.0, -1.0));
    Ray r1 = Ray(Vec3Df(0.0, 0.0, 7.94428), Vec3Df(0.65456, 0.427981, -0.623204));
    Ray r2 = Ray(Vec3Df(0.0, 0.0, 7.94428), Vec3Df(0.633646, -0.11948, -0.764341));
    Vec3Df intersectionPoint;
    ASSERT_TRUE(r0.intersect(v0, v1, v2, intersectionPoint));
    ASSERT_TRUE(r1.intersect(v0, v1, v2, intersectionPoint));
    ASSERT_FALSE(r2.intersect(v0, v1, v2, intersectionPoint));

}
