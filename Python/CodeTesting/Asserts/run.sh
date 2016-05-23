#!/bin/bash

echo '# run with assertions enabled (default):'
python ./fac.py
echo '# --------------------'
echo '# run with assertions disabled (-O optimization flag):'
python -O ./fac.py
