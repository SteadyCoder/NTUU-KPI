import sys
import json
import MySQLdb as mdb

from datetime import time, timedelta


class AbstractController(object):
    __host__ = 'localhost'
    __user__ = 'root'
    __password__ = '1111'
    __db__ = 'downloads'

    def __init__(self, table_name, columns):
        self.table_name = table_name
        self.columns = columns

# **** Get operation with condition****
    def get_with_condition(self, condition):
        try:
            con = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cursor = con.cursor(mdb.cursors.DictCursor)
            request = "select * from " + self.table_name + " " + condition + ";"
            cursor.execute(request)
            result = cursor.fetchall()
            return result
        except mdb.Error, e:
            print "Error %d, %s" %(e.args[0], e.args[1])
        finally:
            if con:
                con.close()
# **************************


# **** Delete operation ****
    def delete(self, condition):
        try:
            connect = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cursor = connect.cursor()
            request = "delete from " + self.table_name + " " + condition + ";"
            cursor.execute(request)
            connect.commit()
        except mdb.Error, e:
            print "Error %d, %s" %(e.args[0], e.args[1])
        finally:
            if connect:
                connect.close()
# **************************

# **** Insert operation ****
    def insert(self, row):
        try:
            connect = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cursor = connect.cursor()
            request = "insert into " + self.table_name + "("
            values = "values('"
            for column in self.columns:
                request += column + ", "
                values += str(row[column]) + "', '"

            request = request[0:-2]
            values = values[0:-3]
            request += ") " + values + ");"

            cursor.execute(request)
            connect.commit()
        except mdb.Error, e:
            print "Error %d, %s" %(e.args[0], e.args[1])
        finally:
            if connect:
                connect.close()
# **************************



# **** Update some row ****
    def update(self, id, row, condition = None):
        try:
            connect = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cur = connect.cursor()
            request = "update " + self.table_name + " set "

            for column in self.columns:
                request += column + "= '" + str(row[column]) + "', "

            request = request[0:len(request) - 2]

            if condition is not None:
                request += condition + " ;"
            else:
                request += " where %s = %s;" %(self.columns[0], id)

            cur.execute(request)
            connect.commit()
        except mdb.Error, e:
            print "Error %d, %s" %(e.args[0], e.args[1])
        finally:
            if connect:
                connect.close()

# **************************

# **** Get operation ****
    def get_all(self):
        return self.get_with_condition("")

    def get_by_id(self, id):
        return self.get_with_condition("WHERE " + self.columns[0] + " = " + str(id))[0]

    def delete_all(self):
        self.delete("")

    def delete_by_id(self, id):
        self.delete("WHERE " + self.columns[0] + " = " + str(id))
# **************************

    def load(self, file_name):
        try:
            connect = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cursor = connect.cursor()
            file_name = '~/Developer/NTUU-KPI/DataBase\ Labs/Lab2/Database/' + file_name
            cursor.execute("LOAD DATA INFILE " + "'" + file_name + "'" + " INTO TABLE " + self.table_name +
                           " FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n'")
            connect.commit()
        except mdb.Error as e:
            print "Error %d, %s" % (e.args[0], e.args[1])
        finally:
            if connect:
                connect.close()
# **************************
    def full_text_search(self, condition):
        try:
            connect = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cursor = connect.cursor(mdb.cursors.DictCursor)
            cursor.execute('SELECT * FROM ' + self.table_name + ' ' + condition)
            return cursor.fetchall()
        except mdb.Error as e:
            print 'ERROR %d %s' % (e.args[0], e.args[1])
        finally:
            if connect:
                connect.close()

# **************************


# ***** Downloadcontroller ******
class DownloadController(AbstractController):
    def __init__(self, table_name):
        self.table_name = table_name
        columns = ["app_id", "user_id", "date_time"]
        super(DownloadController, self).__init__(self.table_name, columns)

    def get_all_downloads(self):
        return super(DownloadController, self).get_all()

    def get_download_with_id(self, download_id):
        return super(DownloadController, self).get_by_id(download_id)

    def get_download_with_condition(self, condition):
        return super(DownloadController, self).get_with_condition(condition)

    def get_choice_lst(self):
        return tuple(tuple([obj["app_id"], obj["user_id"]]) for obj in self.get_all_downloads())

    def full_text_search(self, condition):
        return super(DownloadController, self).full_text_search(condition)

# **************************

# ***** App controller ******
class AppController(AbstractController):
    def __init__(self, table_name):
        self.table_name = table_name
        columns = ["app_id", "dev_id", "name", "price", "memory"]
        super(AppController, self).__init__(self.table_name, columns)

    def get_all_apps(self):
        return super(AppController, self).get_all()

    def get_apps_with_id(self, app_id):
        return super(AppController, self).get_by_id(app_id)

    def get_apps_with_condition(self, condition):
        return super(AppController, self).get_with_condition(condition)

    def get_choice_lst(self):
        return tuple(tuple([obj["app_id"], obj["name"]]) for obj in self.get_all_apps())
# **************************

# ***** User controller ******
class UserController(AbstractController):
    def __init__(self, table_name):
        self.table_name = table_name
        columns = ["user_id", "name", "e_mail", "phone"]
        super(UserController, self).__init__(self.table_name, columns)

    def get_all_users(self):
        return super(UserController, self).get_all()

    def get_user_with_id(self, user_id):
        return super(UserController, self).get_by_id(user_id)

    def get_user_with_condition(self, condition):
        return super(UserController, self).get_with_condition(condition)

    def get_choice_lst(self):
        return tuple(tuple([obj["user_id"], obj["name"]]) for obj in self.get_all_users())
# **************************

# ***** Developer controller ******
class DeveloperConrtoller(AbstractController):
    def __init__(self, table_name):
        self.table_name = table_name
        columns = ["dev_id", "name", "company"]
        super(DeveloperConrtoller, self).__init__(self.table_name, columns)

    def get_all_developers(self):
        return super(DeveloperConrtoller, self).get_all()

    def get_developer_with_id(self, dev_id):
        return super(DeveloperConrtoller, self).get_by_id(dev_id)

    def get_developer_with_condition(self, condition):
        return super(DeveloperConrtoller, self).get_with_condition(condition)

    def get_choice_lst(self):
        return tuple(tuple([obj["dev_id"], obj["name"]]) for obj in self.get_all_developers())
# **************************


class Download(object):
    def __init__(self, app_id, user_id, date_time):
        self.app_id = app_id
        self.user_id = user_id
        self.date = date_time

    def __str__(self):
        return "id: %s, user: %s" %(self.app_id, self.user_id)

    # TO DO: add get time def

class App(object):
    def __init__(self, app_id, dev_id, name, price, memory):
        self.app_id = app_id
        self.dev_id = dev_id
        self.name = name
        self.price = price
        self.memory = memory

    def __str__(self):
        return "id: %s, name: %s" %(self.app_id, self.name)

class Developer(object):
    def __init__(self, name, company):
        self.name = name
        self.company = company

    def __str__(self):
        return "name: %s, company: %s" %(self.name, self.company)

class User(object):
    def __init__(self, name, email, phone):
        self.name = name
        self.email = email
        self.phone = phone

    def __str__(self):
        return "name: %s, e-mail: %s" %(self.name, self.email)