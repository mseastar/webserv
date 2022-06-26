import sqlite3

conn = sqlite3.connect("web.db")
cur = conn.cursor()
cur.execute("SELECT users.id FROM users WHERE login = 'qwerty';")
result = cur.fetchone()
if result is None:
    print("Пользователя не существует")
else:
    author = result[0]
    cur.execute(f"""INSERT INTO comments(text, post_ref, author) 
        VALUES 
        (?, ?, ?);""", ("БОЛЬШЕ КОММЕНТОВ!>!!!", 3, author))
    conn.commit()
