/* This file is part of the Palabos library.
 *
 * Copyright (C) 2011-2015 FlowKit Sarl
 * Route d'Oron 2
 * 1010 Lausanne, Switzerland
 * E-mail contact: contact@flowkit.com
 *
 * The most recent release of Palabos can be downloaded at 
 * <http://www.palabos.org/>
 *
 * The library Palabos is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * The library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/** \file
 * Helper functions for domain initialization -- header file.
 */
#ifndef FINITE_DIFFERENCE_WRAPPER_2D_H
#define FINITE_DIFFERENCE_WRAPPER_2D_H

#include "core/globalDefs.h"
#include "atomicBlock/blockLattice2D.h"
#include "atomicBlock/dataField2D.h"
#include "multiBlock/multiBlockLattice2D.h"
#include "multiBlock/multiDataField2D.h"
#include "dataProcessors/dataAnalysisFunctional2D.h"
#include <memory>


namespace plb {

template<typename T>
void computeXderivative(MultiScalarField2D<T>& value, MultiScalarField2D<T>& derivative, Box2D const& domain);

template<typename T>
std::auto_ptr<MultiScalarField2D<T> > computeXderivative(MultiScalarField2D<T>& value, Box2D const& domain);

template<typename T>
std::auto_ptr<MultiScalarField2D<T> > computeXderivative(MultiScalarField2D<T>& value);

template<typename T>
void computeYderivative(MultiScalarField2D<T>& value, MultiScalarField2D<T>& derivative, Box2D const& domain);

template<typename T>
std::auto_ptr<MultiScalarField2D<T> > computeYderivative(MultiScalarField2D<T>& value, Box2D const& domain);

template<typename T>
std::auto_ptr<MultiScalarField2D<T> > computeYderivative(MultiScalarField2D<T>& value);

template<typename T>
void computeGradientNorm(MultiScalarField2D<T>& value, MultiScalarField2D<T>& derivative, Box2D const& domain);

template<typename T>
std::auto_ptr<MultiScalarField2D<T> > computeGradientNorm(MultiScalarField2D<T>& value, Box2D const& domain);

template<typename T>
std::auto_ptr<MultiScalarField2D<T> > computeGradientNorm(MultiScalarField2D<T>& value);

template<typename T>
std::auto_ptr<MultiScalarField2D<T> > computePoissonRHS(MultiTensorField2D<T,2>& velocity, Box2D const& domain);

template<typename T>
std::auto_ptr<MultiScalarField2D<T> > computePoissonRHS(MultiTensorField2D<T,2>& velocity);


template<typename T>
void poissonIterate(MultiScalarField2D<T>& oldPressure, MultiScalarField2D<T>& newPressure,
                    MultiScalarField2D<T>& rhs, Box2D const& domain);

template<typename T>
T computePoissonResidue(MultiScalarField2D<T>& pressure, MultiScalarField2D<T>& rhs, Box2D const& domain);

/* ************ Gauss-Seidel Solver *************** */

template<typename T>
void JacobiIteration( MultiScalarField2D<T>& u_h, MultiScalarField2D<T>& new_u_h,
                      MultiScalarField2D<T>& rhs, Box2D const& domain );

template<typename T> 
void GaussSeidelIteration( MultiScalarField2D<T>& u_h, MultiScalarField2D<T>& jacobi_u_h,
                           MultiScalarField2D<T>& new_u_h, MultiScalarField2D<T>& rhs, Box2D const& domain );
                      

template<typename T>
void GaussSeidelSolver( MultiScalarField2D<T>& initialValue,
                        MultiScalarField2D<T>& result,
                        MultiScalarField2D<T>& rhs, Box2D const& domain, T tolerance=1e-5, plint maxIter=100000 );
                        
template<typename T> 
MultiScalarField2D<T>* computeGaussSeidelDefect(MultiScalarField2D<T>& u_h, MultiScalarField2D<T>& rhs, 
                                                Box2D const& domain);


/* ************ MultiGrid methods *************** */
template<typename T>
MultiScalarField2D<T>* smooth( MultiScalarField2D<T>& initialValue, 
                               MultiScalarField2D<T>& rhs, Box2D const& domain,
                               plint smoothIters);
                               
template<typename T>
MultiScalarField2D<T>* smoothAndInterpolate(MultiScalarField2D<T>& initialValue, 
                                            MultiScalarField2D<T>& rhs, Box2D const& domain,
                                            plint smoothIters);

template<typename T>
T smoothAndComputeError(MultiScalarField2D<T>& initialValue, MultiScalarField2D<T>& rhs, Box2D const& domain);

template<typename T>
MultiScalarField2D<T>* smoothAndComputeCoarseDefect( MultiScalarField2D<T>& initialValue, 
                                               MultiScalarField2D<T>& rhs, Box2D const& domain, plint smoothIters );   


template<typename T>
T multiGridVCycle( MultiScalarField2D<T>& initialValue, MultiScalarField2D<T>& newValue,
                      MultiScalarField2D<T>& rhs, Box2D const& domain, plint depth=1 );

template<typename T>
std::vector<MultiScalarField2D<T>* > fullMultiGrid( MultiScalarField2D<T>& initialValue, MultiScalarField2D<T>& rhs,
                                                    Box2D const& domain, plint gridLevels=2, plint ncycles=1);

template<typename T>
std::vector<MultiScalarField2D<T>* > fullMultiGrid( MultiScalarField2D<T>& initialValue, MultiScalarField2D<T>& rhs,
                                                    Box2D const& domain, plint gridLevels=2 );

                                                    
                      
}  // namespace plb

#endif  // FINITE_DIFFERENCE_WRAPPER_2D_H
