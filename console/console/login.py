import requests
import constants
from urllib.request import urlopen, URLError


def login_attempt(key):
    print('login_attempt')
    status = check_server()
    print(status)
    if status == requests.codes.not_found:
        pack = constants.ServerAnswer(requests.codes.ok)
        return pack
    ans = requests.get(constants.LOGIN_URL + key)
    if ans.status_code == requests.codes.ok:
        pack = constants.ServerAnswer(requests.codes.ok, ans.text)
        return pack
    else:
        pack = constants.ServerAnswer(requests.codes.unauthorized)
        return pack


def check_server():
    a = ping(constants.HTTP_START + constants.SERVER_IP)
    if (a):
        print("Server is reachable")
        return requests.codes.ok
    else:
        return requests.codes.not_found


def ping(host):
    try:
        urlopen(host, timeout=3)
        return True
    except URLError as a:
        print(a.strerror)
        return False
