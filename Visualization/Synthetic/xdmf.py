#!/usr/bin/env python
'''XDMF generation for syntehtic data generator'''

from xml.dom.minidom import Document
import sys

class Xdmf(object):
    '''Class representing an XDMF data descriptor builder'''

    def __init__(self, particles, points, h5file_name):
        '''Constructor'''
        self._particles = particles
        self._points = points
        self._h5 = h5file_name
        self._doc = Document()
        xdmf = self._doc.createElement('Xdmf')
        xdmf.setAttribute('xmlns:xi', 'http://www.w3.org/2001/XInclude')
        xdmf.setAttribute('Version', '2.0')
        self._doc.appendChild(xdmf)
        self._domain = self._doc.createElement('Domain')
        self._domain.setAttribute('Name', 'domain')
        xdmf.appendChild(self._domain)

    def to_xml(self, xml_file_name, indent='  '):
        with open(xml_file_name, 'w') as xml_file:
            xml_file.write(self._doc.toprettyxml(indent=indent))

    def create_particles(self):
        grid = self._doc.createElement('Grid')
        grid.setAttribute('Name', 'particles')
        grid.setAttribute('GridType', 'Uniform')
        self._domain.appendChild(grid)
        topology = self._doc.createElement('Topology')
        topology.setAttribute('Name', 'particle_topology')
        topology.setAttribute('TopologyType', 'Polyvertex')
        grid._domain.appendChild(topology)
        geometry = self._doc.createElement('Geometry')
        geometry.setAttribute('Name', 'particle_geometry')
        geometry.setAttribute('GeometryType', 'XYZ')
        item = self._doc.createElement('DataItem')
        item.setAttribute('Format', 'HDF')
        item.setAttribute('DataType', 'Float')
        item.setAttribute('Precision', '8')
        item.setAttribute('Dimensions', '{0:d} 3'.format(self._particles))
        ref = self._doc.createTextNode(
            '{0}:/particles/position'.format(self._h5)
        )
        item.appendChild(ref)
        geometry.appendChild(item)
        grid.appendChild(geometry)
        attribute = self._doc.createElement('Attribute')
        attribute.setAttribute('Name', 'mass')
        attribute.setAttribute('Center', 'Node')
        item = self._doc.createElement('DataItem')
        item.setAttribute('Format', 'HDF')
        item.setAttribute('DataType', 'Float')
        item.setAttribute('Precision', '8')
        item.setAttribute('Dimensions', '{0:d}'.format(self._particles))
        ref = self._doc.createTextNode(
            '{0}:/particles/mass'.format(self._h5)
        )
        item.appendChild(ref)
        attribute.appendChild(item)
        grid.appendChild(attribute)
        attribute = self._doc.createElement('Attribute')
        attribute.setAttribute('Name', 'velocity')
        attribute.setAttribute('Center', 'Node')
        attribute.setAttribute('AttributeType', 'Vector')
        item = self._doc.createElement('DataItem')
        item.setAttribute('Format', 'HDF')
        item.setAttribute('DataType', 'Float')
        item.setAttribute('Precision', '8')
        item.setAttribute('Dimensions', '{0:d} 3'.format(self._particles))
        ref = self._doc.createTextNode(
            '{0}:/particles/velocity'.format(self._h5)
        )
        item.appendChild(ref)
        attribute.appendChild(item)
        grid.appendChild(attribute)
        
    def create_field_geometry(self):
        topology = self._doc.createElement('Topology')
        topology.setAttribute('Name', 'field_topology')
        topology.setAttribute('TopologyType', '3DRectMesh')
        topology.setAttribute('Dimensions',
                              '{0:d} {0:d} {0:d}'.format(self._points))
        self._domain.appendChild(topology)
        geometry = self._doc.createElement('Geometry')
        geometry.setAttribute('Name', 'field_geometry')
        geometry.setAttribute('GeometryType', 'VXVYVZ')
        self._domain.appendChild(geometry)
        for coord in "xyz":
            item = self._doc.createElement('DataItem')
            item.setAttribute('Name', coord)
            item.setAttribute('Format', 'HDF')
            item.setAttribute('DataType', 'Float')
            item.setAttribute('Precision', '8')
            item.setAttribute('Dimensions', str(self._points))
            array = self._doc.createTextNode(
                '{0}:/grid/{1}'.format(self._h5, coord)
            )
            item.appendChild(array)
            geometry.appendChild(item)

    def create_scalar_field(self):
        grid = self._doc.createElement('Grid')
        grid.setAttribute('Name', 'scalar_field')
        grid.setAttribute('GridType', 'Uniform')
        self._domain.appendChild(grid)
        topology = self._doc.createElement('Topology')
        topology.setAttribute('Reference', '/Xdmf/Domain/Topology[1]')
        grid.appendChild(topology)
        geometry = self._doc.createElement('Geometry')
        geometry.setAttribute('Reference', '/Xdmf/Domain/Geometry[1]')
        grid.appendChild(geometry)
        attribute = self._doc.createElement('Attribute')
        attribute.setAttribute('Name', 'scalar field')
        attribute.setAttribute('Center', 'Node')
        grid.appendChild(attribute)
        item = self._doc.createElement('DataItem')
        item.setAttribute('Format', 'HDF')
        item.setAttribute('DataType', 'Float')
        item.setAttribute('Precision', '8')
        item.setAttribute('Dimensions',
                          '{0:d} {0:d} {0:d}'.format(self._points))
        data = self._doc.createTextNode('{0}:/scalar'.format(self._h5))
        item.appendChild(data)
        attribute.appendChild(item)

if __name__ == '__main__':
    from argparse import ArgumentParser

    arg_parser = ArgumentParser(description='genearte XMDF file')
    arg_parser.add_argument('--h5', required=True, help='HDF5 data file')
    arg_parser.add_argument('--particles', type=int,
                            help='number of particles')
    arg_parser.add_argument('--points', type=int,
                            help='number of grid points for grid')
    arg_parser.add_argument('file', help='XDMF file name')
    options = arg_parser.parse_args()
    xdmf = Xdmf(options.points, options.particles, options.h5)
    if options.particles is not NOne:
        xdmf.create_particles()
    if options.points is not None:
        xdmf.create_field_geometry()
        xdmf.create_scalar_field()
    xdmf.to_xml(options.file)
