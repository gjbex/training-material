#!/usr/bin/env python

import datetime
import numpy as np
import plotly.plotly as py
import plotly.tools as tls
from plotly.graph_objs import Heatmap, Layout, Font

stream_id = tls.get_credentials_file()['stream_ids'][3]

stream = py.Stream(stream_id)
stream.open()

anno_text = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
layout = Layout(annotations=[dict(
        text=anno_text,  # set annotation text
        showarrow=False, # remove arrow 
        xref='paper',  # use paper coords
        yref='paper',  #  for both coordinates
        x=0.95,  # position's x-coord
        y=1.05,  #   and y-coord
        font=Font(size=14),    # increase font size (default is 12)
        bgcolor='#FFFFFF',     # white background
        borderpad=4            # space bt. border and text (in px)
        )])
x = ['a', 'b', 'c', 'd']
y = ['x', 'y', 'z']
z = np.random.randn(3, 4)
trace = Heatmap(z=z, x=x, y=y)
stream.write(trace, layout=layout)

stream.close()
