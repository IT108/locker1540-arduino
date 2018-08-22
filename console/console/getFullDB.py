import requests
import constants


def get_db():
    DB = requests.get(constants.FULL_DB_URL)
    if DB.status_code != requests.codes.ok:
        return [constants.cardPair(requests.codes.bad)]
    DB = DB.text.split(';')
    PairsDB = []
    for a in DB:
        q = a.split('/')
        if q.__len__() > 1:
            PairsDB.append(constants.cardPair(requests.codes.ok, q[0], q[1]))
    print(PairsDB.__len__())
    return PairsDB


get_db()
