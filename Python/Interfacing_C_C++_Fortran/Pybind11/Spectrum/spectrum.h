#ifndef SPECTRUM_HDR
#define SPECTRUM_HDR

#include <vector>

class Spectrum {
    private:
        std::vector<double> data_;
    public:
        Spectrum(const std::size_t size);
        void* data() const {return const_cast<double*>(data_.data()); }
        std::size_t size() const { return data_.size(); }
};

#endif
