#!/usr/bin/env python3
from functions import *

if not get_auth():
    with open("error_pages/403.html", 'r') as file:
        main_page = file.read()
        print(get_response().format(status="403 Forbidden",
                                    server=os.environ['SERVER_NAME'],
                                    cont_len=len(main_page.encode('utf-8')),
                                    cont_type=os.environ['CONTENT_TYPE']) + "\r\n\r\n" + main_page, end='')
else:
    body = "<body>\n"
    conn = sqlite3.connect("cgi-bin/web.db")
    cur = conn.cursor()
    login = os.environ.get('LOGIN')
    cur.execute(f"SELECT users.id, users.auth_key FROM users WHERE login = '{login}';")
    res = cur.fetchone()
    id = res[0]
    auth_key = res[1]
    if auth_key is None:
        body += "<h2>КОГО НАБЕАТЬ ПЫТАЕШЬСЯ ТЫ НЕ ЗАЛОГИНЕН БАН НАХУЙ</h2>"
        main_page = get_head_html('БАН') + body + "</body>\n</html>"
    else:
        cur.execute(f"""UPDATE users SET auth_key = NULL WHERE id = {id};""")
        conn.commit()
        body += "<h1>Вы успешно вышли из системы!</h1>"
        main_page = get_head_html('Выход из системы') + body + "</body>\n</html>"

    print(get_response().format(status="200 OK",
                                server=os.environ['SERVER_NAME'],
                                cont_len=len(main_page.encode('utf-8')),
                                cont_type=os.environ['CONTENT_TYPE']) + f"\nSet-Cookie:user={login};Max-age=0" +
          "\r\n\r\n" + main_page, end='')
