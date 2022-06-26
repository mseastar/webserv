#!/usr/bin/env python3
import subprocess

from functions import *

if not get_auth():
    subprocess.run(['python3', 'cgi-bin/home.py'])
else:
    print("""HTTP/1.1 301 Moved Permanently\r
    Server: {server}\r
    Location: / \r
    """)
