from django import forms
from .custom_models import *

downloadController = DownloadController("download")
appController = AppController("app")
developerController = DeveloperConrtoller("developer")
userController = UserController("user")

class DownloadForm(forms.Form):
    user_id = forms.ChoiceField(label='User name', choices=userController.get_choice_lst())
    date_time = forms.DateTimeField(label='Date time')

class UserForm(forms.Form):
    name = forms.CharField(label='Name', max_length=50)
    e_mail = forms.CharField(label='E-mail', max_length=50)
    phone = forms.CharField(label='Phone', max_length=50)

class AppForm(forms.Form):
    dev_id = forms.ChoiceField(label='Developer', choices=developerController.get_choice_lst())
    name = forms.CharField(label='Name', max_length=50)
    price = forms.CharField(label='Price', max_length=50)
    memory = forms.CharField(label='Memory', max_length=50)

class DeveloperForm(forms.Form):
    name = forms.CharField(label='Name', max_length=50)
    company = forms.CharField(label='Company', max_length=50)

