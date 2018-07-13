import requests
myFile = open('CARDS.txt', 'w')
allCards = requests.get('http://192.168.1.38/12345/GC')
allCards = allCards.text.split(';')
allCards = allCards[1:len(allCards) - 1]
i = ''
print(len(allCards))
for i in allCards:
    print(i)
    myFile.write(i)
    myFile.write('\n')
myFile.close()

