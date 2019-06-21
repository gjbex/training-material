#include <cstdlib>
#include <pybind11/pybind11.h>
#include "spectrum.h"

Spectrum::Spectrum(const std::size_t size) {
    for (std::size_t i = 0; i < size; ++i)
        data_.push_back(static_cast<double>(std::rand())/RAND_MAX);
}

namespace py = pybind11;

PYBIND11_MODULE(spectrum, m) {
    m.doc() = "module to generate spectra";
    py::class_<Spectrum>(m, "Spectrum", py::buffer_protocol())
        .def_buffer([](Spectrum& s) -> py::buffer_info {
                std::vector<ssize_t> shape;
                shape.push_back(static_cast<ssize_t>(s.size()));
                std::vector<ssize_t> strides;
                strides.push_back(static_cast<ssize_t>(sizeof(double)));
                return py::buffer_info(
                           s.data(),
                           sizeof(double),
                           py::format_descriptor<double>::format(),
                           1,
                           shape, strides
                       );
         })
        .def(py::init<const std::size_t>(), "initialize spectrum with given size");
}

