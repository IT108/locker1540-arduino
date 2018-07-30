# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'cardsView.ui'
#
# Created by: PyQt5 UI code generator 5.11.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.verticalLayoutWidget.setGeometry(QtCore.QRect(19, 19, 761, 561))
        self.verticalLayoutWidget.setObjectName("verticalLayoutWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.removeUser = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.removeUser.setEnabled(False)
        self.removeUser.setCheckable(False)
        self.removeUser.setDefault(False)
        self.removeUser.setObjectName("removeUser")
        self.horizontalLayout.addWidget(self.removeUser)
        self.addUser = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.addUser.setObjectName("addUser")
        self.horizontalLayout.addWidget(self.addUser)
        spacerItem = QtWidgets.QSpacerItem(400, 20, QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.UsersTable = QtWidgets.QTableWidget(self.verticalLayoutWidget)
        self.UsersTable.setObjectName("UsersTable")
        self.UsersTable.setColumnCount(2)
        self.UsersTable.setRowCount(0)
        item = QtWidgets.QTableWidgetItem()
        self.UsersTable.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.UsersTable.setHorizontalHeaderItem(1, item)
        self.UsersTable.horizontalHeader().setDefaultSectionSize(250)
        self.verticalLayout.addWidget(self.UsersTable)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.removeUser.setText(_translate("MainWindow", "Delete user"))
        self.addUser.setText(_translate("MainWindow", "New user"))
        item = self.UsersTable.horizontalHeaderItem(0)
        item.setText(_translate("MainWindow", "Name, Surname"))
        item = self.UsersTable.horizontalHeaderItem(1)
        item.setText(_translate("MainWindow", "UID"))

