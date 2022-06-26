import sqlite3
import os
import hashlib

conn = sqlite3.connect("web.db")
cur = conn.cursor()
login = input('LOGIN:\n')
password = input('PASSWORD:\n')
salt = os.urandom(32)
password = hashlib.pbkdf2_hmac(
    'sha256', password.encode('utf-8'), salt, 100000)
cur.execute(f"SELECT users.login FROM users WHERE users.login='{login}'")
result = cur.fetchone()
if result is not None:
    print('Пользователь с данным логином уже сущетсвует')
else:
    cur.execute(f"""INSERT INTO users(login,password,salt) 
    VALUES
    (?, ?, ?);""", (login, password, salt))
    conn.commit()
    print('Пользователь успешно зарегестрирован')
cur.execute("SELECT users.login FROM users;")
for i in cur.fetchall():
    print(f'Логин: {i[0]}')
# subprocess.run(['python.exe', 'login.py'])
