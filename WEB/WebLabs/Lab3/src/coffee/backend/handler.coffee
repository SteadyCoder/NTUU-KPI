app.get '/', (req, res) ->
    res.sendFile path.join __dirname, '../..' ,'/index.html'

app.post '/doc/collection', (req, res)->
    res.send extracted

app.post '/doc/models', (req, res)->
    builder = new xml2js.Builder rootName: 'bar-chart'
    notUniq = false
    titles.map (el)->
        if el is req.body.title
            return notUniq = true
    if req.body.value > 100 or notUniq
        res.status(400).send "Bad Request"
    else
        extracted.push req.body
        xml = builder.buildObject {'bar': extracted}
        fs.writeFile file, xml
        res.send "OK"
