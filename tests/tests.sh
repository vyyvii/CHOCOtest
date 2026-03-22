#! /bin/bash

success=0
fail=0
try=0

# HELP (not here)
# ERRORS
((try++))
./functional_tests too_much
if [ $? -eq 84 ]; then
    echo "Too much arguments : OK"
    ((success++))
else
    echo "Too much arguments : KO"
    ((fail++))
fi

((try++))
if echo "setenv LANG C\nls nofile" | ./functional_tests 2>&1 | grep -q "No such file or directory"; then
    echo "ls error : OK"
    ((success++))
else
    echo "ls error : KO"
    ((fail++))
fi

((try++))
if echo "crash" | ./functional_tests 2>&1 | grep -q "Command not found"; then
    echo "crash error : OK"
    ((success++))
else
    echo "crash error : KO"
    ((fail++))
fi

((try++))
arm-linux-gnueabi-gcc tests/hello.c -o armbin
if echo "./armbin" | ./functional_tests 2>&1 | grep -q "Exec format error"; then
    echo "Wrong architecutre : OK"
    ((success++))
else
    echo "Wrong architecutre : KO"
    ((fail++))
fi
rm armbin

((try++))
echo "hello" > hello
chmod 000 hello
if echo "./hello" | ./functional_tests 2>&1 | grep -q "Permission denied"; then
    echo "Permission denied : OK"
    ((success++))
else
    echo "Permission denied : KO"
    ((fail++))
fi
rm -rf hello

((try++))
if echo "cd Makefile" | ./functional_tests 2>&1 | grep -q "Not a directory"; then
    echo "Not a directory : OK"
    ((success++))
else
    echo "Not a directory : KO"
    ((fail++))
fi

((try++))
if echo "cat src" | ./functional_tests 2>&1 | grep -q "Is a directory"; then
    echo "Is a directory : OK"
    ((success++))
else
    echo "Is a directory : KO"
    ((fail++))
fi

((try++))
./functional_tests &
pid=$!
kill -SIGSEGV "$pid"
wait "$pid"
if [ $? -eq 139 ]; then
    echo "SIGSEGV : OK"
    ((success++))
else
    echo "SIGSEGV : KO (got $status)"
    ((fail++))
fi

((try++))
gcc tests/fpe.c -o fpe
if echo "./fpe" | ./functional_tests 2>&1 | grep -q "Floating exception"; then
    echo "Floating exception (core dumped) : OK"
    ((success++))
else
    echo "Floating exception (core dumped) : KO"
    ((fail++))
fi
rm armbin

((try++))
gcc tests/segf.c -o segf
if echo "./segf" | ./functional_tests 2>&1 | grep -q "Segmentation fault"; then
    echo "Segmentation fault (core dumped) : OK"
    ((success++))
else
    echo "Segmentation fault (core dumped) : KO"
    ((fail++))
fi
rm armbin

# BASICS
((try++))
echo "cd src" | ./functional_tests
if [ $? -eq 0 ]; then
    echo "cd src code  : OK"
    ((success++))
else
    echo "cd src code  : KO"
    ((fail++))
fi

((try++))
echo "exit" | ./functional_tests
if [ $? -eq 0 ]; then
    echo "exit code  : OK"
    ((success++))
else
    echo "exit code  : KO"
    ((fail++))
fi

((try++))
(echo "setenv test test" ; sleep 1 ; echo "unsetenv test") | ./functional_tests
if [ $? -eq 0 ]; then
    echo "setenv test code  : OK"
    ((success++))
else
    echo "setenv test code  : KO"
    ((fail++))
fi

# SCORE
score=$(( success * 100 / $try))
echo "Try: $try/$try ; successs: $success/$try ; Fails: $fail/$try ; Percent: $score%"
