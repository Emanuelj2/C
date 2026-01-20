#include "Physics.h"
#include <cmath.h>


Physics::Physics(): mass(1000.0), wingArea(16.0), maxThrust(5000.0), rho(1.225), g(9.81)
{
}


void Physics::update(Aircraft& a, const Controls& c, double dt)
{
	//calc angle of attack
	double aoa = a.pitch - atan2(a.vz, a.vx);

	//arodynamic coefficients
	double Cl = 0.3 + 4.5 * aoa;
	double Cd = 0.02 + Cl * Cl * 0.05;

	//calc airspeed
	double V = sqrt(a.vx * a.vx + a.vz * a.vz);

	//calc forces
	double Lift = 0.5 * rho * V * V * wingArea * Cl;
    	double Drag = 0.5 * rho * V * V * wingArea * Cd;
    	double Thrust = c.throttle * maxThrust;

    	// Net forces
    	double fx = Thrust - Drag;
    	double fz = Lift - mass * g;

    	// Update velocities
    	a.vx += (fx / mass) * dt;
    	a.vz += (fz / mass) * dt;

    	// Update position
    	a.x += a.vx * dt;
    	a.z += a.vz * dt;

    	// Update flight data
    	a.altitude = a.z;
    	a.airspeed = V;

    	// Update pitch (simplified control)
    	a.pitchRate = c.elevator * 0.5;
    	a.pitch += a.pitchRate * dt;

}
