import sqlite3


class UnknownConstantError(Exception):
    pass


class ConstantDb(object):

    def __init__(self, file_name='const.db'):
        self._conn = sqlite3.connect(file_name)

    def close(self):
        self._conn.close()

    def init(self):
        constants = {
            'g': (9.81, 'm/s**2'),
            'pi': (3.14, None),
            'mach': (0.00338, 'm/s'),
        }
        cursor = self._conn.cursor()
        cursor.execute('''CREATE TABLE constants (
                              name  TEXT NOT NULL,
                              value REAL NOT NULL,
                              unit  TEXT
                          )''')
        for name, data in constants.items():
            cursor.execute('''INSERT INTO constants
                                  (name, value, unit) VALUES (?, ?, ?)''',
                           (name, data[0], data[1]))
        cursor.execute('''INSERT INTO constants
                              (name, value, unit) VALUES (?, ?, ?)''',
                       ('pi', 3.1415, None))
        self._conn.commit()
        cursor.close()

    def get_value(self, name):
        cursor = self._conn.cursor()
        cursor.execute('''SELECT value FROM constants
                              WHERE name = ?''', (name, ))
        rows = cursor.fetchall()
        cursor.close()
        if not rows:
            msg = "constant '{0}' is undefined".format(name)
            raise UnknownConstantError(msg)
        else:
            return rows[0][0]

    def get_names(self):
        cursor = self._conn.cursor()
        cursor.execute('''SELECT name FROM constants''')
        rows = cursor.fetchall()
        cursor.close()
        return [row[0] for row in rows]

    def get_nr_constants(self):
        return len(self.get_names())
