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

def on_off_link(is_on):
    return '<a href="/led/{0}">Turn LED {0}</a>'.format(ON_OFF[is_on])

def toggle_template(led_is_on):
    return templatize(
            ('<h5>Light is %s!</h5>' % ON_OFF[led_is_on]) +
            on_off_link(not led_is_on))

@app.route('/led')
def hello_route():
    return templatize('<br />'.join(on_off_link(i) for i in [True, False]))

@app.route('/led/<state>')
def change_led_route(state):
    led_is_on = state == 'on'
    TalkToAPi().controlLED(led_is_on)
    return toggle_template(led_is_on)

if __name__ == '__main__':
    app.run()
