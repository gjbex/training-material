#!/usr/bin/env python

import datetime, math, random, time

import plotly.plotly as py
import plotly.tools as tls
from plotly.graph_objs import Data, Figure, Scatter, Layout

stream_id = tls.get_credentials_file()['stream_ids'][0]

stream = py.Stream(stream_id)
stream.open()
i = 0
N = 200

while i < N:
    i += 1

    x = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    y = math.sin(2.0*math.pi*i/15.0) + random.gauss(0.0, 0.2)
    stream.write(dict(x=x, y=y))
    time.sleep(1.0)

stream.close()
