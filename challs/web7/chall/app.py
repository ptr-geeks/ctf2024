from flask import Flask, render_template_string, request, redirect
import random
import string
import os

app = Flask(__name__)
db = {}

def randkey(l):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=l))

@app.route('/')
def index():
    return render_template_string('''
    <html>
    <head>
        <title>Simple URL shortner</title>
    </head>
    <body>
        <h1>Simple URL shortner</h1>
        <form action="/new" method="post">
            <label for="domain">Domain:</label><br>
            <input type="text" id="domain" name="domain" placeholder="google.com"><br>
            <input type="submit" value="Submit">
        </form>
    </body>
    </html>
    ''')

@app.route('/new', methods=['POST'])
def new():
    domain = request.form.get('domain')
    if not domain.startswith('http://') and  not domain.startswith('https://'):
        domain = 'https://' + domain
    key = randkey(5)
    db[key] = domain

    return render_template_string(f'''
    <html>
    <head>
        <title>Simple URL shortner</title>
    </head>
    <body>
        <h1>Simple URL shortner</h1>
        <p>Your short URL for <b>{domain}</b> is: <a href="/s/{key}">https://short.ctf.ptr.si/s/{key}</a></p>
    </body>
    </html>
    ''')

@app.route('/s/<key>')
def shortner(key):
    print(key)
    domain = db.get(key)
    if domain:
        return redirect(domain)
    return 'Not found', 404

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8000)
