import requests
import constants


def get_all_cards():
    allcards = requests.get(constants.ALL_CARDS_URL)
    allcards = allcards.text.split(';')
    allcards = allcards[1:len(allcards) - 1]
    return allcards


def write_cards_to_file():
    myFile = open(constants.CARDS_FILE, 'w')
    cards = get_all_cards()
    print(len(cards))
    for i in cards:
        print(i)
        myFile.write(i)
        myFile.write('\n')
    myFile.close()


write_cards_to_file()
