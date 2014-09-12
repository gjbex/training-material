#!/usr/bin/env python

import plotly.plotly as py
import plotly.tools as tls
from plotly.graph_objs import Stream, Data, Figure, Scatter, Layout

stream_id = tls.get_credentials_file()['stream_ids'][0]

stream = Stream( token=stream_id, maxpoints=50)

trace = Scatter(x=[], y=[], mode='lines+markers', stream=stream)
data = Data([trace])
layout = Layout(title='Streaming test')

figure = Figure(data=data, layout=layout)

unique_url = py.plot(figure, filename='stream_test', auto_open=False)
print 'Plot URL: {0}'.format(unique_url)

