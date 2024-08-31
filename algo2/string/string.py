

def isUniqueChars(s):
    char_set = [False] * 256
    for c in s:
        if (char_set[ord(c)]):
            return False
        char_set[ord(c)] = True
    return True

if __name__ == '__main__':
    test_string = "abcdef"
    print("The {0} string is unique chars {1}".format(test_string, isUniqueChars(test_string)))