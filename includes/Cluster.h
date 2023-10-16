#pragma once

#ifndef CLUSTER_H
#define CLUSTER_H

#include "Libs.h"

class Cluster
{
private:
	std::vector<class Particle> particles;
	int nb_particle;
	glm::vec4 color;


public:
	Cluster(int nb_particle);
	Cluster(int nb_particle, glm::vec4 color);
	~Cluster() {}

// Setter
	void setColor(glm::vec4 color);

// Getter
	glm::vec4 getColor();
	int getNbParticle();

// Cluster rule
	void rule(Cluster cluster, float gravity, float dt);
	void update(float dt);

// Get particle list (position + color)
	std::vector<glm::vec4> getParticles();
};
#endif // !CLUSTER_H
