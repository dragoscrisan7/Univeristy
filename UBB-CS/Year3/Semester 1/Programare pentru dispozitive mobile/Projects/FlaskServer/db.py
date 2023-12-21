from flask import Flask
import sqlite3


app = Flask(__name__)
conn = sqlite3.connect('goals.sqlite')
cursor = conn.cursor()


sql_query2 = """DROP TABLE goals"""


sql_query = """CREATE TABLE IF NOT EXISTS goals (
    id INTEGER PRIMARY KEY,
    title TEXT NOT NULL,
    description TEXT NOT NULL,
    deadline TEXT NOT NULL,
    is_private BOOLEAN NOT NULL,
    mini_goals TEXT NOT NULL
);
"""
# sql_query = """INSERT INTO goals(id, title, description, deadline, is_private, mini_goals)
# VALUES (123, 'alfa', 'alfa', '10/10/1010', 'false', 'unu,doi')
# """

cursor.execute(sql_query)
