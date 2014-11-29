from tables import IsDescription, Float64Col

class ScalarField(IsDescription):
    value = Float64Col()

