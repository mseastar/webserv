#!/usr/bin/env python3

from functions import *
import hashlib

get_auth()
cookie = ""
body = get_body()
form_text = """<form method="post">
        <p><input type="text" name="login" required minlength="8" maxlength="16" placeholder="Login" autocomplete="false"></p>
        <p><input type="password" name="password" required minlength="8" maxlength="16" placeholder="Password""></p>
        <input type="submit" value="Войти">
    </form>"""
form_text_field = """<form method="post">
        <p><input type="text" name="login" required minlength="8" maxlength="16" placeholder="Login" autocomplete="false" value="{login}"></p>
        <p><input type="password" name="password" required minlength="8" maxlength="16" placeholder="Password""></p>
        <input type="submit" value="Войти">
    </form>"""
if os.environ['REQUEST_METHOD'] == 'GET':
    body += form_text
    main_page = get_head_html('Вход в систему') + body + "</body>\n</html>"
else:
    data = os.environ['QUERY_STRING'].split('&')
    dicti = dict()
    for i in data:
        i = i.split('=')
        dicti[i[0]] = i[1]
    login = dicti.get('login')
    password = dicti.get('password')
    if not all([login, password]) or len(data) != 2:
        body += "<h2>КОГО НАЕБАТЬ ХОЧЕШЬ?</h2>\n" + form_text
        main_page = get_head_html('Вход в систему') + body + "</body>\n</html>"
    else:
        conn = sqlite3.connect("cgi-bin/web.db")
        cur = conn.cursor()
        cur.execute(f"SELECT users.password, users.id, users.auth_key, users.salt FROM users WHERE users.login = '{login}';")
        res = cur.fetchone()
        if res is None:
            body += "<h2>Такого логина не существует</h2>\n" + form_text
            main_page = get_head_html('Вход в систему') + body + "</body>\n</html>"
        elif res[2] is not None:
            body += "<h2>Вы уже вошли в систему</h2>\n"
            main_page = get_head_html('Упс') + body + "</body>\n</html>"
        else:
            user_pass = res[0]
            user_id = res[1]
            user_salt = res[3]
            password = hashlib.pbkdf2_hmac('sha256',
                                           password.encode('utf-8'),
                                           user_salt, 100000)
            if user_pass == password:
                auth_key = generate_random_string()
                cur.execute(f"""UPDATE users
                    SET auth_key='{auth_key}' 
                    WHERE id = {user_id};""")
                conn.commit()
                body = "<body>\n<h2>Вы вошли в систему</h2>"
                main_page = get_head_html('Успешно') + body + "</body>\n</html>"
                cookie += f"\nSet-Cookie:login={login};Max-Age=1000;\r\nSet-Cookie:auth-key={auth_key}"
            else:
                body += "<h2>Неверный пароль</h2>\n" + form_text_field.format(login=login)
                main_page = get_head_html('Неудача') + body + "</body>\n</html>"

print(get_response().format(status="200 OK",
                            server=os.environ['SERVER_NAME'],
                            cont_type=os.environ['CONTENT_TYPE'],
                            cont_len=len(main_page.encode('utf-8'))) + cookie +
      "\r\n\r\n" + main_page, end='')
