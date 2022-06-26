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
    if os.environ['REQUEST_METHOD'] == 'POST':
        body = get_body()
        data = os.environ['QUERY_STRING'].split('&')
        firstname = data[0].split('=')[1]
        lastname = data[1].split('=')[1]
        body += f"""<h2>Привет {firstname} {lastname}</h2>"""
        main_page = get_head_html('ФОРМА') + body + "</body>\n</html>"
    else:
        body = get_body()
        body += """<h1> Мой профиль</h1>
            <form method="post">
                <p>Имя <input type="text" name="firstname"></p>
                <p>Фамилия <input type="text" name="lastname"></p>
                <input type="submit" value="Еблуша">
            </form>
            <form action="/upload" method="post" blank="_target" enctype="multipart/form-data">
                <p><input type="file" name="file"></p>
                <input type="submit" value="Upload">
            </form>
            """

        main_page = get_head_html('Мой профиль') + body + "</body>\n</html>"

    print(get_response().format(status="200 OK",
                                server=os.environ['SERVER_NAME'],
                                cont_len=len(main_page.encode('utf-8')),
                                cont_type=os.environ['CONTENT_TYPE']) +
          "\r\n\r\n" + main_page, end='')
