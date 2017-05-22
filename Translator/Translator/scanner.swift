//
//  File.swift
//  Translator
//
//  Created by Ivan on 4/24/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

import Foundation


let delimiters: [String: Int] = [";": 200,
                                 ".": 201,
                                 ":": 202,
                                 "=": 203,
                                 ">": 204,
                                 "<": 205]

let keywords: [String: Int] = ["PROGRAM": 100,
                               "BEGIN": 101,
                               "END": 102,
                               "VAR": 103,
                               "INTEGER": 104,
                               "FLOAT": 105,
                               "WHILE": 106,
                               "DO": 107,
                               "ENDWHILE": 108,
                               "<=": 109,
                               "<>": 110,
                               ">=": 111]

enum MyError : Error {
    case RuntimeError(String)
}

class Scanner {
    
    var fileName: String
    var attributeArray = Array(repeating:0, count: 128)
    var tableID = [String: Int]()
    var tableContants = [String: Int]()
    var resultTableArray: Array<String> = []
    
    //------------attributes------------
    // 0 - space, eof, eol, etc
    // 1 - 0..9
    // 2 - a-z or A-Z
    // 3 - =, :, ;, ')' - one-character delimeter
    // 4 - <, > - first symbols of complex-delimeters (>=, <>, <=)
    // 5 - '(' - commentary  --> (*.....*)
    // 6 - other
    
    init(aFileName: String) {
        self.fileName = aFileName
        
        for items in 0...128 {
            switch items {
            case 0...32:
                attributeArray[items] = 0
                break
            case 48...58:
                attributeArray[items] = 1
                break
            case 65...90:
                attributeArray[items] = 2
                break
            case 97...122:
                attributeArray[items] = 2
                break
            default:
                break
            }
        }
        attributeArray[40] = 5
        attributeArray[41] = 6
        
        attributeArray[58] = 3
        attributeArray[59] = 3
        attributeArray[46] = 3
        attributeArray[61] = 3
        
        attributeArray[60] = 4
        attributeArray[62] = 4
        
        
    }
    
    func addIDToTable(aToken: String) -> Int {
        if keywords.keys.contains(aToken) {
            return keywords[aToken]!
        } else if delimiters.keys.contains(aToken) {
            return delimiters[aToken]!
        } else if tableID.keys.contains(aToken) {
            return tableID[aToken]!
        } else {
            tableID[aToken] = tableID.count + 1000
            return tableID[aToken]!
        }
    }
    
    func addToConstantTable(aToken: String) -> Int {
        if tableContants.keys.contains(aToken) {
           return tableContants[aToken]!
        } else {
            tableContants[aToken] = tableContants.count + 300
            return tableContants[aToken]!
        }
    }
    
    func fileScanner() throws {
        let location = self.fileName
        if let aStreamReader = StreamReader(path: location) {
            defer {
                aStreamReader.close()
            }
            var resultList :Array<String> = []
            
            var line = aStreamReader.nextLine()
            if ((line) == nil) {
                try throwError(message: "ERROR! File is empty");
            }
            
            var row = 1
            var column = 0
            var multipleLineCommentFlag = false
            
            while (line != nil) {
                let lineLength = (line?.characters.count)!
                var wordBuffer: String = ""
                
                var i = 0
                while 0..<lineLength ~= i {
                    wordBuffer = ""
                    var firstCharacter: Character = line![i]
                    if multipleLineCommentFlag {
                        firstCharacter = "("
                    }
                    switch attributeArray[(firstCharacter.asciiValue)!] {
                    case 0:
                        for j in i..<lineLength {
                            let character: Character = line![j]
                            if attributeArray[character.asciiValue!] == 0 {
                                column += 1
                                i += 1
                            } else {
                                break
                            }
                        }
                    case 1:
                        column += 1
                        i += 1
                        for j in i..<lineLength {
                            let character: Character = line![j]
                            if attributeArray[character.asciiValue!] == 1 {
                                wordBuffer += String(character).uppercased()
                            }
                        }
                        resultList.append("\(addToConstantTable(aToken: wordBuffer)): \(row) \(column) \(wordBuffer)")
                        column += wordBuffer.characters.count - 1
                        i += wordBuffer.characters.count - 1
                    case 2:
                        column += 1
                        for j in i..<lineLength {
                            let character: Character = line![j]
                            if attributeArray[character.asciiValue!] == 2 || attributeArray[character.asciiValue!] == 1 {
                                wordBuffer += String(character).uppercased()
                            } else {
                                break
                            }
                        }
                        resultList.append("\(addIDToTable(aToken: wordBuffer)): \(row) \(column) \(wordBuffer)")
                        column += wordBuffer.characters.count - 1
                        i += wordBuffer.characters.count
                    case 3:
                        column += 1
                        i += 1
                        resultList.append("\(String(delimiters[String(firstCharacter)]!)): \(row) \(column) \(firstCharacter)")
                    case 4:
                        wordBuffer += String((line?[i])!)
                        i += 1
                        wordBuffer += String((line?[i])!)
                        if keywords.keys.contains(wordBuffer) {
                            column += 2
                            resultList.append("\(String(keywords[String(wordBuffer)]!)): \(row) \(column) \(wordBuffer)")
                            i += 1
                        } else {
                            column += 1
                            resultList.append("\(String(delimiters[String(firstCharacter)]!)): \(row) \(column) \(wordBuffer)")
                        }
                    case 5:
                        var flag = false
                        if (!multipleLineCommentFlag) {
                            i += 1
                        }
                        var currentCharacter: Character = line![i]
                        if currentCharacter == "*" || multipleLineCommentFlag {
                            column += 2
                            multipleLineCommentFlag = true
                            while (i < lineLength) {
                                i += 1
                                if i < lineLength {
                                    currentCharacter = (line?[i])!
                                } else {
                                    break
                                }
                                if currentCharacter == "*" {
                                    i += 1
                                    if i < lineLength {
                                        currentCharacter = (line?[i])!
                                    } else {
                                        break
                                    }
                                    
                                    if (currentCharacter == ")") {
                                        multipleLineCommentFlag = false
                                        column += 2
                                        break;
                                    }
                                }
                                column += 1
                            }
                            if flag {
                                try throwError(message: "ERROR: Exepected '*)' but have end of file")
                            }
                            i += 1
                            if i < lineLength {
                                currentCharacter = (line?[i])!
                            }
                        } else {
                            column += 1
                            resultList.append("ERROR \(row) \(column) \(wordBuffer)")
                        }
                    case 6:
                        column += 1
                        resultList.append("ERROR \(row) \(column) \(wordBuffer)")
                        i += 1
                    default:
                        print ("Troubles")
                    }
                }
                
                row += 1
                column = 0
                line = aStreamReader.nextLine()
            }
            self.resultTableArray = resultList
        }
        
    }
    
    func whiteSpaceHandler(line: String, currentRow: Int, currentColumn: Int) -> Void {
        var currentColumn = currentColumn
        for character: Character in line.characters {
            if attributeArray[character.asciiValue!] == 0 {
                currentColumn += 1
            }
        }
    }
    
    func throwError(message: String) throws {
        throw MyError.RuntimeError(message)
    }
}

extension Character {
    var asciiValue: Int? {
        return Int((String(self).unicodeScalars.filter{$0.isASCII}.first?.value)!)
    }
}

extension String {
    
    subscript (i: Int) -> Character {
        return self[self.index(self.startIndex, offsetBy: i)]
    }
    
    subscript (i: Int) -> String {
        return String(self[i] as Character)
    }
    
    subscript (r: Range<Int>) -> String {
        let start = self.index(startIndex, offsetBy: r.upperBound)
        let end = self.index(startIndex, offsetBy: r.lowerBound - r.upperBound)
        return self[Range(start ..< end)]
    }
}

		
