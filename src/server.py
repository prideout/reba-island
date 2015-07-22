#!/usr/bin/env python

from bottle import get, post, run, request
import time
import json
import island


@get('/')
def get_root():
    return "Try doing a POST to /render."


@post('/render')
def post_render():
    now = time.strftime("%y%m%d%H%M%S")
    renderspec = request.json
    renderspec['filename'] = now + '.png'
    island.generate(json.dumps(renderspec))
    return now

run(host='0.0.0.0', port=8082, debug=True)
