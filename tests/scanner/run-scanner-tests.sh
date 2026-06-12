#!/bin/bash

cd ../..
make
cd tests/scanner

failed=0
passed=0

RED='\e[31m'
GREEN='\e[32m'
YELLOW='\e[33m'
BLUE='\e[34m'
NC='\e[0m'

for file in *.dy; do
    if [ -f "$file" ]; then
        printf "${BLUE}Testing${NC}: $file\n"
        
        ../../bin/dusty $file > .result-$file.tmp
        res=$(rg --count-matches "error" .result-$file.tmp)

        if [ -n "$res" ]; then
            if [[ $file =~ expect* ]]; then
                printf "${GREEN}PASS${NC} (expected error)\n"
                ((passed++))
            else
                printf "${RED}FAIL${NC}\n"
                ((failed++))
            fi
        else 
            printf "${GREEN}PASS${NC}\n";
            ((passed++))
        fi

        echo
    fi
done

printf "${GREEN}$passed${NC} tests passed, ${RED}$failed${NC} tests failed\n"

shopt -s dotglob
rm *.tmp
shopt -u dotglob
