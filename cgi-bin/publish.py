#!/usr/bin/env python3
import os
import html
from functions import *


if not get_auth():
    with open("error_pages/403.html", 'r') as file:
        main_page = file.read()
        print(get_response().format(status="403 Forbidden",
                                    server=os.environ['SERVER_NAME'],
                                    cont_len=len(main_page.encode('utf-8')),
                                    cont_type=os.environ['CONTENT_TYPE']) + "\r\n\r\n" + main_page, end='')
else:
    if os.environ['REQUEST_METHOD'] == 'POST':
        body = get_body()
        data = os.environ['QUERY_STRING'].split('&')
        dicti = dict()
        for i in data:
            i = i.split('=')
            dicti[i[0]] = i[1]
        img_path = html.escape(dicti.get('img_path'))
        description = dicti.get('description')
        if not all([img_path, description]) or len(data) != 2:
            body += f"""<h2>ОШИБКА</h2>"""
            main_page = get_head_html('Ошибка публикации') + body + "</body>\n</html>"
        else:
            conn = sqlite3.connect("cgi-bin/web.db")
            cur = conn.cursor()
            cur.execute(f"SELECT users.id FROM users WHERE login = '{os.environ.get('LOGIN')}';")
            result = cur.fetchone()
            author = result[0]
            cur.execute(f"""INSERT INTO posts(img_path, description, author) 
                VALUES 
                (?, ?, ?);""", (img_path, description, author))
            conn.commit()
            body += f"""<h2>Успешно!</h2>"""
            main_page = get_head_html('Пост опубликован') + body + "</body>\n</html>"
    else:
        body = get_body()
        body += """<h1> Добавить запись </h1>
            <form method="post">
                <p> Путь до изображения <input type="text" name="img_path"></p>
                <p>Описание <textarea name="description"></textarea></p>
                <input type="submit" value="Давай рычи">
            </form>"""
        main_page = get_head_html('Публикация поста') + body + "</body>\n</html>"

    print(get_response().format(status="200 OK",
                                server=os.environ['SERVER_NAME'],
                                cont_len=len(main_page.encode('utf-8')),
                                cont_type=os.environ['CONTENT_TYPE']) +
          "\r\n\r\n" + main_page, end='')


