#!/usr/bin/env python

if __name__ == '__main__':
    
    from argparse import ArgumentParser
    from math import exp
    import sys
    if sys.version_info.major < 3:
        from StringIO import StringIO
    else:
        from io import StringIO
    from xml.dom.minidom import Document
    import numpy as np

    min_val = -1.0
    max_val = 1.0
    default_points = 10
    default_a = 1.0
    default_a_t = 0.95
    arg_parser = ArgumentParser(description='produce a 3D scalar field')
    arg_parser.add_argument('-x', type=int, default=default_points,
                            help='number of x points')
    arg_parser.add_argument('-y', type=int, default=default_points,
                            help='number of y points')
    arg_parser.add_argument('-z', type=int, default=default_points,
                            help='number of z points')
    arg_parser.add_argument('-t', type=int, default=default_points,
                            help='number of time steps')
    arg_parser.add_argument('-a_x', type=float, default=default_a,
                            help='alpha_x')
    arg_parser.add_argument('-a_y', type=float, default=default_a,
                            help='alpha_y')
    arg_parser.add_argument('-a_z', type=float, default=default_a,
                            help='alpha_z')
    arg_parser.add_argument('-a_t', type=float, default=default_a_t,
                            help='alpha_t')
    options = arg_parser.parse_args()
# create data points
    x_points = np.linspace(min_val, max_val, num=options.x, endpoint=True) 
    y_points = np.linspace(min_val, max_val, num=options.y, endpoint=True)
    z_points = np.linspace(min_val, max_val, num=options.z, endpoint=True)
# dimensions string
    dim_str = '{x} {y} {z}'.format(x=len(x_points),
                                   y=len(y_points),
                                   z=len(z_points))
    a_t = 1.0
# create Xmdf
    doc = Document()
# create Xdmf element
    xdmf = doc.createElement('Xdmf')
    xdmf.setAttribute('xmlns:xi', 'http://www.w3.org/2001/XInclude')
    xdmf.setAttribute('Version', '2.0')
    doc.appendChild(xdmf)
# create Domain element
    domain = doc.createElement('Domain')
    domain.setAttribute('Name', 'domain')
    xdmf.appendChild(domain)
# create Topology element
    topology = doc.createElement('Topology')
    topology.setAttribute('Name', 'topology')
    topology.setAttribute('TopologyType', '3DCoRectMesh')
    topology.setAttribute('Dimensions', dim_str)
    domain.appendChild(topology)
# create Geometry element
    geometry = doc.createElement('Geometry')
    geometry.setAttribute('Name', 'geometry')
    geometry.setAttribute('GeometryType', 'ORIGIN_DxDyDz')
# create DataItem for origin
    origin_data_item = doc.createElement('DataItem')
    origin_data_item.setAttribute('Dimensions', '3')
    origin_data_item.setAttribute('Format', 'XML')
    origin_values = doc.createTextNode('0.0 0.0 0.0')
    origin_data_item.appendChild(origin_values)
    geometry.appendChild(origin_data_item)
# create DataItem for dxdydz
    dxdydz_data_item = doc.createElement('DataItem')
    dxdydz_data_item.setAttribute('Dimensions', '3')
    dxdydz_data_item.setAttribute('Format', 'XML')
    dxdydz_values = doc.createTextNode('1.0 1.0 1.0')
    dxdydz_data_item.appendChild(dxdydz_values)
    geometry.appendChild(dxdydz_data_item)
    domain.appendChild(geometry)
# create Grid element
    grid = doc.createElement('Grid')
    grid.setAttribute('Name', 'mesh')
    grid.setAttribute('GridType', 'Collection')
    grid.setAttribute('CollectionType', 'Temporal')
    domain.appendChild(grid)
# create time element
    time = doc.createElement('Time')
    time.setAttribute('TimeType', 'Hyperslab')
    grid.appendChild(time)
# create time DataItem element
    time_data_item = doc.createElement('DataItem')
    time_data_item.setAttribute('Format', 'XML')
    time_data_item.setAttribute('NumberType', 'Float')
    time_data_item.setAttribute('Dimensions', '3')
    time_values = doc.createTextNode('0.0 1.0 {0}'.format(options.t))
    time_data_item.appendChild(time_values)
    time.appendChild(time_data_item)
    for t in xrange(options.t):
# create time point grid
        time_grid = doc.createElement('Grid')
        time_grid.setAttribute('Name', 'time {0}'.format(t))
        time_grid.setAttribute('GridType', 'Uniform')
        grid.appendChild(time_grid)
# create Topology element
        topology = doc.createElement('Topology')
        topology.setAttribute('Reference', '/Xdmf/Domain/Topology[1]')
        time_grid.appendChild(topology)
# create Geometry element
        geometry = doc.createElement('Geometry')
        geometry.setAttribute('Reference', '/Xdmf/Domain/Geometry[1]')
        time_grid.appendChild(geometry)
# create Attribute for values
        attribute = doc.createElement('Attribute')
        attribute.setAttribute('Name', 'temperature')
        attribute.setAttribute('Center', 'Node')
        time_grid.appendChild(attribute)
# create DataItem for Attribute
        data_item = doc.createElement('DataItem')
        data_item.setAttribute('Format', 'XML')
        data_item.setAttribute('Dimensions', dim_str)
        data_str = StringIO()
        data_str.write('\n')
        for x in x_points:
            for y in y_points:
                for z in z_points:
                    v = exp(-a_t*(options.a_x*x**2 +
                                  options.a_y*y**2 +
                                  options.a_z*z**2))
                    data_str.write('{0}\n'.format(str(v)))
        data_text = doc.createTextNode(data_str.getvalue())
        data_item.appendChild(data_text)
        attribute.appendChild(data_item)
        data_str.close()
        a_t *= options.a_t
    print(doc.toprettyxml(indent='  '))

