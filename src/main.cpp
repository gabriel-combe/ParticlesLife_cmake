#include "Sandbox.h"

int main() {

	// Create a Particle sandbox
	Sandbox sandbox(
		"Particle sandbox",
		1920, 1080,
		3, 3,
		"#version 330",
		true);
	
	// Render Loop
	while(!sandbox.getWindowShouldClose()) {
		// Update
		sandbox.update();

		// Render Particles
		sandbox.render();
	}

	return 0;
}