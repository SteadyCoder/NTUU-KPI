from django.conf.urls import url

from  . import views

urlpatterns = [
    url(r'^$', views.home, name='downloads'),
    url(r'^downloads$', views.home, name='downloads'),
    url(r'^apps$', views.apps_show, name='apps'),
    url(r'^users$', views.users_show, name='users'),

    url(r'^downloads/edit/(?P<app_id>[0-9]+)/$', views.download_edit, name='edit_downloads'),
    url(r'^apps/edit/(?P<app_id>[0-9]+)/$', views.app_edit, name='edit_apps'),
    url(r'^users/edit/(?P<app_id>[0-9]+)/$', views.user_edit, name='edit_users'),

    url(r'^downloads/new/$', views.download_new, name='download_new'),
    url(r'^apps/new/$', views.app_new, name='app_new'),
    url(r'^users/new/$', views.user_new, name='user_new'),

]

