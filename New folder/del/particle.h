// particle.h
// Bart Stander
// January, 2002
// For CS 3600 projects.
// Taken from SIGGRAPH course notes on physically based modeling

#ifndef PARTICLE
#define PARTICLE

#include <vector>
class Force;

using namespace std;

const int DIM = 2;
const int MAX_PARTICLES = 1000;

class Particle
{
public:
	Particle();
	Particle(double pos_temp[DIM], double dir_temp[DIM], double r_temp, bool anchored_temp);
	Particle(double x, double y, double xDir, double yDir, double r_temp, bool anchored_temp);

	// accessor methods:
	double GetRadius() { return r; }
	double GetMass() { return m; }
	bool GetAnchored() { return anchored; }

	void GetPosition(double pos_temp[DIM]);
	void GetDirection(double dir_temp[DIM]);
	void GetForce(double f_temp[DIM]);
	void SetPosition(double pos_temp[DIM]);
	void SetDirection(double dir_temp[DIM]);
	void SetForce(double f_temp[DIM]);

	double GetPositionx() { return pos[0]; }
	double GetDirectionx() { return dir[0]; }
	double GetForcex() { return f[0]; }
	void SetPositionx(double x) {pos[0] = x;}
	void SetDirectionx(double x) {dir[0] = x;}
	void SetForcex(double x) {f[0] = x;}

	double GetPositiony() { return pos[1]; }
	double GetDirectiony() { return dir[1]; }
	double GetForcey() { return f[1]; }
	void SetPositiony(double y) {pos[1] = y;}
	void SetDirectiony(double y) {dir[1] = y;}
	void SetForcey(double y) {f[1] = y;}

private:
	double pos[DIM]; // position
	double dir[DIM]; // velocity
	double f[DIM]; // force
	double r; // radius
	double m; // mass
	bool anchored; // fixed or moving?
};

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void AddParticle(Particle * p);
	int GetNumParticles();
	Particle * GetParticle(int i);

	void AddForce(Force * f);
	int GetNumForces();
	Force * GetForce(int i);

	// Methods for ODE solvers:
	int ParticleDims();
	void ParticleGetState(double * dst);
	void ParticleSetState(double * src);
	void ParticleGetDerivative(double * dst);
	void IncrementTime(double DeltaT);

private:
	void ClearForces();
	void ComputeForces();

	vector<Particle*> pArray;
	vector<Force*> fArray;
	double time;
};

void EulerStep(ParticleSystem & ps, double DeltaT);
void MidpointStep(ParticleSystem & ps, double DeltaT);
void RungeKuttaStep(ParticleSystem & ps, double DeltaT);

#endif

