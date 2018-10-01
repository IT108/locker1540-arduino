from tkinter import *
from BL.login import card_login_attempt
import BL.constants
import serial.tools.list_ports
import serial


root = Tk()
root.geometry(str(root.winfo_screenwidth()) + 'x' + str(root.winfo_screenheight()))
mes = StringVar(root, 'Выберите порт')
label = Label(root, {"textvariable": mes, "justify": 'center'})
lb = Listbox()
btn = Button(root, {"text": "Считать карту", 'height': 22, 'width': 50})


def listen_card():
    com = BL.constants.SERIAL_PORT
    if com == '':
        btn['text'] = 'Выберите порт'
        root.update()
        return
    print('reading card')
    try:
        ser = serial.Serial(com, timeout=5)
    except EXCEPTION:
        btn['text'] = 'Что-то пошло не так'
        root.update()
        return
    btn['text'] = 'Читаю карту'
    root.update()
    card = ser.read(9)
    card = card[1:]
    print(card)
    ser.close()
    btn['text'] = "Аунтификация..."
    root.update()
    card_login_attempt(card)


btn['command'] = listen_card


def on_select_list(val):
    sender = val.widget
    idx = sender.curselection()
    value = sender.get(idx)
    print(value)
    BL.constants.SERIAL_PORT = value
    mes.set("Нажмите кнопку \'считать карту\'")
    btn['text'] = "Считать карту"
    root.update()


def start():
    serials = [comport.device for comport in serial.tools.list_ports.comports()]
    for i in serials:
        lb.insert(END, i)
    lb.bind("<<ListboxSelect>>", on_select_list)
    btn.bind(listen_card)
    label.pack()
    lb.pack()
    btn.pack()
    # label.grid({"row": 1, "column": 1, "sticky": W+E})
    root.mainloop()
