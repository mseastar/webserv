#!/usr/bin/env python3
from functions import *

data = os.environ['QUERY_STRING'].split('&')
dicti = dict()
for i in data:
    i = i.split('=')
    dicti[i[0]] = i[1]
post_id = int(dicti.get('id_post'))
conn = sqlite3.connect("cgi-bin/web.db")
cur = conn.cursor()
cur.execute(f"DELETE FROM posts WHERE id = {post_id};")
conn.commit()
print(f"""HTTP/1.1 307 Temporary Redirect\r
Server: {os.environ['SERVER_NAME']}\r
Connection: Closed\r
Location: http://127.0.0.1:8080/profile \r
Content-Length: 0\r\n\r\n""")
