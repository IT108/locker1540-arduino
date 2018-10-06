import postgresql
import constants


def init():
    constants.DB = postgresql.open('pq://' + constants.username + ':' + constants.password + '@' + constants.DBIP
                                   + ':5432/' + constants.DBName)


def get_card(card):
    resp = constants.DB.query('select active from public.users where card = \'' + card + '\'')
    if resp.__len__() > 0:
        return resp[0][0]
    else:
        return False


def get_greet(card):
    resp = constants.DB.query('select greeting from public.users where card = \'' + card + '\'')
    if resp.__len__() > 0:
        return resp[0][0]
    else:
        return -1
