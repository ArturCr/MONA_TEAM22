import requests

URL = "http://192.168.4.1"
page = requests.get(URL)

print(page.text)
