#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <statistics.h>

namespace py = pybind11;

Statistics compute_stats(py::array_t<double> data) {
    Statistics stats;
    auto data_info = data.request();
    ssize_t n = 1;
    for (const auto& size: data_info.shape)
        n *= size;
    for (ssize_t i = 0; i < n; ++i)
        stats.add(((double*) data_info.ptr)[i]);
    return stats;
}

PYBIND11_MODULE(stats, m) {
    m.doc() = "module defining Statistics class";
    m.def("compute_stats", &compute_stats, "return statistics over numpy array");
    py::class_<Statistics>(m, "Statistics")
        .def(py::init<>(), "initialize an anonymous Statistics object")
        .def(py::init<const std::string&>(), "initialize a named Statistics object")
        .def("name", &Statistics::name, "return the name of the Statistics object")
        .def("n", &Statistics::n, "return the number of data items")
        .def("add", (void (Statistics::*)(const double)) &Statistics::add,
             "add a floating point value to the statistics")
        .def("add", (void (Statistics::*)(const std::string&)) &Statistics::add,
             "add a string representation of a value to the statistics")
        .def("sum", &Statistics::sum, "return the sum of the values")
        .def("min", &Statistics::min, "return the minimum value")
        .def("max", &Statistics::max, "return the maximum value")
        .def("mean", &Statistics::mean, "return the mean value")
        .def("stddev", &Statistics::stddev, "return the standard deviation")
        .def("nr_missing", &Statistics::nr_missing, "return the number of missing values");
}
