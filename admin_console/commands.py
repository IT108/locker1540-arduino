import constants
import strings
import net


def add_card():
    __card = ''
    while 1:
        __card = input(strings.INPUT_CARD).upper()
        if isValid(__card):
            break
        print(strings.INVALID_CARD)
    return net.make_request({'id': constants.OPERATION_KEYS[constants.ADD_CARD], 'key': constants.PASS, 'card': __card})


def remove_card():
    __card = ''
    while 1:
        __card = input(strings.INPUT_CARD).upper()
        if isValid(__card):
            break
        print(strings.INVALID_CARD)
    return net.make_request({'id': constants.OPERATION_KEYS[constants.REMOVE_CARD], 'key': constants.PASS,
                             'card': __card})


def get_all_ascii():
    return net.make_request({id: constants.OPERATION_KEYS[constants.ALL_CARDS_ASCII], 'key': constants.PASS})


def get_all_byte():
    return net.make_request({id: constants.OPERATION_KEYS[constants.ALL_CARDS_BYTE], 'key': constants.PASS})


def isValid(val):
    val = str(val)
    if val.__len__() == 8:
        return True
    return False
