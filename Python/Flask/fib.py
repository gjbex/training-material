#!/usr/bin/env python

from flask import Flask, render_template, session

app = Flask(__name__)
app.secret_key = 'A1Zr38g/3yZ R~XGH!jlN]3WX/,?RT'

@app.route('/reset')
def reset():
    session['fib'] = 1
    session['fib_prev'] = 1
    session['number'] = 0
    return render_template('fib.html', number=None)
    
@app.route('/')
def start():
    if 'number' not in session:
        return reset()
    session['number'] += 1
    fib = session['fib']
    session['fib'] += session['fib_prev']
    session['fib_prev'] = fib
    return render_template('fib.html',
                           number=session['number'],
                           fibonacci=session['fib'])

if __name__ == '__main__':
    app.run(threaded=True)
