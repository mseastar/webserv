import sqlite3

conn = sqlite3.connect("web.db")
cur = conn.cursor()

img = 'images/2.png'
description = 'Мой второй пост'
cur.execute("SELECT users.id FROM users WHERE login = 'vag';")
result = cur.fetchone()
if result is None:
    print("Пользователя не существует")
else:
    author = result[0]
    cur.execute(f"""INSERT INTO posts(img_path, description, author) 
        VALUES 
        (?, ?, ?);""", (img, description, author))
    conn.commit()
cur.execute('SELECT * FROM posts;')
print(cur.fetchall())
