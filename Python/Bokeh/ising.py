#!/usr/bin/env python

from argparse import ArgumentParser
from bokeh.layouts import column
from bokeh.models import CustomJS, ColumnDataSource, Slider
from bokeh.plotting import Figure, output_file, show
import math


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='Visualize Ising mean field '
                                            'magnetization')
    arg_parser.add_argument('file', help='HTML output file')
    options = arg_parser.parse_args()
    output_file(options.file)

    x = [x*0.01 for x in range(-150, 151)]
    y = x
    beta = 4.0
    y_tanh = [math.tanh(4.0*xx*beta) for xx in x]

    source = ColumnDataSource(data=dict(x=x, y=y_tanh))

    def callback(source=source):
        data = source.get('data')
        beta = cb_obj.get('value')
        x, y = data['x'], data['y']
        for i in range(len(x)):
            y[i] = Math.tanh(4.0*x[i]*beta)
        source.trigger('change')

    plot = Figure(plot_width=600, plot_height=600)
    plot.line(x, y)
    plot.line('x', 'y', source=source, line_width=1)

    slider = Slider(start=0.2, end=4.0, value=4.0, step=0.01, title="beta",
                    callback=CustomJS.from_py_func(callback))

    layout = column(children=[plot, slider])

    show(layout)
