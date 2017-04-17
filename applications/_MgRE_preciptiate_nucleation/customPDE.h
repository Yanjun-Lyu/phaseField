/*
 * customPDE.h
 *
 *  Created on: Feb 24, 2017
 *      Author: stephendewitt
 */

#ifndef APPLICATIONS_PRECIPITATEEVOLUTION_CUSTOMPDE_H_
#define APPLICATIONS_PRECIPITATEEVOLUTION_CUSTOMPDE_H_

#include "../../include/matrixFreePDE.h"
#include "../../include/parallelNucleationList.h"
#include "../../include/nucleus.h"

template <int dim, int degree>
class customPDE: public MatrixFreePDE<dim,degree>
{
public:
	customPDE(userInputParameters<dim> _userInputs): MatrixFreePDE<dim,degree>(_userInputs) {};

	void setBCs();

private:

	const static unsigned int CIJ_tensor_size =2*dim-1+dim/3;

	void residualRHS(const std::vector<modelVariable<dim> > & modelVarList,
			  	  	 std::vector<modelResidual<dim> > & modelResidualsList,
					 dealii::Point<dim, dealii::VectorizedArray<double> > q_point_loc) const;

	void residualLHS(const std::vector<modelVariable<dim> > & modelVarList,
	  		  	  	 modelResidual<dim> & modelRes,
					 dealii::Point<dim, dealii::VectorizedArray<double> > q_point_loc) const;

	void energyDensity(const std::vector<modelVariable<dim> > & modelVarList, const dealii::VectorizedArray<double> & JxW_value,
			  	  	 dealii::Point<dim, dealii::VectorizedArray<double> > q_point_loc);

	// Virtual method in MatrixFreePDE we choose to override
	void getNucleiList ();


	// ----------------------------------------------------------------
	// Nucleation methods specific to this subclass
	// ----------------------------------------------------------------

	// Function to determine where new nuclei are seeded, varies between applications unless generalized, accesses MatrixFreePDE members
	void getLocalNucleiList(std::vector<nucleus<dim> > &newnuclei, std::vector<unsigned int> order_parameter_list, std::vector<unsigned int> other_var_list) const;

	// Contains nucleation probability that varies between applications, no MatrixFreePDE member access
	double nucProb(double cValue, double dV) const;

	void safetyCheckNewNuclei(std::vector<nucleus<dim> > newnuclei, std::vector<unsigned int> order_parameter_list, std::vector<unsigned int> &conflict_inds);

	// Function to refine the mesh near the new nuclei, generic, accesses and modifies MatrixFreePDE members
	void refineMeshNearNuclei(std::vector<nucleus<dim> > newnuclei);

	// Vector of all the nuclei seeded in the problem
	std::vector<nucleus<dim> > nuclei;

};



#endif /* APPLICATIONS_PRECIPITATEEVOLUTION_CUSTOMPDE_H_ */
