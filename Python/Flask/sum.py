#!/usr/bin/env python

from flask import Flask, request, render_template

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def start():
    if request.method == 'POST':
        op1 = float(request.form['op1'])
        op2 = float(request.form['op2'])
        result = op1 + op2
        return render_template('sum.html', op1=op1, op2=op2, result=result)
    else:
        return render_template('sum.html')

if __name__ == '__main__':
    app.run()
