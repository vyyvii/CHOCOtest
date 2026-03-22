#! /bin/bash

success=0
fail=0
try=0

run_test()
{
    ((try++))
    name="$1"
    shift

    if eval "$@"; then
        echo "$name : OK"
        ((success++))
    else
        echo "$name : KO"
        ((fail++))
    fi
}

# ---------------------------
# ERRORS
# ---------------------------
run_test "Too much arguments" "./functional_tests too_much >/dev/null 2>&1; [ \$? -eq 84 ]"

run_test "ls error" \
'echo -e "setenv LANG C\nls nofile" | ./functional_tests 2>&1 | grep -q "No such file or directory"'

run_test "command not found" \
'echo "crash" | ./functional_tests 2>&1 | grep -q "Command not found"'

arm-linux-gnueabi-gcc tests/hello.c -o armbin
run_test "Wrong architecture" \
'echo "./armbin" | ./functional_tests 2>&1 | grep -q "Exec format error"'
rm -f armbin

echo "hello" > hello
chmod 000 hello
run_test "Permission denied" \
'echo "./hello" | ./functional_tests 2>&1 | grep -q "Permission denied"'
rm -f hello

run_test "Not a directory" \
'echo "cd Makefile" | ./functional_tests 2>&1 | grep -q "Not a directory"'

run_test "Is a directory" \
'echo "cat src" | ./functional_tests 2>&1 | grep -q "Is a directory"'

((try++))
./functional_tests & pid=$!
kill -SIGSEGV "$pid"
wait "$pid"
if [ $? -eq 139 ]; then
    echo "SIGSEGV : OK"
    ((success++))
else
    echo "SIGSEGV : KO"
    ((fail++))
fi

gcc tests/fpe.c -o fpe
run_test "Floating exception" \
'echo "./fpe" | ./functional_tests 2>&1 | grep -q "Floating exception"'
rm -f fpe

gcc tests/segf.c -o segf
run_test "Segmentation fault" \
'echo "./segf" | ./functional_tests 2>&1 | grep -q "Segmentation fault"'
rm -f segf

# ---------------------------
# BASICS
# ---------------------------
run_test "cd return code" \
'echo "cd src" | ./functional_tests >/dev/null; [ $? -eq 0 ]'

run_test "exit return code" \
'echo "exit" | ./functional_tests >/dev/null; [ $? -eq 0 ]'

run_test "setenv/unsetenv flow" \
'(echo "setenv test test"; sleep 1; echo "unsetenv test") | ./functional_tests >/dev/null; [ $? -eq 0 ]'

# ---------------------------
# PIPE TESTS
# ---------------------------
run_test "pipe simple" \
'echo "echo hello | cat" | ./functional_tests | grep -q "hello"'

run_test "pipe wc" \
'echo "echo hello | wc -c" | ./functional_tests | grep -q "6"'

run_test "pipe left fail" \
'echo "abc | ls" | ./functional_tests 2>&1 | grep -q "Command not found"'

run_test "pipe right fail" \
'echo "ls | abc" | ./functional_tests 2>&1 | grep -q "Command not found"'

run_test "pipe both fail" \
'echo "abc | def" | ./functional_tests 2>&1 | grep -q "Command not found"'

run_test "pipe multi process" \
'echo "ls | wc -l" | ./functional_tests >/dev/null'

# ---------------------------
# BUILTIN + PIPE
# ---------------------------
run_test "pipe builtin last" \
'echo "ls | cd" | ./functional_tests >/dev/null'

run_test "pipe builtin first" \
'echo "cd / | ls" | ./functional_tests >/dev/null'

run_test "cd in pipe no effect" \
'echo "cd /tmp | pwd" | ./functional_tests | grep -vq "/tmp"'

# ---------------------------
# REDIRECTION TESTS
# ---------------------------
echo "hello" > testfile
run_test "input redirection" \
'echo "cat < testfile" | ./functional_tests | grep -q "hello"'
rm -f testfile

run_test "output redirection" \
'echo "echo hello > outfile" | ./functional_tests && grep -q "hello" outfile'
rm -f outfile

echo "hello" > outfile
run_test "append redirection" \
'echo "echo world >> outfile" | ./functional_tests && grep -q "world" outfile'
rm -f outfile

run_test "missing redirect file" \
'echo "ls >" | ./functional_tests 2>&1 | grep -q "Missing name for redirect"'

run_test "invalid null command redirect" \
'echo "> file" | ./functional_tests 2>&1 | grep -q "Invalid null command"'

# ---------------------------
# AMBIGUOUS / INVALID
# ---------------------------
run_test "ambiguous redirect" \
'echo "ls > file | wc" | ./functional_tests 2>&1 | grep -q "Ambiguous output redirect"'

run_test "double pipe invalid" \
'echo "ls || wc" | ./functional_tests 2>&1 | grep -q "Invalid null command"'

# ---------------------------
# EDGE CASES
# ---------------------------
run_test "empty input" \
'echo "" | ./functional_tests >/dev/null'

run_test "only spaces" \
'echo "   " | ./functional_tests >/dev/null'

run_test "multiple spaces" \
'echo "ls      -l" | ./functional_tests >/dev/null'

# ---------------------------
# SCORE
# ---------------------------
score=$(( success * 100 / try ))
echo "Try: $try/$try ; success: $success/$try ; fails: $fail/$try ; percent: $score%"
