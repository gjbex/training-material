from tables import IsDescription, Float64Col

class Particle(IsDescription):
    x_pos = Float64Col()
    y_pos = Float64Col()
    z_pos = Float64Col()
    x_vel = Float64Col()     
    y_vel = Float64Col()     
    z_vel = Float64Col()     
    mass = Float64Col()     

