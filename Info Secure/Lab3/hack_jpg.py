import random

def compute_bytes(message):
    result = hex(len(message) + 2)
    tmp = '0' * (4 - len(result[2:])) + result[2:]
    return chr(int(tmp[:2], 16)) + chr(int(tmp[2:], 16))



def encode(message, input_file, output_file):
    try:
        with open(input_file, 'rb+') as source_file, open(output_file,'wb') as out:
            lst = source_file.readlines()
            info_place = 4 #random.randint(4, 12)
            print "Info place %d" %info_place

            count = 0
            for item in lst:
                if '\xff' in item and count == info_place:
                    index = item.find('\xff')
                    line = item[:index] + '\xff\xfe' + compute_bytes(message) + message + item[index:]
                    lst[lst.index(item)] = line
                    break
                elif '\xff' in item:
                    count += 1

            for i in lst:
                out.write(i)
    except IOError:
        return False

    return True

def decode(file_name):
    try:
        with open(file_name, 'rb') as f:
            lst = f.readlines()
            secret_word = ''
            for item in lst:
                if '\xff\xfe' in item:
                    first_indx = item.index('\xff\xfe')
                    for letter in item[first_indx:][4:]:
                        if letter != '\xff':
                            secret_word += letter
                        elif letter == '\xff':
                            break
                    break
            return secret_word
    except IOError:
        return ''

# shoud add console menu
# add word separate 

if __name__ == '__main__':

    comment = raw_input('Enter comment: ')
    pict_name = "copy.jpg" #raw_input('Picture name: ')
    pict_decode = "store.jpg" #raw_input('Picture name to store comment: ')

    if (encode(comment, pict_name, pict_decode)):
        print "Success"
        print "Secret word from decode: " + decode(pict_decode)
    else: 
        print "File error"
