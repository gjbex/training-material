#!/usr/bin/env python

from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def start():
    return '<h1>Action is <a href="hello">here</a>!</h1>'

@app.route('/hello/')
@app.route('/hello/<name>')
def hello(name=None):
    return render_template('hello.html', name=name)

if __name__ == '__main__':
    app.run()
