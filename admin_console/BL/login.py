import requests
from BL import constants, net


def login_attempt(key):
    status = net.check_server()
    print(status)
    if status == requests.codes.not_found:
        pack = constants.ServerAnswer(requests.codes.not_found)
        return pack
    ans = net.make_request({'id': constants.OPERATION_KEYS[constants.LOGIN], 'key': key})
    if ans.status_code == requests.codes.ok:
        pack = constants.ServerAnswer(requests.codes.ok, ans.text)
        return pack
    else:
        pack = constants.ServerAnswer(requests.codes.unauthorized)
        return pack


def card_login_attempt(key):
    print("card_attempt")


