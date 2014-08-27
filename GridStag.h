//GridStag.h

#ifndef _GRIDSTAG_H_
#define _GRIDSTAG_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include "Particles.h"
//using namespace boost::numeric::ublas;

#include "ParameterFLAGS.hpp"


class GridStag
{
public:
	int gridSizeVL;//grid Size Vertical line - physical
	int gridSizeHL; //grid Size Horizontal Lines - Physical
	double stepX ; //associated with gridSizeVL
	double stepY; //associated with gridSizeHL
	
	int nX; //Number of vertical lines
	int nY; //Number if Horizontal Lines..
	//int nZ; //Number if Horizontal Lines..
	
	double dx;
	double dy;
	
	boost::numeric:: ublas:: matrix<double> u; //VL - 
	boost::numeric:: ublas:: matrix<double> v; //HL
	
	boost::numeric:: ublas::matrix<double> p; //pressure
	boost::numeric:: ublas::matrix<double> d; //density
	boost::numeric:: ublas::matrix<double> cellType; //type of cell..liquid/air/solid
	boost::numeric:: ublas::matrix<double> isFluidBoundary; //type of cell..liquid/air/solid

	boost::numeric:: ublas::matrix<double> u0; //VL - 
	boost::numeric:: ublas::matrix<double> v0; //HL
	
	boost::numeric:: ublas::matrix<double> p0; //pressure
	boost::numeric:: ublas::matrix<double> d0; //density
	boost::numeric:: ublas::matrix<double> distanceLevelSet;
	std::vector< Particles* > fluidParticles ;
	void initGridStag();
	bool isParticlePresent(double mc_x, double mc_y) ;
};



#endif
