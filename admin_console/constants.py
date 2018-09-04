HTTP_START = 'http://'
SERVER_IP = '192.168.1.38'
PASS = '12345'
CARDS_FILE = "CARDS.txt"
ALL_CARDS_ASCII = 'GA'
ALL_CARDS_BYTE = 'GB'
LOGIN = 'LA'
FULL_DB = 'FD'
ADD_CARD = 'AC'
REMOVE_CARD = "RC"
TOKEN = ""
OPERATION_KEYS = {'AC': 1, 'RC': 2, 'GA': 3, 'GB': 4, 'LA': 5}


class ServerAnswer:
    def __init__(self, code, data='null'):
        self.answer_code = code
        self.data = data


class CardPair:
    def __init__(self, code, name='null', card='null'):
        self.name = name
        self.card = card
        self.code = code

