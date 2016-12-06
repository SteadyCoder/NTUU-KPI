from django.conf.urls import url

from  . import views

urlpatterns = [
    url(r'^$', views.home, name='downloads'),
    url(r'^downloads$', views.home, name='downloads'),
    url(r'^apps$', views.apps_show, name='apps'),
    url(r'^users$', views.users_show, name='users'),
]

