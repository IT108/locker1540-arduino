HTTP_START = 'http://'
SERVER_IP = '192.168.1.38'
PASS = '12345'
CARDS_FILE = "CARDS.txt"
ALL_CARDS_URL = HTTP_START + SERVER_IP + '/' + PASS + '/GC'
LOGIN_URL = HTTP_START + SERVER_IP + '/' + 'LA/'


class ServerAnswer:
    def __init__(self, code, data='null'):
        self.answer_code = code
        self.data = data

