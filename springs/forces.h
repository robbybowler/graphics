// force.h
// This file contains definitions for the Force classes.
// All forces derive from the abstract base class Force.
//
#ifndef FORCE
#define FORCE

#include "particle.h"

enum FORCE_TYPE { SPRING_FORCE, GRAVITY_FORCE, DRAG_FORCE };

class Particle;


//
// Force class, the base class
//
class Force
{
public:
	virtual void Apply()=0;
	virtual FORCE_TYPE Type()=0;
};

//
// SpringForce class
//
class SpringForce : public Force
{
public:
	SpringForce(Particle* p1, Particle *p2, double spring_constant, double damping_constant,double red, double green, double blue, double rest_length=0);
	SpringForce(Particle* p1, Particle *p2, double spring_constant, double damping_constant, double rest_length = 0);

	virtual void Apply();
	virtual FORCE_TYPE Type();

	//void SetColor(double red, double green,double blue);
	double GetRed() { return mRed; }
	double GetGreen() { return mGreen; }
	double GetBlue() { return mBlue; }



	Particle* GetParticle1();
	Particle* GetParticle2();

private:
	Particle* p1;
	Particle* p2;
	double rest_length;
	double spring_constant;
	double damping_constant;
	double mRed, mGreen, mBlue;
};

//
// GravityForce class
//
class GravityForce : public Force
{
public:
	GravityForce(double gravity[DIM], ParticleSystem * PS);
	
	virtual void Apply();
	virtual FORCE_TYPE Type();

private:
	double gravity[DIM];
	ParticleSystem * PS;
};

//
// DragForce class
//
class DragForce : public Force
{
public:
	DragForce(double friction_temp, ParticleSystem * PS);
	
	virtual void Apply();
	virtual FORCE_TYPE Type();

private:
	double friction;
	ParticleSystem * PS;
};

#endif
