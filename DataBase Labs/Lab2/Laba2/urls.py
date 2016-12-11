from django.conf.urls import url

from  . import views

urlpatterns = [
    url(r'^$', views.home, name='downloads'),
    url(r'^downloads$', views.home, name='downloads'),
    url(r'^apps$', views.apps_show, name='apps'),
    url(r'^users$', views.users_show, name='users'),

    url(r'^downloads/edit/(?P<app_id>[0-9]+)/$', views.download_edit, name='edit'),
    url(r'^apps/edit/(?P<app_id>[0-9]+)/$', views.app_edit, name='edit'),
]

