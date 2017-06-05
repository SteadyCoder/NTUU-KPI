function interactTd() {
    $('td').on('click', function() {
        var $this = $(this);
        var $input = $('<input>', {
            value: $this.text(),
            type: 'text',
            blur: function() {
                $this.text(this.value);
            },
            keyup: function(e) {
                if (e.which === 13) $input.blur();
            }
        }).appendTo($this.empty()).focus();
    });
}


function interactTh() {
    $('th').on('click', function() {
        var $this = $(this);
        var $input = $('<input>', {
            value: $this.text(),
            type: 'text',
            blur: function() {
                $this.text(this.value);
            },
            keyup: function(e) {
                if (e.which === 13) $input.blur();
            }
        }).appendTo($this.empty()).focus();
    });
}

function createTable() {
    var prettyTable = document.getElementById('prettyTable');
    var table = document.createElement('table')
    table.id = "superTable";

    var rows = document.getElementById('Rows').value;
    var columns = document.getElementById('Columns').value;

    var tableHead = document.createElement('thead');
    table.appendChild(tableHead);


    for (var i = 0; i < columns; ++i) {
        var th = document.createElement('th');
        th.appendChild(document.createTextNode("Column title"));
        tableHead.appendChild(th);
    }

    var tableBody = document.createElement('tbody');
    table.appendChild(tableBody);

    for (var i = 0; i < rows; ++i) {
        var tr = document.createElement('tr');
        tableBody.appendChild(tr);
        for (var j = 0; j < columns; ++j) {
            var td = document.createElement('td');
            td.appendChild(document.createTextNode("Cell text"));
            tr.appendChild(td);
        }
        tr.insertCell(j).innerHTML = '<input type="button" value = "Delete" onClick="Javacsript:deleteRow(this)">';
    }
    prettyTable.appendChild(table);
    alert(table.rows.length);
    interactTh();
    interactTd();
}

function addRow() {
    var table = document.getElementById('superTable');
    var numOfRows = table.rows.length;
    var row = table.insertRow(numOfRows);

    var columns = table.rows[0].cells.length;
    for (var i = 0; i < columns; ++i) {
        row.insertCell(i).innerHTML = "Cell text";
    }
    row.insertCell(i).innerHTML = '<input type="button" value = "Delete" onClick="Javacsript:deleteRow(this)">';
}


function deleteRow(obj) {
    var index = obj.parentNode.parentNode.rowIndex;
    var table = document.getElementById('superTable');
    table.deleteRow(index);
}

function load() {
    console.log("Page load finished");
}