#include "Cluster.h"

Cluster::Cluster(int nb_particle, glm::vec4 color) {
	this->nb_particle = nb_particle;
	this->color = color;

	for (int i = 0; i < nb_particle; i++)
		this->particles.push_back(Particle(glm::vec3(0.0f), glm::vec3(0.0f)));
}

Cluster::Cluster(int nb_particle) {
	this->nb_particle = nb_particle;
	this->color = glm::vec4(glm::linearRand(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f)), 1.0f);

	for (int i = 0; i < nb_particle; i++)
		this->particles.push_back(Particle(glm::vec3(0.0f), glm::vec3(0.0f)));
}

void Cluster::setColor(glm::vec4 color) { this->color = color; }

glm::vec4 Cluster::getColor() { return this->color; }

int Cluster::getNbParticle() { return this->nb_particle; }

void Cluster::rule(Cluster cluster, float gravity, float dt) {
	for (int i = 0; i < this->particles.size(); i++) {
		glm::vec3 force = glm::vec3(0.0f);

		for (int j = 0; j < cluster.particles.size(); j++) {
			float dist = glm::distance(this->particles[i].getPosition(), cluster.particles[j].getPosition());
			if(dist > 0.0f && dist < 10.0f)
				force += (gravity / dist) * (this->particles[i].getPosition() - cluster.particles[j].getPosition());
		}

		this->particles[i].setVelocity((this->particles[i].getVelocity() + force) * 0.5f);
		this->particles[i].setPosition(this->particles[i].getPosition() + this->particles[i].getVelocity() * dt);

		if (this->particles[i].getPosition().x <= -2.0f) {
			this->particles[i].repelX(-2.0f);
			this->particles[i].reverseVelX(2.0f);
		}
		if (this->particles[i].getPosition().x >= 2.0f) {
			this->particles[i].repelX(2.0f);
			this->particles[i].reverseVelX(2.0f);
		}

		if (this->particles[i].getPosition().y <= -2.0f) {
			this->particles[i].repelY(-2.0f);
			this->particles[i].reverseVelY(2.0f);
		}
		if (this->particles[i].getPosition().y >= 2.0f) {
			this->particles[i].repelY(2.0f);
			this->particles[i].reverseVelY(2.0f);
		}

		if (this->particles[i].getPosition().z <= -2.0f) {
			this->particles[i].repelZ(-2.0f);
			this->particles[i].reverseVelZ(2.0f);
		}
		if (this->particles[i].getPosition().z >= 2.0f) {
			this->particles[i].repelZ(2.0f);
			this->particles[i].reverseVelZ(2.0f);
		}
	}

	for (auto& particle : this->particles)
		particle.setPosition(glm::clamp(particle.getPosition(), glm::vec3(-2.0f), glm::vec3(2.0f)));
}

void Cluster::update(float dt) {
	for (int i = 0; i < this->particles.size(); i++)
		this->particles[i].update(dt);
}

std::vector<glm::vec4> Cluster::getParticles() {
	std::vector<glm::vec4> vertices;
	for (int i = 0; i < this->particles.size(); i++) {
		vertices.push_back(glm::vec4(this->particles[i].getPosition(), 1.0f));
		vertices.push_back(this->color);
	}

	return vertices;
}