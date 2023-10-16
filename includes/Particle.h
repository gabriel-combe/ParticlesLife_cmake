#pragma once

#ifndef PARTICLE_H
#define PARTICLE_H

#include "Libs.h"

class Particle
{
private:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;


public:
// Constructor/Destructor
	Particle();
	Particle(glm::vec3 position);
	Particle(glm::vec3 velocity, glm::vec3 acceleration);
	Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration);
	~Particle() {}

// Setters
	void setPosition(glm::vec3 pos);
	void setVelocity(glm::vec3 vel);
	void setAcceleration(glm::vec3 acc);

// Getters
	glm::vec3 getPosition();
	glm::vec3 getVelocity();
	glm::vec3 getAcceleration();

// Update
	void update(float dt);

// Utils
	void reverseVelX(float force);
	void reverseVelY(float force);
	void reverseVelZ(float force);
	void remapX(float borne);
	void remapY(float borne);
	void remapZ(float borne);
	void repelX(float borne);
	void repelY(float borne);
	void repelZ(float borne);
};
#endif // !PARTICLE_H
