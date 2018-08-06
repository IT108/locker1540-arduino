HTTP_START = 'http://'
SERVER_IP = '192.168.1.38'
PASS = '12345'
CARDS_FILE = "CARDS.txt"
ALL_CARDS_URL = HTTP_START + SERVER_IP + '/' + PASS + '/GC'
LOGIN_URL = HTTP_START + SERVER_IP + '/' + 'LA/'
FULL_DB_URL = HTTP_START + SERVER_IP + '/' + PASS + '/FD'
TOKEN = ""


class ServerAnswer:
    def __init__(self, code, data='null'):
        self.answer_code = code
        self.data = data


class cardPair:
    def __init__(self, code, name='null', card='null'):
        self.name = name
        self.card = card
        self.code = code

