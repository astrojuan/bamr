/*
  -------------------------------------------------------------------
  
  Copyright (C) 2012-2016, Andrew W. Steiner
  
  This file is part of Bamr.
  
  Bamr is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.
  
  Bamr is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with Bamr. If not, see <http://www.gnu.org/licenses/>.

  -------------------------------------------------------------------
*/
/** \file entry.h
    \brief Definition of entry class
*/
#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>

#include "nstar_cold2.h"

namespace bamr {

  /** \brief A data class which holds the EOS parameters,
      the masses and the radii
  */
  class entry {
  
  public:
  
    /// Create empty entry object
    entry();

    /// Create object for \c nps parameters and \c nso sources
    entry(size_t nps, size_t nso);
    
    /// Reallocate object for \c nps parameters and \c nso sources
    int allocate(size_t nps, size_t nso);

    /// Copy constructor
    entry &operator=(const entry &e);
  
    /// Copy constructor
    entry(const entry &e);
    
    /** \brief Number of parameters 
    */
    size_t np;
  
    /// Parameters
    ubvector params;

    /// Number of sources
    size_t ns;

    /// Mass for each source
    ubvector mass;

    /// Radius for each source
    ubvector rad;
  };

  /// Output an entry object (without trailing endline)
  std::ostream &operator<<(std::ostream &os, entry &e);

}

#endif
