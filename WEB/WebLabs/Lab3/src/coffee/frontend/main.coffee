Backbone.emulateJSON = true

$('form').on 'submit', (e)->
    e.preventDefault()
    titleInput = document.forms[0].title.value

    $.post @action, {title: @title.value, value: @val.value}
    collection.fetch type: 'POST', reset: true, alert ('Check inputs, dude')

$(document).ready ->
    window.collection = new barChartCollection
    collection.fetch type: 'POST', success: ()->
        view = new barChartView collection: collection

    $("form input#val").keydown (e)->
        if not (e.keyCode == 46 or e.keyCode == 8)
            if e.keyCode < 48 or e.keyCode > 57
                e.preventDefault()
