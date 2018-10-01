from BL import constants, net, strings, commands, login
import requests


def start():
    print(strings.GREETING)
    chk = net.check_server()
    if chk == requests.codes.not_found:
        print(strings.NOT_FOUND)
        exit(1)
    print(strings.FOUND)


def _login():
    while 1:
        constants.PASS = input(strings.INPUT_KEY)
        print(strings.ATTEMPTING_LOGIN)
        res = login.login_attempt(constants.PASS)
        if res.answer_code == requests.codes.not_found:
            print(strings.NOT_FOUND)
            exit(1)
        elif res.answer_code == requests.codes.unauthorized:
            print(strings.WRONG_KEY)
        elif res.answer_code == requests.codes.ok:
            print(strings.SUCCESS_LOGIN)
            break
        else:
            print(strings.UNKNOWN_ERROR)
    return


def menu():
    while 1:
        print(strings.MENU)
        i = 0
        for a in strings.CHOOSE_MENU.values():
            print(str(i) + ' ' + a)
            i += 1
        try:
            req = int(input())
            print(strings.CHOOSE_MENU[req])
            run_command(req)
        except ValueError:
            print(strings.INVALID_TUPLE_KEY)
        except KeyError:
            print(strings.INVALID_TUPLE_KEY)


def run_command(num):
    if num == constants.OPERATION_KEYS[constants.EXIT]:
        exit(0)
    elif num == constants.OPERATION_KEYS[constants.ADD_CARD]:
        commands.add_card()
    elif num == constants.OPERATION_KEYS[constants.REMOVE_CARD]:
        commands.remove_card()
    elif num == constants.OPERATION_KEYS[constants.ALL_CARDS_ASCII]:
        commands.get_all_ascii()
    elif num == constants.OPERATION_KEYS[constants.ALL_CARDS_BYTE]:
        commands.get_all_byte()
