import requests
import constants
from urllib.request import urlopen, URLError


def make_request(data):
    # print(data)
    return requests.post(constants.HTTP_START + constants.SERVER_IP, data)


def check_server():
    a = ping(constants.HTTP_START + constants.SERVER_IP)
    if a:
        return requests.codes.ok
    else:
        return requests.codes.not_found


def ping(host):
    try:
        urlopen(host, timeout=3)
        return True
    except URLError:
        return False


def to_http(val):
    return constants.HTTP_START + constants.SERVER_IP + '/' + str(val)
