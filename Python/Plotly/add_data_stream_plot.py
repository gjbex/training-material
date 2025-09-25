#!/usr/bin/env python

import datetime
import math
import random
import time
import plotly.plotly as py
import plotly.tools as tls

stream_id = tls.get_credentials_file()['stream_ids'][0]

stream = py.Stream(stream_id)
stream.open()
N = 200

for i in range(1, N + 1):
    x = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    y = math.sin(2.0*math.pi*i/15.0) + random.gauss(0.0, 0.2)
    stream.write(dict(x=x, y=y))
    time.sleep(1.0)

stream.close()
