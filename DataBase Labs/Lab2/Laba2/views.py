from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from .forms import DownloadForm
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

def download_edit(request, app_id):
    if request.method == 'POST':
        if 'delete_btn' in request.POST:
            downloadController.delete_by_id(request.POST["app_id"])
            return HttpResponseRedirect('/downloads')
        else:
            form = DownloadForm(request.POST)
            if form.is_valid():
                row = {"app_id": request.POST["app_id"], "user_id": request.POST["user_id"],
                       "date_time": request.POST["date_time"] }
                print request.POST["app_id"]
                downloadController.update(request.POST["app_id"], row)
                return HttpResponseRedirect('/')
    else:
        download = downloadController.get_by_id(app_id)

        req = {'app_id': download['app_id'], 'user_id': download['user_id'], 'date_time': download['date_time']}
        form = DownloadForm(req)
    context = {'form': form, 'add_object': False, 'title': 'Download Edit'}
    return render(request, 'Laba2/download_edit.html', context)

def app_edit(request, app_id):
    return HttpResponse("Hello")