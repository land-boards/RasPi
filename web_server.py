#!/usr/bin/env python
from flask import Flask
from pyBits import TalkToAPi
app = Flask(__name__)

HTML_TEMPLATE = """
<html>
<head>
</head>
<body>
    %s
</body>
</html>
"""

def templatize(body):
    return HTML_TEMPLATE % body

@app.route('/led')
def hello_route():
    return templatize(
            '<a href="led/on">Turn LED On</a>' +
            '<br />' +
            '<a href="led/off">Turn LED Off</a>')

@app.route('/led/<state>')
def turn_led_on_route(state):
    led_is_on = bool(state == 'on')
    TalkToAPi().controlLED(led_is_on)
    return templatize('<h5>Light is %s!</h5>' % ('on' if led_is_on else 'off'))

if __name__ == '__main__':
    app.run()
