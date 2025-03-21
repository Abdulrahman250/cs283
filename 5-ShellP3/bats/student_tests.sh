#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Simple pipe between two commands" {
    run ./dsh <<EOF
echo "Hello World" | grep "Hello"
exit
EOF
    echo "$output" | grep -q "Hello World"
    [ "$status" -eq 0 ]
}

@test "Multiple pipes between three commands" {
    run ./dsh <<EOF
echo "Hello World" | grep "Hello" | wc -w
exit
EOF
    echo "$output" | grep -q "2"
    [ "$status" -eq 0 ]
}

@test "Pipe with unknown command fails gracefully" {
    run ./dsh <<EOF
echo "Hello World" | foobar | wc -w
exit
EOF
    echo "$output" | grep -qi "No such file"
    [ "$status" -eq 0 ]
}

@test "Pipe with command returning error status" {
    run ./dsh <<EOF
cat nonexistent_file | wc -l
exit
EOF
    echo "$output" | grep -qi "No such file"
    [ "$status" -eq 0 ]
}

@test "Longer pipeline with four commands" {
    run ./dsh <<EOF
echo "a b c d e" | tr ' ' '\n' | grep "c" | wc -l
exit
EOF
    echo "$output" | grep -q "1"
    [ "$status" -eq 0 ]
}


@test "Handles piped commands: echo and grep" {
    run ./dsh <<EOF
echo "Hello World" | grep "World"
exit
EOF
    echo "$output" | grep -q "World"
    [ "$status" -eq 0 ]
}

@test "Multiple commands with semicolon separation execute correctly" {
    run ./dsh <<EOF
echo First; echo Second; echo Third
exit
EOF
    echo "$output" | grep -q "First"
    echo "$output" | grep -q "Second"
    echo "$output" | grep -q "Third"
    [ "$status" -eq 0 ]
}

@test "Unknown command produces an error message" {
    run ./dsh <<EOF
foobar
exit
EOF
    echo "$output" | grep -qi "No such file"
    [ "$status" -eq 0 ]
}

@test "Handles quoted spaces correctly" {
    run ./dsh <<EOF
echo "hello world"
exit
EOF
    echo "$output" | grep -q "hello world"
    [ "$status" -eq 0 ]
}

@test "Built-in cd with valid directory changes directory" {
    run ./dsh <<EOF
cd /tmp
pwd
exit
EOF
    echo "$output" | grep -q "/tmp"
    [ "$status" -eq 0 ]
}

@test "Built-in cd with no arguments does nothing" {
    current_dir=$(pwd)
    run ./dsh <<EOF
cd
pwd
exit
EOF
    echo "$output" | grep -q "$current_dir"
    [ "$status" -eq 0 ]
}

@test "External command with arguments runs correctly" {
    run ./dsh <<EOF
echo External Test
exit
EOF
    echo "$output" | grep -q "External Test"
    [ "$status" -eq 0 ]
}

@test "cd to non-existent directory prints error" {
    run ./dsh <<EOF
cd /nonexistent_directory
exit
EOF
    echo "$output" | grep -qi "No such file"
    [ "$status" -eq 0 ]
}

@test "Whitespace only input warns the user" {
    run ./dsh <<EOF
       
exit
EOF
    echo "$output" | grep -q "warning: no commands provided"
    [ "$status" -eq 0 ]
}

@test "Multiple separate commands execute correctly" {
    run ./dsh <<EOF
echo First
echo Second
exit
EOF
    echo "$output" | grep -q "First"
    echo "$output" | grep -q "Second"
    [ "$status" -eq 0 ]
}

@test "Command with mixed quotes and spaces" {
    run ./dsh <<EOF
echo "Mixed quotes test with spaces"
exit
EOF
    echo "$output" | grep -q "Mixed quotes test with spaces"
    [ "$status" -eq 0 ]
}

@test "Built-in exit command terminates the shell" {
    run ./dsh <<EOF
exit
EOF
    [ "$status" -eq 0 ]
}
