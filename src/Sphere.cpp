//
// Created by MSI-PC on 2021/12/1.
//

#include "Sphere.h"
#include "Utils.hpp"


Sphere::Sphere(const Point3 &center, double radius, std::shared_ptr<Material> material)
        : center_(center), radius_(radius), material_(material) {
}

bool Sphere::hit(const Ray &ray, double distanceMin, double distanceMax, HitRecord &hitRecord) const {
    auto centerToOrigin = ray.origin() - center_;
    auto a = ray.direction().lengthSquared();
    auto halfB = dot(ray.direction(), centerToOrigin);
    auto c = centerToOrigin.lengthSquared() - radius_ * radius_;
    auto discriminant = halfB * halfB - a * c;

    if (discriminant > 0) {
        auto sqrtD = sqrt(discriminant);
        auto distance = (-halfB - sqrtD) / a;

        if (distance > distanceMin && distance < distanceMax) {
            hitRecord.distance = distance;
            hitRecord.point = ray.at(distance);
            auto normal = (hitRecord.point - center_).normalize();
            hitRecord.setFaceNormal(ray, normal);
            hitRecord.material = material_;
            return true;
        }

        distance = (-halfB + sqrtD) / a;
        if (distance > distanceMin && distance < distanceMax) {
            hitRecord.distance = distance;
            hitRecord.point = ray.at(distance);
            auto normal = (hitRecord.point - center_).normalize();
            hitRecord.setFaceNormal(ray, normal);
            hitRecord.material = material_;
            return true;
        }
    }

    return false;
}

Point3 Sphere::randomPointInSphere() const {
    return Utils::randomUnitVector3() * Utils::randomDouble(0, radius_) + center_;
}