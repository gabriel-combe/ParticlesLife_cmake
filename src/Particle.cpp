#include "Particle.h"

Particle::Particle() {
	this->position = glm::linearRand(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	this->velocity = glm::linearRand(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f));
	this->acceleration = glm::linearRand(glm::vec3(-0.05f, -0.05f, -0.05f), glm::vec3(0.05f, 0.05f, 0.05f));
}

Particle::Particle(glm::vec3 position) {
	this->position = position;
	this->velocity = glm::linearRand(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f));
	this->acceleration = glm::linearRand(glm::vec3(-0.05f, -0.05f, -0.05f), glm::vec3(0.05f, 0.05f, 0.05f));
}

Particle::Particle(glm::vec3 velocity, glm::vec3 acceleration) {
	this->position = glm::linearRand(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	this->velocity = velocity;
	this->acceleration = acceleration;
}

Particle::Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration) {
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
}

void Particle::setPosition(glm::vec3 pos) { this->position = pos; }

void Particle::setVelocity(glm::vec3 vel) { this->velocity = vel; }

void Particle::setAcceleration(glm::vec3 acc) { this->acceleration = acc; }

glm::vec3 Particle::getPosition() { return this->position; }

glm::vec3 Particle::getVelocity() { return this->velocity; }

glm::vec3 Particle::getAcceleration() { return this->acceleration; }

void Particle::update(float dt) {
	this->velocity += this->acceleration * dt;
	this->position += 0.5f * this->acceleration * dt * dt + this->velocity * dt;
}

void Particle::reverseVelX(float force) { this->velocity.x *= -force; }

void Particle::reverseVelY(float force) { this->velocity.y *= -force; }

void Particle::reverseVelZ(float force) { this->velocity.z *= -force; }

void Particle::remapX(float borne) {
	if ((int)trunc(this->position.x / borne) % 2) {
		if (this->position.x < -borne)
			this->position.x = borne + fmod(this->position.x, borne);
		else
			this->position.x = fmod(this->position.x, borne) - borne;
	}
	else
		this->position.x = fmod(this->position.x, borne);
}

void Particle::remapY(float borne) {
	if ((int)trunc(this->position.y / borne) % 2) {
		if (this->position.y < -borne)
			this->position.y = borne + fmod(this->position.y, borne);
		else
			this->position.y = fmod(this->position.y, borne) - borne;
	}
	else
		this->position.y = fmod(this->position.y, borne);
}

void Particle::remapZ(float borne) {
	if ((int)trunc(this->position.z / borne) % 2) {
		if (this->position.z < -borne)
			this->position.z = borne + fmod(this->position.z, borne);
		else
			this->position.z = fmod(this->position.z, borne) - borne;
	}
	else
		this->position.z = fmod(this->position.z, borne);
}

void Particle::repelX(float borne) {
	this->position.x -= 2.0f * (this->position.x - borne);
}

void Particle::repelY(float borne) {
	this->position.y -= 2.0f * (this->position.y - borne);
}

void Particle::repelZ(float borne) {
	this->position.z -= 2.0f * (this->position.z - borne);
}