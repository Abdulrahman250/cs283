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

@test "Check exit command works" {
    run ./dsh <<EOF
exit
EOF

    [ "$status" -eq 0 ]
}

@test "Check stop-server command works" {
    run ./dsh -c 127.0.0.1 <<EOF
stop-server
EOF

    [ "$status" -eq 0 ]
}

@test "Check pwd runs without errors" {
    run ./dsh <<EOF                
pwd
EOF

    [ "$status" -eq 0 ]
}

@test "Check echo runs without errors" {
    run ./dsh <<EOF                
echo "Hello World!"
EOF

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

@test "Handle empty commands" {
    run ./dsh <<EOF
    
EOF

    [[ "$output" == *"warning: no commands provided"* ]]
}

