/*
  -------------------------------------------------------------------
  
  Copyright (C) 2012-2017, Andrew W. Steiner
  
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
/** \file process.h
    \brief Definition of main process class
*/
#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>

// For gsl_sf_erf
#include <gsl/gsl_specfunc.h>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <o2scl/table.h>
#include <o2scl/table3d.h>
#include <o2scl/format_float.h>
#include <o2scl/vec_stats.h>
#include <o2scl/contour.h>
#include <o2scl/hist.h>
#include <o2scl/hdf_io.h>
#include <o2scl/expval.h>
#include <o2scl/interp.h>
#include <o2scl/vector.h>
#include <o2scl/hist.h>

#ifdef BAMR_READLINE
#include <o2scl/cli_readline.h>
#else
#include <o2scl/cli.h>
#endif

typedef boost::numeric::ublas::vector<double> ubvector;
typedef boost::numeric::ublas::matrix<double> ubmatrix;

namespace bamr {

  /** \brief Processing MCMC data from bamr
   */
  class process {
  
  protected:
    
    o2scl::cli::parameter_double p_xscale;
    o2scl::cli::parameter_double p_yscale;
    o2scl::cli::parameter_bool p_errors;
    o2scl::cli::parameter_bool p_logx;
    o2scl::cli::parameter_bool p_logy;
    o2scl::cli::parameter_bool p_logz;
    o2scl::cli::parameter_int p_hist_size;
    o2scl::cli::parameter_int p_n_blocks;
    o2scl::cli::parameter_int p_line_start;
    o2scl::cli::parameter_int p_verbose;
    o2scl::cli::parameter_string p_constraint;
    
    /// \name Command-line parameters
    //@{
    /// Verbosity (default 1)
    int verbose;
    /// Ignore all lines before start
    int line_start;
    /// Scale for x-axis
    double xscale;
    /// Scale for y-axis
    double yscale;
    /// If true, use a logarithmic x scale
    bool logx;
    /// If true, use a logarithmic y scale
    bool logy;
    /// If true, use a logarithmic z scale
    bool logz;
    /// If true, plot errors in 1d
    bool errors;
    /// Histogram size
    int hist_size_int;
    /// Number of blocks
    int n_blocks;
    //@}

#ifdef BAMR_READLINE
    o2scl::cli_readline cl;
#else
    o2scl::cli cl;
#endif
    
    /// \name Axis limits from 'xlimits' and 'ylimits'
    //@{
    /// If true, x limits are set
    bool xset;
    /// Lower x value
    double user_xlow;
    /// Upper x value
    double user_xhigh;
    /// If true, y limits are set
    bool yset;
    /// Lower y value
    double user_ylow;
    /// Upper y value
    double user_yhigh;
    //@}

    /// \name Const confidence limits
    //@{
    /// The one-sigma limit of a normal distribution, 0.6827
    const double one_sigma;
    /// The two-sigma limit of a normal distribution, 0.9545
    const double two_sigma;
    /// The three-sigma limit of a normal distribution, 0.9973
    const double three_sigma;
    //@}

    /// \name Other class member data
    //@{
    /// Constraint to apply to the data
    std::string constraint;
    /// Contour levels set in 'contours'
    std::vector<double> cont_levels;
    /// Formatter for floating point numbers
    o2scl::format_float ff;
    //@}

    /// \name Commands
    //@{
    /** \brief Create a table of autocorrelation data from a specified
	column
    */
    int auto_corr(std::vector<std::string> &sv, bool itive_com);
    
    /** \brief Set limits for the x-axis
     */
    int xlimits(std::vector<std::string> &sv, bool itive_com);
    
    /** \brief Set limits for the y-axis
     */
    int ylimits(std::vector<std::string> &sv, bool itive_com);
    
    /** \brief Create a histogram from a specified column

	\future This function isn't that efficient. It first reads all
	of the data into one long vector and then reparses the long
	vector into a set of \ref o2scl::expval_scalar objects. The
	averages and errors for the \ref o2scl::expval_scalar objects
	are stored into a table, and the table is written to the
	output file. This could be improved.
    */
    int hist(std::vector<std::string> &sv, bool itive_com);
    
    /** \brief Create a two-dimensional histogram from two
	user-specified columns
    */
    int hist2(std::vector<std::string> &sv, bool itive_com);
    
    /** \brief Create a set of histograms from a set of columns in
	the bamr MCMC output
    */
    int hist_set(std::vector<std::string> &sv, bool itive_com);
    
    /** \brief Combine several <tt>bamr</tt> output files
     */
    int combine(std::vector<std::string> &sv, bool itive_com);

    /** \brief Specify which contour levels to use
     */
    int contours(std::vector<std::string> &sv, bool itive_com);
    //@}

    /// Desc
    virtual void setup_cli();
    
  public:
    
    /// Create the process object
    process();
    
    /** \brief Main public interface
     */
    void run(int argc, char *argv[]);

  };

}

#endif
