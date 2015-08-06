#pragma once

struct Particle {
	explicit Particle(float radius, float duration)
		: radius(radius), d(1.0f) {}

	float radius, alpha, d;
};
