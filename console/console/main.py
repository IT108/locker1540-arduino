import sys
from PyQt5 import QtWidgets
import requests
from PyQt5.QtWidgets import QMessageBox, QDialog, QMainWindow, QTableWidgetItem

import ui.cardsView
import ui.login
import ui.addUserDialog
import login
import getFullDB
import constants


class AddUserDialog(QDialog, ui.addUserDialog.Ui_Dialog):
    def __init__(self):
        super().__init__()
        self.setupUi(self)


class CardsView(QMainWindow, ui.cardsView.Ui_MainWindow):
    def __init__(self):
        a = getFullDB.get_db()
        i = 0
        if a[0].code != requests.codes.bad:
            for q in a:
                self.UsersTable.setItem(i, 0, QTableWidgetItem(q.name))
                self.UsersTable.setItem(i, 1, QTableWidgetItem(q.card))
        super().__init__()
        self.setupUi(self)
        self.addUser.clicked.connect(self.add_user)

    def add_user(self):
        self.window = AddUserDialog()
        self.window.show()


class ConsoleApp(QtWidgets.QMainWindow, ui.login.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.loginBtn.clicked.connect(self.login_with_key)

    def login_with_key(self):
        a = login.login_attempt(self.keyInputLine.text())
        if a.answer_code == requests.codes.not_found:
            QMessageBox.question(self, 'Message', "Server not found!", QMessageBox.Yes, QMessageBox.Yes)
        elif a.answer_code == requests.codes.unauthorized:
            QMessageBox.question(self, 'Message', "Wrong key!", QMessageBox.Yes, QMessageBox.Yes)
        elif a.answer_code == requests.codes.ok:
            print(a.answer_code)
            constants.TOKEN = a.data
            self.close()
            self.window = CardsView()
            self.window.show()


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = ConsoleApp()
    window.show()
    app.exec()


if __name__ == '__main__':
    main()
