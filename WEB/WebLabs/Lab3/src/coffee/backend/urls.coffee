app.use '/', express.static path.join __dirname, '../..' ,'/build'
app.use '/lib', express.static path.join __dirname, '../..' ,'/node_modules'
app.use '/img', express.static path.join __dirname, '../..' ,'/img'

console.log "Server started at http://localhost:8080/"
app.listen 8080
