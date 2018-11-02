from graphic.constants import root
from graphic.constants import card_wait_frame
from graphic.constants import options_frame
from tkinter import *



def start():
    buttons_padding = 5
    buttons_height = 10
    buttons_width = 50
    buttons = [Button(options_frame, {'text': 'добавить пользователя', 'height': buttons_height, 'width': buttons_width}),
               Button(options_frame,
                      {'text': 'добавить пользовате', 'height': buttons_height, 'width': buttons_width}),
               Button(options_frame,
                      {'text': 'добавить пользоват', 'height': buttons_height, 'width': buttons_width})]

    card_wait_frame.destroy()
    root.update()
    row = 0
    column = 0
    for i in range(3):
        options_frame.grid_columnconfigure(i, {'minsize': buttons_width})
        options_frame.grid_rowconfigure(i, {'minsize': buttons_height})
    for i in buttons:
        i.grid(row=row, column=column)
        row += 1
        if row == 3:
            row = 0
            column += 1

    options_frame.pack()
    root.update()
