#!/usr/local/bin/python3

from functions import *
if not get_auth():
    with open("error_pages/403.html", 'r') as file:
        main_page = file.read()
        print(get_response().format(status="403 Forbidden",
                                    server=os.environ['SERVER_NAME'],
                                    cont_len=len(main_page.encode('utf-8')),
                                    cont_type=os.environ['CONTENT_TYPE']) + f"\nSet-Cookie:user={os.environ.get('LOGIN')};Max-age=0" + "\r\n\r\n" + main_page, end='')
else:
    body = get_body()
    body += """<h1>Главная страница</h1>\n """
    for i in os.environ.keys():
        body += "\t<p>" + i + ":" + os.environ[i] + '</p>\n'
    conn = sqlite3.connect("cgi-bin/web.db")
    cur = conn.cursor()
    cur.execute("""SELECT posts.img_path,  users.login, posts.date_post, posts.id
                FROM posts
                JOIN users ON posts.author = users.id;""")
    for i in cur.fetchall():
        body += f"\n<br>\n<br>\n<p>Название статьи: {i[0]}\nАвтор: {i[1]}\nДата публикации: {i[2]}</p>"
        cur.execute(f"""SELECT c.text, u.login FROM posts
            LEFT JOIN comments c on posts.id = c.post_ref
            LEFT JOIN users u on c.author = u.id
            WHERE posts.id={i[3]};""")
        res = cur.fetchall()
        body += "<p>Комментарии:</p>"
        for j in res:
            body += f'<p>Автор: {j[1]}, Текст: {j[0]}</p>'
    main_page = get_head_html('Домашняя страница') + body + "</body>\n</html>"
    print(get_response().format(status="200 OK",
                                server=os.environ['SERVER_NAME'],
                                cont_len=len(main_page.encode('utf-8')),
                                cont_type=os.environ['CONTENT_TYPE']) +
          "\r\n\r\n" + main_page, end='')