import postgresql
import postgresql.exceptions

HTTP_START = 'http://'
SERVER_IP = '192.168.1.38'
PASS = ''
CARDS_FILE = "CARDS.txt"
ALL_CARDS_ASCII = 'GA'
ALL_CARDS_BYTE = 'GB'
LOGIN = 'LA'
FULL_DB = 'FD'
ADD_CARD = 'AC'
REMOVE_CARD = "RC"
EXIT = 'EX'
TOKEN = ""
OPERATION_KEYS = {'EX': 0, 'AC': 1, 'RC': 2, 'GA': 3, 'GB': 4, 'LA': 5}
OPERATOR_CARD = ""
SERIAL_PORT = ''
DBIP = '217.61.106.178'
username = 'locker'
password = 'locker1540'
DBName = 'locker'
try:
    DB = postgresql.open('pq://' + username + ':' + password + '@' + DBIP + ':5432/' + DBName)
except postgresql.exceptions.ClientCannotConnectError:
    DB = ''

class ServerAnswer:
    def __init__(self, code, data='null'):
        self.answer_code = code
        self.data = data


class CardPair:
    def __init__(self, code, name='null', card='null'):
        self.name = name
        self.card = card
        self.code = code

