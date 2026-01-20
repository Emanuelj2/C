#ifndef AIRCRAFT_H
#define AIRCRAFT_H

struct AircraftState
{
	//position
	double x = 0.0;
	double z = 1000.0;	//100 meter altitude

	//velocity
	double vx = 50.0; 	//forward
	double vz = 0.0;

	//altitude
	double pitch = 0.0;
	double pitchRate = 0.0;

	//flight data
	double airspeed = 50.0;
	double altitude = 1000.0;

#endif
