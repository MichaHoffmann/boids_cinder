#pragma once

#include "Forces/Force.hpp"
#include "Boids/Boid.hpp"

class MaxVelocityForce : public Force
{

    float max_velocity;

public:

    explicit MaxVelocityForce ( float max_velocity );

    void actOnBoids ( std::vector<Boid>& boids ) override;
};

class BoundaryForce : public Force
{

    int left, right, up, down;
    float strength;

public:

    explicit BoundaryForce ( int left, int right, int up, int down, float strength );

    void actOnBoids ( std::vector<Boid>& boids ) override;
};

class ObstacleForce : public Force
{

    utility::vec_t position;
    float strength;

public:

    explicit ObstacleForce ( utility::vec_t position, float strength );

    void actOnBoids ( std::vector<Boid>& boids ) override;
};