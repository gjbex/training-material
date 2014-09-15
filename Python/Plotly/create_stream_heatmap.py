#!/usr/bin/env python

import datetime
import numpy as np
import plotly.plotly as py
import plotly.tools as tls
from plotly.graph_objs import Stream, Data, Figure, Heatmap, Layout, Font

stream_id = tls.get_credentials_file()['stream_ids'][3]

stream = Stream( token=stream_id, maxpoints=50)

x = ['a', 'b', 'c', 'd']
y = ['x', 'y', 'z']
z = np.random.randn(3, 4)
trace = Heatmap(z=z, x=x, y=y, stream=stream)
data = Data([trace])
anno_text = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
annotations = [
    dict(
        text=anno_text,  # set annotation text
        showarrow=False, # remove arrow 
        xref='paper',  # use paper coords
        yref='paper',  #  for both coordinates
        x=0.95,  # position's x-coord
        y=1.05,  #   and y-coord
        font=Font(size=14),    # increase font size (default is 12)
        bgcolor='#FFFFFF',     # white background
        borderpad=4            # space bt. border and text (in px)
    )
]
layout = Layout(title='Streaming heatmap test', annotations=annotations)

figure = Figure(data=data, layout=layout)

unique_url = py.plot(figure, filename='stream_heatmap_test',
                     auto_open=False)
print 'Stream ID: {0}'.format(stream_id)
print 'Plot URL: {0}'.format(unique_url)


