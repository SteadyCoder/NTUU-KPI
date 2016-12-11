from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from .forms import DownloadForm, AppForm, UserForm, DeveloperForm
from .custom_models import DownloadController, AppController, DeveloperConrtoller, UserController

downloadController = DownloadController("download")
appController = AppController("app")
developerController = DeveloperConrtoller("developer")
userController = UserController("user")

# downloadController.load('downloads.csv')
# appController.load('apps.csv')
# developerController.load('developer.csv')
# userController.load('users.csv')

def index(request):
    return HttpResponse("Works")

def home(request):
    return render(request, "Laba2/home.html", {'downloads': downloadController.get_all_downloads(), 'users': userController })

def apps_show(request):
    return render(request, "Laba2/apps_table.html", {'apps': appController.get_all_apps()})

def users_show(request):
    return render(request, "Laba2/users_table.html", {'users': userController.get_all_users()})

def download_edit(request, app_id):
    if request.method == 'POST':
        if 'delete_btn' in request.POST:
            downloadController.delete_by_id(app_id)
            return HttpResponseRedirect('/downloads')
        else:
            form = DownloadForm(request.POST)
            if form.is_valid():
                row = {"app_id": app_id, "user_id": request.POST["user_id"],
                       "date_time": request.POST["date_time"]}
                downloadController.update(app_id, row)
                return HttpResponseRedirect('/downloads')
    else:
        download = downloadController.get_by_id(app_id)
        user_id = userController.get_by_id(download['user_id'])['user_id']
        req = {'user_id': user_id, 'date_time': download['date_time']}
        form = DownloadForm(req)
    context = {'form': form, 'add_object': False, 'title': 'Download Edit'}
    return render(request, 'Laba2/download_edit.html', context)


def app_edit(request, app_id):
    if request.method == 'POST':
        if 'delete_btn' in request.POST:
            appController.delete_by_id(request.POST["app_id"])
            return HttpResponseRedirect('/apps')
        else:
            form = AppForm(request.POST)
            if form.is_valid():
                row = {"app_id": app_id, "dev_id": request.POST["dev_id"], "name": request.POST["name"],
                       "price": request.POST["price"], "memory": request.POST["memory"]}
                appController.update(app_id, row)
                return HttpResponseRedirect('/apps')
    else:
        app = appController.get_by_id(app_id)
        dev_id = developerController.get_by_id(app['dev_id'])['dev_id']
        req = {'app_id': app['app_id'], 'dev_id': dev_id, 'name': app['name'], 'price': app['price'], 'memory': app['memory']}
        form = AppForm(req)
    context = {'form': form, 'add_object': False, 'title': 'App Edit'}
    return render(request, 'Laba2/download_edit.html', context)

def user_edit(request, app_id):
    if request.method == 'POST':
        if 'delete_btn' in request.POST:
            userController.delete_by_id(request.POST["user_id"])
            return HttpResponseRedirect('/users')
        else:
            form = UserForm(request.POST)
            if form.is_valid():
                row = {"user_id": request.POST["user_id"], "name": request.POST["name"], "e_mail": request.POST["e_mail"],
                       "phone": request.POST["phone"]}
                userController.update(request.POST["user_id"], row)
                return HttpResponseRedirect('/users')
    else:
        user = userController.get_by_id(app_id)
        req = {'user_id': user['user_id'], 'name': user['name'], 'e_mail': user['e_mail'], 'phone': user['phone']}
        form = UserForm(req)
    context = {'form': form, 'add_object': False, 'title': 'User Edit'}
    return render(request, 'Laba2/download_edit.html', context)


def download_new(request):
    if request.method == 'POST':
        tmp = downloadController.get_all_downloads()
        row = {"app_id": tmp[len(tmp) - 1]["app_id"] + 1, "user_id": request.POST["user_id"],
               "date_time": request.POST["date_time"]}
        downloadController.insert(row)
        return HttpResponseRedirect('/downloads')

    form = DownloadForm()
    context = {'form': form, 'add_object': True, 'title': 'New app'}
    return render(request, 'Laba2/download_edit.html', context)

def app_new(request):
    if request.method == 'POST':
        row = {"app_id": request.POST["app_id"], "dev_id": request.POST["dev_id"],
               "name": request.POST["name"], "price": request.POST["price"], "memory": request.POST["memory"]}
        appController.insert(row)
        return HttpResponseRedirect('/apps')

    form = AppForm()
    context = {'form': form, 'add_object': True, 'title': 'New app'}
    return render(request, 'Laba2/download_edit.html', context)

def user_new(request):
    if request.method == 'POST':
        row = {"user_id": request.POST["user_id"], "name": request.POST["name"],
               "e_mail": request.POST["e_mail"], "phone": request.POST["phone"]}
        userController.insert(row)
        return HttpResponseRedirect('/users')

    form = UserForm()
    context = {'form': form, 'add_object': True, 'title': 'New user'}
    return render(request, 'Laba2/download_edit.html', context)