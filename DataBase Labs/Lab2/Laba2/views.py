from django.shortcuts import render

from django.contrib import  messages
from django.http import HttpResponse
from django.views.generic.base import TemplateView

# Create your views here.

class HomePageView(TemplateView):
    template_name = "Laba2/home.html"

    def get_context_data(self, **kwargs):
        context = super(HomePageView, self).get_context_data(**kwargs)
        # messages.info(self.request, 'http://localhost:8000')
        return context

class DownloadsTable(TemplateView):
    template_name = "Laba2/downloads_table.html"

    def get_context_data(self, **kwargs):
        context = super(DownloadsTable, self).get_context_data(**kwargs)
        return context