from tkinter import *
from BL.login import card_login_attempt
import BL.constants
import serial.tools.list_ports
import serial
import graphic.options
from graphic.constants import root
from graphic.constants import card_wait_frame

root.geometry(str(root.winfo_screenwidth()) + 'x' + str(root.winfo_screenheight()))
root.attributes("-fullscreen", True)
mes = StringVar(card_wait_frame, 'Выберите порт')
label = Label(card_wait_frame, {"textvariable": mes, "justify": 'center'})
lb = Listbox(card_wait_frame)
btn = Button(card_wait_frame, {"text": "Считать карту", 'height': 22, 'width': 50})


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
    card = card.decode('utf-8')
    print(card)
    ser.close()
    btn['text'] = "Аунтификация..."
    root.update()
    resp = card_login_attempt(card)
    if not resp:
        btn['text'] = 'Пользователя не существует или ему запрещено изменение базы данных'
        root.update()
    else:
        graphic.options.start()


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
    card_wait_frame.grid_columnconfigure(0, {'minsize': root.winfo_screenwidth()})
    lb.grid(row=2, column=0)
    label.grid(row=1, column=0)
    btn.grid(row=3, column=0)

    card_wait_frame.grid()
    # label.grid({"row": 1, "column": 1, "sticky": W+E})
    root.mainloop()
