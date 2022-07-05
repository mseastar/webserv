import os
import string
import random
import sqlite3


def get_nav():
    nav = str()
    if os.environ.get('LOGIN') is None:
        with open('pages/nav.html') as html:
            for row in html:
                nav += row
    else:
        with open('pages/nav_log.html') as html:
            for row in html:
                nav += row
    return nav


def get_head_html(title):
    head = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{title}</title>
    <link rel="stylesheet" href="/bootstrap5/css/bootstrap.min.css" />
    <script src="/bootstrap5/js/bootstrap.min.js"></script>
</head>
"""
    return head


def get_logins():
    with open("users.txt", 'r') as file:
        lst = file.read().split('\n')
        return lst


def get_passwords():
    with open("passwords.txt", 'r') as file:
        lst = file.read().split('\n')
        return lst


def get_response():
    tmp = """HTTP/1.1 {status}\r
Server: {server}\r
Content-Type: {cont_type}\r
Content-Length: {cont_len}"""
    return tmp


def get_body(header):
    tmp = """<body>
    <h1 class="display-3" style="margin-left:10px;"> {header} </h1>
{nav}
   """.format(nav=get_nav().format(login=os.environ.get('LOGIN'),
                                   server=os.environ['SERVER_NAME']),
              header=header)
    return tmp


def get_auth():
    data = os.environ['COOKIE'].split(';')
    dicti = dict()
    for i in data:
        i = i.split('=')
        if len(i) == 2:
            dicti[i[0].strip()] = i[1].strip()
    if not all([dicti.get('login'), dicti.get('auth-key')]):
        return False
    with sqlite3.connect("cgi-bin/web.db") as conn:
        cur = conn.cursor()
        cur.execute(f"SELECT users.auth_key FROM users WHERE users.login = '{dicti.get('login')}';")
        res = cur.fetchone()
        if res is None or res[0] != dicti.get('auth-key'):
            return False
        os.environ['LOGIN'] = dicti.get('login')
    return True


def generate_random_string():
    letters = string.ascii_letters
    rand_string = ''.join(random.choice(letters) for i in range(32))
    return rand_string

def check_uniq(img_path):
    with sqlite3.connect("cgi-bin/web.db") as conn:
        cur = conn.cursor()
        cur.execute(f"SELECT * FROM posts WHERE img_path='{img_path}';")
        result = cur.fetchone()
        if result is None:
            return True
    return False
