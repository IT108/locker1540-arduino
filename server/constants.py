import postgresql
DBIP = '217.61.106.178'
username = 'locker'
password = 'locker1540'
DBName = 'locker'
DB = postgresql.open('pq://' + username + ':' + password + '@' + DBIP + ':5432/' + DBName)
