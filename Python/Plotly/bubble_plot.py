#!/usr/bin/env python

import plotly.plotly as py
from plotly.graph_objs import Scatter, Marker, Data, Layout, Figure

trace = Scatter(
    x=[1, 2, 1, 2],
    y=[1, 1, 2, 2],
    mode='markers',
    marker=Marker(
        color=['rgb(255,30,30)', 'rgb(150,30,30)',
               'rgb(30,30,150)', 'rgb(30,30,255)'],
        size=[12, 22, 32, 42],
    ),
    text=['alpha', 'beta', 'gamma', 'delta'],
)
data = Data([trace])
layout = Layout(
    showlegend=False
)
fig = Figure(data=data, layout=layout)

plot_url = py.plot(fig, filename='bubblechart_test')
print plot_url

