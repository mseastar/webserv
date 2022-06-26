import sqlite3

conn = sqlite3.connect("web.db")
cur = conn.cursor()
cur.execute("""SELECT posts.img_path,  users.login, posts.date_post, posts.id
            FROM posts
            JOIN users ON posts.author = users.id
            ;""")
for i in cur.fetchall():
    print(f"Название статьи: {i[0]}\nАвтор: {i[1]}\nДата публикации: {i[2]}")
    cur.execute(f"""SELECT c.text, u.login FROM posts
        LEFT JOIN comments c on posts.id = c.post_ref
        LEFT JOIN users u on c.author = u.id
        WHERE posts.id={i[3]};""")
    res = cur.fetchall()
    print("Комментарии:")
    for j in res:
        print('_____________________________________')
        print('\tАвтор: ' + j[1], '\n\t\tТекст: ' + j[0])
        print('_____________________________________')
    print('#_____________________________________')