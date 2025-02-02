/*    Copyright (c) 2010-2018, Delft University of Technology
 *    All rights reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "expose_io.h"

#include "tudat/io/readHistoryFromFile.h"
#include "tudat/io/missileDatcomData.h"

#include <pybind11/stl.h>

namespace py = pybind11;

namespace tudatpy {

void expose_io(py::module &m) {

      m.def("get_resource_path", &tudat::paths::get_resource_path);
      m.def("get_ephemeris_path", &tudat::paths::getEphemerisDataFilesPath);
      m.def("get_earth_orientation_path", &tudat::paths::getEarthOrientationDataFilesPath);
      m.def("get_quadrature_path", &tudat::paths::getQuadratureDataPath);
      m.def("get_spice_kernel_path", &tudat::paths::getSpiceKernelPath);
      m.def("get_atmosphere_tables_path", &tudat::paths::getAtmosphereTablesPath);
      m.def("get_gravity_models_path", &tudat::paths::getGravityModelsPath);
      m.def("get_space_weather_path", &tudat::paths::getSpaceWeatherDataPath);

      m.def("read_vector_history_from_file", &tudat::input_output::readVectorHistoryFromFile< double, double >,
            py::arg("vector_size"),
            py::arg("file_name") );

      m.def("read_matrix_history_from_file", &tudat::input_output::readMatrixHistoryFromFile< double, double >,
            py::arg("matrix_rows"),
            py::arg("matrix_columns"),
            py::arg("file_name") );

      py::class_<tudat::input_output::MissileDatcomData,
            std::shared_ptr<tudat::input_output::MissileDatcomData>>(
            m, "missile_DATCOM_data")
            .def(py::init<
                  const std::string &>(),
                  py::arg("file_name_and_path"))
            .def("get_static_coefficient",
                  &tudat::input_output::MissileDatcomData::getStaticCoefficient,
                  py::arg("mach_index"),
                  py::arg("angle_of_attack_index"),
                  py::arg("coefficient_index"))
            .def("get_dynamic_coefficient",
                  &tudat::input_output::MissileDatcomData::getDynamicCoefficient,
                  py::arg("mach_index"),
                  py::arg("angle_of_attack_index"),
                  py::arg("coefficient_index"))
            .def("get_angle_of_attacks",
                  &tudat::input_output::MissileDatcomData::getAngleOfAttacks)
            .def("get_mach_numbers",
                  &tudat::input_output::MissileDatcomData::getMachNumbers)
            .def("get_Reynolds_numbers",
                  &tudat::input_output::MissileDatcomData::getReynoldsNumbers)
            .def("write_all_coefficients_to_files",
                  &tudat::input_output::MissileDatcomData::writeAllCoefficientsToFiles,
                  py::arg("file_name_base"),
                  py::arg("base_precision") = 15,
                  py::arg("exponent_width") = 2 )
            .def("write_force_and_moment_coefficients_to_files",
                  &tudat::input_output::MissileDatcomData::writeForceAndMomentCoefficientsToFiles,
                  py::arg("file_name_base"),
                  py::arg("base_precision") = 15,
                  py::arg("exponent_width") = 2 );

      py::enum_<tudat::input_output::MissileDatcomData::DynamicCoefficientNames>(m, "DynamicCoefficientNames")
            .value("cnq", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::cnq)
            .value("cmq", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::cmq)
            .value("caq", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::caq)
            .value("cyq", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::cyq)
            .value("clnq", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::clnq)
            .value("cllq", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::cllq)
            .value("cnr", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::cnr)
            .value("cmr", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::cmr)
            .value("car", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("cyr", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("clnr", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("cllr", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("cnp", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("cmp", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("cap", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("cyp", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("clnp", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("cllp", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("cnad", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .value("cmad", tudat::input_output::MissileDatcomData::DynamicCoefficientNames::car)
            .export_values();

      py::enum_<tudat::input_output::MissileDatcomData::StaticCoefficientNames>(m, "StaticCoefficientNames")
            .value("cn", tudat::input_output::MissileDatcomData::StaticCoefficientNames::cn)
            .value("cm", tudat::input_output::MissileDatcomData::StaticCoefficientNames::cm)
            .value("ca", tudat::input_output::MissileDatcomData::StaticCoefficientNames::ca)
            .value("cy", tudat::input_output::MissileDatcomData::StaticCoefficientNames::cy)
            .value("cln", tudat::input_output::MissileDatcomData::StaticCoefficientNames::cln)
            .value("cll", tudat::input_output::MissileDatcomData::StaticCoefficientNames::cll)
            .value("cna", tudat::input_output::MissileDatcomData::StaticCoefficientNames::cna)
            .value("cma", tudat::input_output::MissileDatcomData::StaticCoefficientNames::cma)
            .value("cyb", tudat::input_output::MissileDatcomData::StaticCoefficientNames::cyb)
            .value("cnb", tudat::input_output::MissileDatcomData::StaticCoefficientNames::cnb)
            .value("clb", tudat::input_output::MissileDatcomData::StaticCoefficientNames::clb)
            .export_values();

};

}// namespace tudatpy