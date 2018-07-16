import sys
from PyQt5 import QtWidgets
import requests
from PyQt5.QtWidgets import QMessageBox

import ui.login
import login


class ConsoleApp(QtWidgets.QMainWindow, ui.login.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.loginBtn.clicked.connect(self.login_with_key)

    def login_with_key(self):
        a = login.login_attempt(self.keyInputLine.text())
        print(a.answer_code)
        if a.answer_code == requests.codes.not_found:
            QMessageBox.question(self, 'Message', "Server not found!", QMessageBox.Yes, QMessageBox.Yes)


def main():
    app = QtWidgets.QApplication(sys.argv)
    window = ConsoleApp()
    window.show()
    app.exec()


if __name__ == '__main__':
    main()
