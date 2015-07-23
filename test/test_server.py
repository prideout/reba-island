from subprocess import Popen, PIPE
import pytest
import requests
import os.path

TIMEOUT = 5


@pytest.fixture(scope='module')
def renderfarm(request):
    import time
    child = Popen(['python', 'src/server.py'], stdout=PIPE, bufsize=1)
    time.sleep(0.5)
    request.addfinalizer(lambda: child.terminate())
    return child


def test_server(renderfarm):
    payload = open('test/example.json').read()
    headers = {'content-type': 'application/json'}
    req = requests.post(
        'http://0.0.0.0:8082/render',
        data=payload,
        headers=headers)
    imgid = req.text
    path = imgid + '.png'
    assert os.path.exists(path)
    os.unlink(path)
