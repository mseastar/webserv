#!/usr/local/bin/python3
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
    body = get_body()

    path = os.environ.get('FILENAME')
    if os.path.isdir(path):
        for i in os.listdir(path):
            body += f"\t<a href=\"/{path}/{i}\">{path}.{i}</a><br/>\n"
    elif os.path.isfile(path):
        with open(path, 'r') as f:
            for i in f:
                body += html.escape(i) + "<br />\n"

    main_page = get_head_html('autoindex') + body + "</body>\n</html>"

    print(get_response().format(status="200 OK",
                                server=os.environ['SERVER_NAME'],
                                cont_type=os.environ['CONTENT_TYPE'],
                                cont_len=len(main_page.encode('utf-8'))) + "\r\n\r\n" + main_page)
