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
 * A collection of dynamics classes (e.g. BGK) with which a Cell object
 * can be instantiated -- header file.
 */
#ifndef WAVE_PROPAGATION_H
#define WAVE_PROPAGATION_H

#include "core/globalDefs.h"
#include "core/dynamics.h"

namespace plb {

/// Implementation of O(Ma^2) BGK dynamics with adjustable speed of sound
template<typename T, template<typename U> class Descriptor>
class WaveDynamics : public IsoThermalBulkDynamics<T,Descriptor> {
public:
/* *************** Construction / Destruction ************************ */
    WaveDynamics(T vs2_);

    /// Clone the object on its dynamic type.
    virtual WaveDynamics<T,Descriptor>* clone() const;

    /// Return a unique ID for this class.
    virtual int getId() const;

    /// Serialize the dynamics object.
    virtual void serialize(HierarchicSerializer& serializer) const;

    /// Un-Serialize the dynamics object.
    virtual void unserialize(HierarchicUnserializer& unserializer);

/* *************** Collision and Equilibrium ************************* */

    /// Implementation of the collision step
    virtual void collide(Cell<T,Descriptor>& cell,
                         BlockStatistics& statistics_);

    /// Implementation of the collision step, with imposed macroscopic variables
    virtual void collideExternal(Cell<T,Descriptor>& cell, T rhoBar,
                         Array<T,Descriptor<T>::d> const& j, T thetaBar, BlockStatistics& stat);

    /// Compute equilibrium distribution function
    virtual T computeEquilibrium(plint iPop, T rhoBar, Array<T,Descriptor<T>::d> const& j,
                                 T jSqr, T thetaBar=T()) const;
    
/* *************** Configurable parameters *************************** */

    /// Set local value of any generic parameter
    virtual void setParameter(plint whichParameter, T value);
    /// Get local value of any generic parameter
    virtual T getParameter(plint whichParameter) const;
    /// Set local speed of sound
    void setVs2(T vs2_);
    /// Get local speed of sound
    T    getVs2() const;

private:
/* *************** Static implementation methods********************** */

    /// Implementation of collision operator
    static T waveCollision (
        Cell<T,Descriptor>& cell, T rhoBar, Array<T,Descriptor<T>::d> const& j, T vs2);
    /// Implementation of equilibrium
    static T waveEquilibrium (
        plint iPop, T rhoBar, T invRho, Array<T,Descriptor<T>::d> const& j, T jSqr, T vs2);
private:
    T vs2;    ///< speed of sound
private:
    static int id;
};


/// This class implements the absorbing condition of H. Xu 
template<typename T, template<typename U> class Descriptor>
class WaveAbsorptionDynamics : public CompositeDynamics<T,Descriptor> {
public:
    WaveAbsorptionDynamics(Dynamics<T,Descriptor>* baseDynamics_);
    WaveAbsorptionDynamics(HierarchicUnserializer& unserializer);
    virtual void collide(Cell<T,Descriptor>& cell, BlockStatistics& statistics_);
    virtual void collideExternal(Cell<T,Descriptor>& cell, T rhoBar,
                         Array<T,Descriptor<T>::d> const& j, T thetaBar, BlockStatistics& stat);
    virtual void serialize(HierarchicSerializer& serializer) const;
    virtual void unserialize(HierarchicUnserializer& unserializer);
    virtual WaveAbsorptionDynamics<T,Descriptor>* clone() const {
        return new WaveAbsorptionDynamics<T,Descriptor>(*this);
    }
    virtual void prepareCollision(Cell<T,Descriptor>& cell);
        /// Return a unique ID for this class.
    virtual int getId() const;
private:
    static int id;
};

// Declaration of a specific "sigma" function for WaveAbsorptionDynamics.

template<typename T>
class WaveAbsorptionSigmaFunction3D {
public:
    WaveAbsorptionSigmaFunction3D(Box3D domain_, Array<plint,6> const& numCells_, T omega_);
    T operator()(plint iX, plint iY, plint iZ) const;

private:
    void addDistance(plint from, plint pos, std::vector<plint>& distances, plint i) const;
    T sigma(T x0, T x1, T x) const;

private:
    Box3D domain;
    Array<plint,6> numCells;
    T xi;
};

}  // namespace plb

#endif  // WAVE_PROPAGATION_H
