TJ SCT Grader 2.1
Puneeth Uttla, 2013 adapted from Sreenath Are, 2012

USAGE

./grader {judge} {user} {task} {lang}

judge
    judging program to be used - use `default' for standard USACO-style problems
lang
    one of {c,cpp,java,python2,python3}

FOLDERS

judges
    contains judge programs.
data
    contains a folder containing test data for each task
submissions
    put submissions here, filename should be {user}_{task}.{c|cpp|java|python2|python3}

COMPILATION
    first compile libsandbox (in lib/libsandbox), then run src/build.sh


