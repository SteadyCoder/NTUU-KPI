fs = require 'fs'
xml2js = require 'xml2js'
express = require 'express'
path = require "path"
bodyParser = require 'body-parser'
file = path.join __dirname, '../..', 'barChart.xml'
parser = new xml2js.Parser()

app = express()

extracted = []
titles = []
xml = fs.readFile file, (err, data) ->
    parser.parseString data, (err, result)->
        extracted = result['bar-chart']['bar']
        extracted.map (el)->
            titles.push el.title[0]

app.use bodyParser.json type: 'application/*+json'
app.use bodyParser.urlencoded extended: true
