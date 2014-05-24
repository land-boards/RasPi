#!/usr/bin/env python
from flask import Flask
from pyBits import TalkToAPi
app = Flask(__name__)

ON_OFF = {
    True: 'on',
    False: 'off'
}

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

def toggle_template(led_is_on):
    return templatize(
            ('<h5>Light is %s!</h5>' % ON_OFF[led_is_on]) +
            '<a href="/led/{0}">Turn LED {0}</a>'.format(ON_OFF[not led_is_on]))

@app.route('/led')
def hello_route():
    return templatize(
            '<a href="/led/on">Turn LED on</a>' +
            '<br />' +
            '<a href="/led/off">Turn LED off</a>')

@app.route('/led/<state>')
def change_led_route(state):
    led_is_on = bool(state == 'on')
    TalkToAPi().controlLED(led_is_on)
    return toggle_template(led_is_on)

if __name__ == '__main__':
    app.run()
