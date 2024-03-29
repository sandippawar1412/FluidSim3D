//FluidSim.h

#ifndef _FLUIDSIM_H
#define _FLUIDSIM_H

#define NDEBUG

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/operation_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

// Must be set if you want to use ViennaCL algorithms on ublas objects
#define VIENNACL_HAVE_UBLAS 1

//
// ViennaCL includes
//
#include "viennacl/linalg/ilu.hpp"
#include "viennacl/linalg/cg.hpp"
#include "viennacl/linalg/bicgstab.hpp"
#include "viennacl/linalg/gmres.hpp"
#include "viennacl/io/matrix_market.hpp"

// Some helper functions for this tutorial:

//#include "Random.hpp"
#include "vector-io.hpp"






#include "GridStag.h"
#include "Particles.h"
//#include "viennacl/vector.hpp"
//#include "viennacl/compressed_matrix.hpp"

#include "pcgsolver/sparse_matrix.h"
#include "pcgsolver/pcg_solver.h"

#include "eigen/Eigen/IterativeLinearSolvers"
//using namespace Eigen;
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include "viennacl/linalg/ilu.hpp"
#include "viennacl/io/matrix_market.hpp"
//#include "Random.hpp"
//#include "vector-io.hpp"
	
//#include "viennacl/linalg/direct_solve.hpp"
#include "viennacl/linalg/cg.hpp"
//#include "viennacl/linalg/inner_prod.hpp"
	using namespace boost::numeric::ublas ;
//using namespace viennacl::linalg;

#include "ParameterFLAGS.hpp"

#define FLUID 1
#define SOLID 2
#define AIR 0

#define GRAVITY -9.8
#define VELOCITY_BC2 4

//#define
//#define DENSITY 100
//#define FORCE -9.8


class FluidSim{
public:
	GridStag *sGrid; //can be used as call by name...declare GridStag& sGrid
	matrix<int> uValid , vValid ; //stores the flag for valid velocities bordering the liquid cells
	double dt;
	double getMinDistance(double,double,double);
	void calculateLevelSetDistance();

	void init(GridStag* );
	void simulate(double);
	void applyBoundaryConditions(int );

	double cfl();
	void advect2DSelf(matrix<double>& q, double,matrix<double> &u,matrix<double> &v,int ); //passing u and v compenents...
	matrix<double> addForce(matrix<double> dest, double dt, matrix<double> src) ;
	void initFluidBody_Helper(int bx,int tx, int by,int ty,matrix<double>& mat,double val);
	void initFluidBody(int ); //set markers...add density/particles in region
	void advectParticles(std::vector< Particles* > & plst, matrix<double>&  ,matrix<double>& , double dt );
	void addGravity(matrix<double> &, double ); //un = un+dt*g	
	void initSolidBoundary(int ); //set markers..applyboundarycondition..can change the boundary...by giving choice
	void markFluidCells();	
	void extrapolate2D(matrix<double> &grid, matrix<int> &valid);

	double getVelInterpolated(double x,double y, matrix<double> &mat);

	void solvePressureBridson(float dt);
	void solvePressureEigen(float dt);
	void solvePressureViennacl(float dt);	//Solver data

	PCGSolver<double> solver;
	SparseMatrixd matrix1;
	std::vector<double> rhs;
	std::vector<double> pressure;

	void RK2(double &posx, double &posy,matrix<double> &u, matrix<double> &v, double dt);
	void setValidVelocity(int val);
	void addViscosity(double,double) ;
	matrix<double> addVisc_Helper(matrix<double>, double, double , int );
	int getNeighbours(matrix<double>mat, int comp, int i, int j, double &nval);
};
#endif

