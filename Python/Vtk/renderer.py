#!/usr/bin/env python

import vtk

if __name__ == '__main__':
    from argparse import ArgumentParser
    arg_parser = ArgumentParser(description='read and render VTK data')
    arg_parser.add_argument('file', help='VTK file')
    options = arg_parser.parse_args()
# create a reader, and set file name
    reader = vtk.vtkXMLPolyDataReader()
    reader.SetFileName(options.file)
# create a mapper, connect reader's output port to input connector
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(reader.GetOutputPort())
# create actor, and set its mapper
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
# create renderer, and add actor
    renderer = vtk.vtkRenderer()
    renderer.AddActor(actor)
# create render window, and add renderer
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)
# create render window interactor, set render window, initialize and start
    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(render_window)
    interactor.Initialize()
    render_window.Render()
    interactor.Start()
