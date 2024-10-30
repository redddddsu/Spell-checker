from bs4 import BeautifulSoup
from bs4 import SoupStrainer
import time
import requests

startTime = time.time()

url = "https://www.dictionary.com/list/"


wordList = []


for index in range(97, 123):
    print(chr(index))
    currentPage = 1
    pageOnWebsite = 1

    while(currentPage):
        
        newUrl = url + chr(index) + "/"
        newUrl = newUrl + str(currentPage)

        source = requests.get(newUrl).text
        soup = BeautifulSoup(source, 'lxml')

        emptyPage = False

        badWords = [" ", "&", "'", ".", "/", "-", "–", "ˈ", " "]

        for li in soup.find_all("li", class_= "B9oKmcJ0oEIPzTLS8nGl"):
            pageOnWebsite = int(li.text)

        div = soup.find("div", class_="dDeYl3zUalQgXsSgFtAi")

        for word in div.find_all("a", href=True):
            if all(bad not in word.text for bad in badWords):
                text = word.text.strip()
                wordList.append(word.text)
                emptyPage = True

        if (pageOnWebsite < currentPage):
            print("break")
            break
        else:
            print("Page: " + str(currentPage))
            currentPage += 1

with open("dictionary.txt", "w", encoding="utf-8") as file:
    for i in range(len(wordList)):
        file.write(wordList[i])
        file.write("\n")

print("Scraping complete")
print("--- %s seconds ---" % (time.time() - startTime))
