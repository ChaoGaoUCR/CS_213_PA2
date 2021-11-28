from os import close
import sys
from operator import itemgetter


def main():
    with open(sys.argv[1]) as textFile1:
        first = textFile1.readline()
    # print(first)

    with open(sys.argv[1]) as textFile:
        next(textFile)
        lines = [line.split() for line in textFile]
        for element in lines:
            element[0] = int(element[0])
            element[1] = int(element[1])
    lines = sorted(lines, key=(lambda x:x[1]))
    with open(sys.argv[1]+ 'csc.txt', 'w+') as textreturn:
        textreturn.write(first)
        for element in lines:
            textreturn.write("%s %s %s\n" % (element[0],element[1],element[2]))

            


if __name__ == "__main__":
    main()
