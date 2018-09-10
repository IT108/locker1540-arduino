import requests
import constants
from urllib.request import urlopen, URLError
from platform import system as system_name # Returns the system/OS name
from os import system as system_call


def make_request(data):
    # print(data)
    return requests.post(constants.HTTP_START + constants.SERVER_IP, data)


def check_server():
    a = ping(constants.SERVER_IP)
    if a:
        return requests.codes.ok
    else:
        return requests.codes.not_found


def ping(host):

    # Ping parameters as function of OS
    parameters = "-n 1 -w 1" if system_name().lower()=="windows" else "-w 1 -c 1"

    # Pinging
    return system_call("ping " + parameters + " " + host) == 0


def to_http(val):
    return constants.HTTP_START + constants.SERVER_IP + '/' + str(val)
