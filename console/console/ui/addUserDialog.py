# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'addUserDialog.ui'
#
# Created by: PyQt5 UI code generator 5.11.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(400, 300)
        self.verticalLayout = QtWidgets.QVBoxLayout(Dialog)
        self.verticalLayout.setObjectName("verticalLayout")
        spacerItem = QtWidgets.QSpacerItem(20, 70, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        self.verticalLayout.addItem(spacerItem)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.cardNumberLine = QtWidgets.QLineEdit(Dialog)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(30)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.cardNumberLine.sizePolicy().hasHeightForWidth())
        self.cardNumberLine.setSizePolicy(sizePolicy)
        self.cardNumberLine.setReadOnly(True)
        self.cardNumberLine.setObjectName("cardNumberLine")
        self.horizontalLayout.addWidget(self.cardNumberLine)
        self.readCard = QtWidgets.QPushButton(Dialog)
        self.readCard.setEnabled(True)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(20)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.readCard.sizePolicy().hasHeightForWidth())
        self.readCard.setSizePolicy(sizePolicy)
        self.readCard.setObjectName("readCard")
        self.horizontalLayout.addWidget(self.readCard)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.Name = QtWidgets.QLineEdit(Dialog)
        self.Name.setInputMask("")
        self.Name.setText("")
        self.Name.setObjectName("Name")
        self.verticalLayout.addWidget(self.Name)
        spacerItem1 = QtWidgets.QSpacerItem(20, 100, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        self.verticalLayout.addItem(spacerItem1)
        self.buttonBox = QtWidgets.QDialogButtonBox(Dialog)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.verticalLayout.addWidget(self.buttonBox)

        self.retranslateUi(Dialog)
        self.buttonBox.accepted.connect(Dialog.accept)
        self.buttonBox.rejected.connect(Dialog.reject)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
        self.cardNumberLine.setPlaceholderText(_translate("Dialog", "номер карты"))
        self.readCard.setText(_translate("Dialog", "считать карту"))
        self.Name.setPlaceholderText(_translate("Dialog", "Фамилия и имя"))

