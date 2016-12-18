import MySQLdb as mdb

db = None
user_name = None

def error_print(error):
    print "Error %d %s" %(error.args[0], error.args[1])

def db_connect(user_n, password):
    global db
    global user_name
    try:
        db = mdb.connect(host='localhost', user=user_n, passwd=password, db='mysql')
        user_name = user_n
    except mdb.Error as e:
        error_print(e)
    print db

def set_password(new_password):
    query = "UPDATE mysql.user SET authentication_string='%s' WHERE user = '%s';" %(new_password, user_name)
    cursor = db.cursor()
    try:
        cursor.execute(query)
    except mdb.Error as e: 
        error_print(e)
    db.commit()
    flush_query = 'FLUSH PRIVILEGES;'
    try: 
        cursor.execute(flush_query)
    except mdb.Error as e:
        error_print(e)
    print 'Password changed'
    cursor.close()

def show_grants():
    query = "SHOW GRANTS;"
    cursor = db.cursor()
    try:
        cursor.execute(query)
    except mdb.Error as e:
        error_print(e)
    result = cursor.fetchall()
    for row in result:
        print row
    cursor.close()

def user_describe(rows_number = None):
    query = "DESCRIBE mysql.user;"
    cursor = db.cursor()
    try:
        cursor.execute(query)
    except mdb.Error as e:
        error_print(e)
    if rows_number is None:
        result = cursor.fetchall()
    else:
        result = cursor.fetchmany(rows_number)
    for row in result:
        print row
    cursor.close()

def user_data():
    query = "SELECT * FROM mysql.user where user = '%s';" %(user_name)
    cursor = db.cursor()
    try:
        cursor.execute(query)
    except mdb.Error as e:
        error_print(e)
    result = cursor.fetchall()
    for row in result:
        print row
    cursor.close()

def close():
    try:
        db.close()
    except mdb.Error as e:
        error_print(e)
