import postgresql
DBIP = '217.61.106.178'
username = 'locker'
password = 'locker1540'
DBName = 'locker'
DB = postgresql.open('pq://' + username + ':' + password + '@' + DBIP + ':5432/' + DBName)


# ------------------------------------------------DATASETS------------------------------------------------ #

# -------------------------------STUDENTS------------------------------- #
students_morning = [2, 3, 4, 5]
students_day = [1, 2, 3, 5]
students_evening = [2, 3, 5]
# -------------------------------TEACHERS------------------------------- #
teachers_morning = [2, 4, 5]
teachers_day = [1, 2, 5]
teachers_evening = [2, 5]
