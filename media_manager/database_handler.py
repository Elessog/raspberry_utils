import sqlite3
import link_class

def clean_name(some_var):
    return ''.join(char for char in some_var if char.isalnum())

class database_handler:
    def __init__(self,database_name):
        self.db_name = database_name
        self.db_conn = None
        self.cur = None

    def connect(self):
        self.db_conn = sqlite3.connect(self.db_name)
        self.cur = self.db_conn.cursor()

    def initialize(self):
        self.cur.execute("SELECT name FROM sqlite_master WHERE type='table';")
        res = self.cur.fetchall()
        print(res[0][0])
        if res==[]:
            self.cur.execute('CREATE TABLE {tn} ({fn} {ft} PRIMARY KEY)'\
        .format(tn='PARAMETERS', fn='LASTENTRY', ft='TEXT'))

    def close(self):
        self.db_conn.close()

if __name__ == '__main__':
    db_handler = database_handler('media.db')
    db_handler.connect()
    db_handler.initialize()
    db_handler.close()
