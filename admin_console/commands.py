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
    name = input(strings.INPUT_NAME)
    return net.make_request({'id': constants.OPERATION_KEYS[constants.ADD_CARD], 'key': constants.PASS, 'card': __card,
                             'name': name})


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
    id = constants.OPERATION_KEYS[constants.ALL_CARDS_ASCII]
    ans = net.make_request({'id': id, 'key': constants.PASS})
    ans = ans.text.split(';')
    q = 1
    for i in ans:
        if i.__len__() == 8:
            print(str(q) + '. ' + i)
            q += 1
    return ans


def get_all_byte():
    id = constants.OPERATION_KEYS[constants.ALL_CARDS_BYTE]
    ans = net.make_request({'id': id, 'key': constants.PASS})
    ans = ans.text.split(';')
    q = 1
    for i in ans:
        if i.__len__() > 2:
            print(str(q) + '. ' + i)
            q += 1
    return ans


def isValid(val):
    val = str(val)
    if val.__len__() == 8:
        return True
    return False
