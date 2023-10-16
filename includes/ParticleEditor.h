#pragma once

#ifndef PARTICLEEDITOR_H
#define PARTICLEEDITOR_H

#include "Libs.h"

class ParticleEditor
{
private:
// Private Functions
	void show();

public:
// Constructor/Destructor
	ParticleEditor();
	~ParticleEditor();

// Functions
	void ParticleEditorInitialize();
	void ParticleEditorShow();
	void ParticleEditorShutdown();
};

#endif // !PARTICLEEDITOR_H
