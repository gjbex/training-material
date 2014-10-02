#!/usr/bin/env python

import numpy as np
import plotly.plotly as py
from plotly.graph_objs import Scatter, Marker, Data, Layout, Figure

colors_orig = [
    'rgb(103,0,31)',
    'rgb(178,24,43)',
    'rgb(214,96,77)',
    'rgb(244,165,130)',
    'rgb(253,219,199)',
    'rgb(247,247,247)',
    'rgb(209,229,240)',
    'rgb(146,197,222)',
    'rgb(67,147,195)',
    'rgb(33,102,172)',
    'rgb(5,48,97)'
]

colors = [
    'rgb(103,0,31)',
    'rgb(178,24,43)',
    'rgb(214,96,77)',
    'rgb(244,165,130)',
    'rgb(248,214,194)',
    'rgb(237,237,237)',
    'rgb(204,224,236)',
    'rgb(146,197,222)',
    'rgb(67,147,195)',
    'rgb(33,102,172)',
    'rgb(5,48,97)'
]
x = np.linspace(0.0, 1.0, 11)
trace = Scatter(
    x=x,
    y=x,
    mode='markers',
    marker=Marker(
        color=colors,
        size=15,
    ),
)
data = Data([trace])
layout = Layout(
    showlegend=False
)
fig = Figure(data=data, layout=layout)

plot_url = py.plot(fig, filename='bubble_colors_test')
print plot_url

