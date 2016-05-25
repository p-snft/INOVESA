/******************************************************************************
 * Inovesa - Inovesa Numerical Optimized Vlasov-Equation Solver Algorithms   *
 * Copyright (c) 2014-2016: Patrik Schönfeldt                                 *
 *                                                                            *
 * This file is part of Inovesa.                                              *
 * Inovesa is free software: you can redistribute it and/or modify            *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * Inovesa is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with Inovesa.  If not, see <http://www.gnu.org/licenses/>.           *
 ******************************************************************************/

#include "IO/ProgramOptions.hpp"

vfps::ProgramOptions::ProgramOptions() :
    _cldevice(1),
    _startdistfile(""),
    _configfile("default.cfg"),
    _glversion(2),
    _verbose(false),
    _wakefile(""),
    meshsize(256),
    outsteps(100),
    padding(0),
    pq_size(5.0),
    meshshiftx(0),
    meshshifty(0),
    steps(4000),
    rotations(1),
    rotmapsize(-1),
    E_0(1.3e9),
    Fk(0),
    f_c(23e9),
    f_s(8.5e3),
    f_rev(2.7e6),
    h(0),
    H(1),
    I_b(1),
    t_d(0.01),
    r_bend(-1),
    s_E(4.7e-4),
    V_RF(1e6),
    _physopts("Physical Parameters for Simulation"),
    _proginfoopts("Program Information"),
    _programopts_cli("General Program Parameters"),
    _simulopts("Non-Physical Parameters for Simulation"),
    _visibleopts("Possible Parameters")
{
    _proginfoopts.add_options()
        ("help,h", "print help message")
        ("version,V", "print version string")
    ;
    _physopts.add_options()
        ("RevolutionFrequency,F", po::value<double>(&f_rev),
            "Revolution frequency (Hz)")
        ("SyncFreq,f", po::value<double>(&f_s),"Synchrotron frequency (Hz)")
        ("DampingTime,d", po::value<double>(&t_d),"Damping time (s)")
        ("HarmonicNumber,H", po::value<double>(&H),
            "Harmonic Number (1)")
        ("InitialDistFile,D", po::value<std::string>(&_startdistfile),
            "might be:\n"
            #ifdef INOVESA_USE_PNG
            "\tgrayscale png (.png) file\n"
            #endif // INOVESA_USE_PNG
            "\ttext file (.txt) w/ particle coordinates")
        ("InitialDistParam,K",po::value<double>(&Fk),
            "Parameter F(k) of initial distribution")
        ("BunchCurrent,I", po::value<double>(&I_b),
            "Ring Current due to a single bunch (A)")
        ("BendingRadius,R", po::value<double>(&r_bend),
            "Bending radius of accelerator (m)\n"
            "negative: calculate from RevolutionFrequency")
        ("BeamEnergy,E", po::value<double>(&E_0),
            "Beam energy (GeV)")
        ("BeamEnergySpread,e", po::value<double>(&s_E),
            "Natural energy spread (relative)")
        ("Impedance,Z", po::value<std::string>(&_impedancefile),
            "File containing impedance information.")
        ("VaccuumHeight", po::value<double>(&h),
            "Height of vacuum chamber (m)\n"
            "<0: no CSR\n"
            " 0: free space CSR\n"
            ">0: parallel plates CSR")
        ("CutoffFreq", po::value<double>(&f_c),"Beamline cutoff frequency (Hz)")
        ("RFVoltage,V", po::value<double>(&V_RF),
            "Accelerating Voltage (V)")
        ("WakeFunction,w", po::value<std::string>(&_wakefile),
            "File containing wake function.")
    ;
    _programopts_file.add_options()
        ("cldev", po::value<int>(&_cldevice)->default_value(1),
            "OpenCL device to use\n('-1' lists available devices)")
        ("gui,g", po::value<bool>(&_showphasespace)->default_value(true),
            "Show phase space view")
        ("ForceOpenGLVersion", po::value<int>(&_glversion),
            "Force OpenGL version")
        ("verbose,v", po::value<bool>(&_verbose),
            "print information more detailed")
        ("output,o",
            po::value<std::string>(&_outfile),
            "name of file to safe results.")
    ;
    _programopts_cli.add_options()
        #ifdef INOVESA_USE_CL
        ("cldev", po::value<int>(&_cldevice)->default_value(1),
            "OpenCL device to use\n('-1' lists available devices)")
        #endif // INOVESA_USE_CL
        ("config,c", po::value<std::string>(&_configfile),
            "name of a file containing a configuration.")
        ("gui,g", po::value<bool>(&_showphasespace)->default_value(true),
            "Show phase space view")
        ("ForceOpenGLVersion", po::value<int>(&_glversion),
            "Force OpenGL version")
        ("verbose,v", "print information more detailed" )
        ("output,o",
            po::value<std::string>(&_outfile),
            "name of file to safe results.")
    ;
    _simulopts.add_options()
        ("steps,N", po::value<unsigned int>(&steps),
            "Steps for one synchrotron period")
        ("outstep,n", po::value<unsigned int>(&outsteps),
            "Save results every n steps.")
        ("padding,p", po::value<unsigned int>(&padding),
            "Factor for zero padding of bunch profile")
        ("PhaseSpaceSize,P", po::value<double>(&pq_size),
            "Size of phase space")
        ("PhaseSpaceShiftX",po::value<double>(&meshshiftx),
            "Shift grid by X mesh points")
        ("PhaseSpaceShiftY",po::value<double>(&meshshifty),
            "Shift grid by Y mesh points")
        ("RotMapSize", po::value<int>(&rotmapsize)->default_value(-1),
            "Size of rotation map\n"
            "-1: on-axis displacements\n"
            " 0: none\n"
            " 1: full\n"
            " 2: half")
        ("GridSize,s", po::value<unsigned int>(&meshsize),
            "Number of mesh points per dimension")
        ("rotations,T", po::value<double>(&rotations),
            "Simulated time (in number of synchrotron periods)")
        ("derivation",po::value<unsigned int>(&deriv_type)->default_value(4u),
            "Number of grid points to be used to numerically find derivative")
        ("InterpolationPoints",po::value<unsigned int>(&interpol_type)->default_value(4u),
            "Number of grid points to be used for interpolation")
        ("InterpolateClamped",po::value<bool>(&interpol_clamp)->default_value(true),
            "Restrict result of interpolation to the values of the neighboring grid points")
    ;
    _cfgfileopts.add(_physopts);
    _cfgfileopts.add(_programopts_file);
    _cfgfileopts.add(_simulopts);
    _commandlineopts.add(_proginfoopts);
    _commandlineopts.add(_programopts_cli);
    _commandlineopts.add(_simulopts);
    _commandlineopts.add(_physopts);
    _visibleopts.add(_commandlineopts);


    std::stringstream timestamp;
    timestamp << time(nullptr);
    _outfile = "result_" + timestamp.str() + ".h5";
}

bool vfps::ProgramOptions::parse(int ac, char** av)
{
    po::store(po::parse_command_line(ac, av, _commandlineopts), _vm);
    po::notify(_vm);

    if (_vm.count("verbose")) {
        _verbose = true;
    }
    if (_vm.count("help")) {
        std::cout << _visibleopts << std::endl;
        return false;
    }
    if (_vm.count("version")) {
        std::cout << "Inovesa v"
                  << INOVESA_VERSION_RELEASE << '.'
                  << INOVESA_VERSION_MINOR << '.'
                  << INOVESA_VERSION_FIX;
        if (std::string(GIT_BRANCH) != "master") {
            std::cout << " (Branch: " GIT_BRANCH ")";
        }
        std::cout << std::endl;
        return false;
    }
    std::ifstream ifs(_configfile.c_str());
    if (!ifs) {
        std::cout << "Cannot open config file: " << _configfile
                  << std::endl;
        return false;
    } else {
        store(parse_config_file(ifs, _cfgfileopts), _vm);
        notify(_vm);
    }
    #ifndef INOVESA_USE_CL
    if (_vm.count("cldev")) {
        std::cout    << "Warning: Defined device for OpenCL "
                    << "but running Inovesa without OpenCL support."
                    << std::endl;
    }
    #endif

    return true;
}

void vfps::ProgramOptions::save(std::string fname)
{
    std::ofstream ofs(fname.c_str());

    ofs << "#Inovesa v"
        << INOVESA_VERSION_RELEASE << '.'
        << INOVESA_VERSION_MINOR << '.'
        << INOVESA_VERSION_FIX;
    if (std::string(GIT_BRANCH) != "stable") {
        ofs << " (Branch: " GIT_BRANCH ")";
    }
    ofs << std::endl;

    for (po::variables_map::iterator it=_vm.begin(); it != _vm.end(); it++ ) {
        if (!it->second.value().empty() && !_vm[it->first].defaulted()) {
            if (it->second.value().type() == typeid(double)) {
                ofs << it->first << '='
                    << _vm[it->first].as<double>()
                    << std::endl;
            } else if (it->second.value().type() == typeid(unsigned int)) {
                ofs << it->first << '='
                    << _vm[it->first].as<unsigned int>()
                    << std::endl;
            } else if (it->second.value().type() == typeid(int)) {
                ofs << it->first << '='
                    << _vm[it->first].as<int>()
                    << std::endl;
            } else if (it->second.value().type() == typeid(bool)) {
                ofs << it->first << '='
                    << _vm[it->first].as<bool>()
                    << std::endl;
            } else {
                std::string val;
                try {
                    if (it->first == "config") {
                        ofs << '#';
                    }
                    val = _vm[it->first].as<std::string>();
                    ofs << it->first << '='
                        << val
                        << std::endl;
                } catch(const boost::bad_any_cast &){}
            }
        }
    }
}
