from tables import IsDescription, Int32Col, Float64Col

class Particle(IsDescription):
    particle_id = Int32Col()
    mass        = Float64Col()
    x_pos       = Float64Col()
    y_pos       = Float64Col()
    x_vel       = Float64Col()     
    y_vel       = Float64Col()     

