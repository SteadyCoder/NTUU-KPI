import sys
import json
import MySQLdb as mdb

from datetime import time, timedelta
'''
class DownloadController(object):
    def __init__(self, table_name):
        self.table_name = table_name


    def get_all_downloads(self):
        return 0

    def get_download_with_id(self, app_id):
        return app_id

    def get_download_with_condition(self, condition):
        return condition

class AppController(object):
    def __init__(self, table_name):
        self.table_name = table_name

    def get_all_apps(self):
        return 0

    def get_app_with_id(self, app_id):
        return app_id

    def get_app_with_condition(self, condition):
        return condition

class DeveloperConrtoller(object):
    def __init__(self, table_name):
        self.table_name = table_name

    def get_all_developers(self):
        return 0

    def get_developer_with_id(self, dev_id):
        return dev_id

    def get_developer_with_condition(self, condition):
        return condition

class UserController(object):
    def __init__(self, table_name):
        self.talbe_name = table_name
'''

class AbstractController(object):
    __host__ = 'localhost'
    __user__ = 'root'
    __password__ = ''
    __db__ = 'downloads'

    def __init__(self, table_name, columns):
        self.table_name = table_name
        self.columns = columns

    def get_all(self):
        try:
            connect = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cursor = connnect.cursor(mdb.cursors.DictCusror)
            cursor.execute("select * from %s;" %self.table_name)
            result = cursor.fetchall()
            return result
        except mdb.Error, e:
            print "Error %d, %s" %(e.args[0], e.args[1])
        finally:
            if connect:
                connect.close()

    def get_with_condition(self, condition):
        try:
            connect = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cursor = connect.cursor(mdb.cursors.DictCusror)
            request = "select * from " + self.table_name + " " + condition + ";"
            cursor.execute(request)
            result = cursor.fetchall()
            return result
        except mdb.Error, e:
            print "Error %d, %s" %(e.args[0], e.args[1])
        finally:
            if connect:
                connect.close()

    def delete(self, condition):
        try:
            connect = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cursor = connect.cursor(mdb.cursors.DictCusror)
            request = "delete from " + self.table_name + " " + condition + ";"
            cursor.execute(request)
            connect.commit()
        except mdb.Error, e:
            print "Error %d, %s" %(e.args[0], e.args[1])
        finally:
            if connect:
                connect.close()

    def insert(self, row):
        try:
            connect = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cursor = connect.cursor(mdb.cursors.DictCusror)
            request = "insert into " + self.table_name + "("
            values = "values("
            for column in self.columns:
                request += column + ", "
                values += str(row[column]) + ", "
            request += ")" + values + ";"
            cursor.execute(request)
            connect.commit()
        except mdb.Error, e:
            print "Error %d, %s" %(e.args[0], e.args[1])
        finally:
            if connect:
                connect.close()

    def update(self, row, id, condition):
        try:
            connect = mdb.connect(self.__host__, self.__user__, self.__password__, self.__db__)
            cursor = connect.cursor(mdb.cursors.DictCusror)
            request = "update " + self.table_name + " set "
            for key in row:
                request += key + " = " + row[key]
            if condition:
                request += condition + " ;"
            else:
                request += "where %s = %d;" %(self.columns[0], id)

            cursor.execute(request)
            connect.commit()
        except mdb.Error, e:
            print "Error %d, %s" %(e.args[0], e.args[1])
        finally:
            if connect:
                connect.close()


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