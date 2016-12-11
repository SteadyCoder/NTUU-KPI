from django import forms

class DownloadForm(forms.Form):
    app_id = forms.IntegerField(label='app_id')
    user_id = forms.IntegerField(label='user_id')
    date_time = forms.DateTimeField(label='date_time')

class UserForm(forms.Form):
    user_id = forms.IntegerField(label='user_id')
    name = forms.
