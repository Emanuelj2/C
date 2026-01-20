#ifndef PHYSICS_H
#define PHYSICS_H

#include "Aircraft.h"

class Physics
{
	public:
		Physics();
		void update(AircraftState& aircraft, const Controls& controls, double dt);
	private:
		
		double mass;		//kg
		double wingArea;	//m^2
		double maxThrust;	//N
		
		double rho;	//air density
		double g;	//gravity
}

#endif
