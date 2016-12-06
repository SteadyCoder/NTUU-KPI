from django.shortcuts import render

from django.http import HttpResponse
from .custom_models import DownloadController, AppController, DeveloperConrtoller, UserController

downloadController = DownloadController("download")
appController = AppController("app")
developerController = DeveloperConrtoller("developer")
userController = UserController("user")

downloadController.load('downloads.csv')
appController.load('apps.csv')
developerController.load('developer.csv')
userController.load('users.csv')

def index(request):
    return  HttpResponse("Hello")

def home(request):
    return render(request, "Laba2/home.html", {'downloads': downloadController.get_all_downloads()})

def apps_show(request):
    return render(request, "Laba2/apps_table.html", {'apps': appController.get_all_apps()})

def users_show(request):
    return render(request, "Laba2/users_table.html", {'users': userController.get_all_users()})