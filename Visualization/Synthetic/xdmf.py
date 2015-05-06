#!/usr/bin/env python
'''XDMF generation for syntehtic data generator'''

from xml.dom.minidom import Document
import sys

class Xdmf(object):
    '''Class representing an XDMF data descriptor builder'''

    def __init__(self, points, h5file_name):
        '''Constructor'''
        self._doc = Document()
        xdmf = self._doc.createElement('Xdmf')
        xdmf.setAttribute('xmlns:xi', 'http://www.w3.org/2001/XInclude')
        xdmf.setAttribute('Version', '2.0')
        self._doc.appendChild(xdmf)
        self._domain = self._doc.createElement('Domain')
        self._domain.setAttribute('Name', 'domain')
        xdmf.appendChild(self._domain)
        self._create_geometry(points, h5file_name)
        self._create_scalar_field(points, h5file_name)
        self._create_vector_field(points, h5file_name)

    def to_xml(self, xml_file_name, indent='  '):
        with open(xml_file_name, 'w') as xml_file:
            xml_file.write(self._doc.toprettyxml(indent=indent))

    def _create_geometry(self, points, h5file_name):
        topology = self._doc.createElement('Topology')
        topology.setAttribute('Name', 'topology')
        topology.setAttribute('TopologyType', '3DRectMesh')
        topology.setAttribute('Dimensions',
                              '{0:d} {0:d} {0:d}'.format(points))
        self._domain.appendChild(topology)
        geometry = self._doc.createElement('Geometry')
        geometry.setAttribute('Name', 'geometry')
        geometry.setAttribute('GeometryType', 'VXVYVZ')
        self._domain.appendChild(geometry)
        for coord in "xyz":
            item = self._doc.createElement('DataItem')
            item.setAttribute('Name', coord)
            item.setAttribute('Format', 'HDF')
            item.setAttribute('DataType', 'Float')
            item.setAttribute('Precision', '8')
            item.setAttribute('Dimensions', str(points))
            array = self._doc.createTextNode(
                '{0}:/grid/{1}'.format(h5file_name, coord)
            )
            item.appendChild(array)
            geometry.appendChild(item)

    def _create_scalar_field(self, points, h5file_name):
        grid = self._doc.createElement('Grid')
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
        item.setAttribute('Dimensions', '{0:d} {0:d} {0:d}'.format(points))
        data = self._doc.createTextNode('{0}:/scalar'.format(h5file_name))
        item.appendChild(data)
        attribute.appendChild(item)

    def _create_vector_field(self, points, h5file_name):
        grid = self._doc.createElement('Grid')
        grid.setAttribute('GridType', 'Uniform')
        self._domain.appendChild(grid)
        topology = self._doc.createElement('Topology')
        topology.setAttribute('Reference', '/Xdmf/Domain/Topology[1]')
        grid.appendChild(topology)
        geometry = self._doc.createElement('Geometry')
        geometry.setAttribute('Reference', '/Xdmf/Domain/Geometry[1]')
        grid.appendChild(geometry)
        for dim in ['x', 'y', 'z']:
            attribute = self._doc.createElement('Attribute')
            attribute.setAttribute('Name', '{0}-component'.format(dim))
            attribute.setAttribute('Center', 'Node')
            grid.appendChild(attribute)
            item = self._doc.createElement('DataItem')
            item.setAttribute('Format', 'HDF')
            item.setAttribute('DataType', 'Float')
            item.setAttribute('Precision', '8')
            item.setAttribute('Dimensions',
                              '{0:d} {0:d} {0:d}'.format(points))
            data = self._doc.createTextNode(
                '{0}:/vector/{1}'.format(h5file_name, dim)
            )
            item.appendChild(data)
            attribute.appendChild(item)

if __name__ == '__main__':
    from argparse import ArgumentParser

    arg_parser = ArgumentParser(description='genearte XMDF file')
    arg_parser.add_argument('--h5', required=True, help='HDF5 data file')
    arg_parser.add_argument('--points', type=int, required=True,
                            help='number of grid points for grid')
    arg_parser.add_argument('file', help='XDMF file name')
    options = arg_parser.parse_args()
    xdmf = Xdmf(options.points, options.h5)
    xdmf.to_xml(options.file)
