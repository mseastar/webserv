#!/usr/bin/env python3
import hashlib
from functions import *

def check_form(login, password):
    conn = sqlite3.connect("cgi-bin/web.db")
    cur = conn.cursor()
    salt = os.urandom(32)
    password = hashlib.pbkdf2_hmac(
        'sha256', password.encode('utf-8'), salt, 100000)
    cur.execute(f"SELECT users.login FROM users WHERE users.login='{login}'")
    result = cur.fetchone()
    if result is None:
        cur.execute("""INSERT INTO users(login,password,salt) 
            VALUES
            (?, ?, ?);""", (login, password, salt))
        conn.commit()
        return True
    return False


form_text = """<form method="post">
        <p><input type="text" name="login" required minlength="5" maxlength="16" placeholder="Login" autocomplete="false"></p>
        <p><input type="password" name="password1" required minlength="8" maxlength="16" placeholder="Password""></p>
        <p><input type="password" name="password2" required minlength="8" maxlength="16" placeholder="Confirm password""></p>
        <input type="submit" value="Зарегистрироваться">
    </form>"""
form_text_field = """<form method="post">
            <p><input type="text" name="login" required minlength="5" maxlength="16" placeholder="Login" autocomplete="false" value="{login}"></p>
            <p><input type="password" name="password1" required minlength="8" maxlength="16" placeholder="Password""></p>
            <p><input type="password" name="password2" required minlength="8" maxlength="16" placeholder="Confirm password""></p>
            <input type="submit" value="Зарегистрироваться">
        </form>"""

body = get_body()
if os.environ['REQUEST_METHOD'] == 'GET':
    body += form_text
    main_page = get_head_html('Регистрация') + body + "</body>\n</html>"

else:
    data = os.environ['QUERY_STRING'].split('&')
    dicti = dict()
    for i in data:
        i = i.split('=')
        dicti[i[0]] = i[1]
    login = dicti.get('login')
    password1 = dicti.get('password1')
    password2 = dicti.get('password2')
    if not all([login, password1, password2]) or len(data) != 3:
        body += "<h2>КОГО НАЕБАТЬ ХОЧЕШЬ?</h2>"
        body += form_text
        main_page = get_head_html('Регистрация') + body + "</body>\n</html>"
    elif password1 != password2:
        body += "<h2>КОГО НАЕБАТЬ ХОЧЕШЬ ? ПАРОЛИ НЕ СОВПАДАЮТ</h2>"
        body += form_text_field.format(login=login)
        main_page = get_head_html('Регистрация') + body + "</body>\n</html>"
    elif not check_form(login, password1):
        body += "<h2>Такой пользователь уже существует</h2>"
        body += form_text_field.format(login=login)
        main_page = get_head_html('Ошибка пользователь не создан!') + body + "</body>\n</html>"
    else:
        body += f"<h2>{login} , {password1}, {password2}, {dicti}</h2>"
        main_page = get_head_html('Пользователь успешно создан') + body + "</body>\n</html>"

print(get_response().format(status="200 OK",
                            server=os.environ['SERVER_NAME'],
                            cont_type=os.environ['CONTENT_TYPE'],
                            cont_len=len(main_page.encode('utf-8'))) +
      "\r\n\r\n" + main_page, end='')
