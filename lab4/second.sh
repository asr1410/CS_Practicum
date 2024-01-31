#!/bin/bash
for dir in "d1" "d2" "d3" "d4" "d5" "d6" "d7"; do
    cd "$dir" || continue
    cDir=$(basename "$(pwd)")
    for file in *; do
        if [[ "$file" == 2* ]]; then
            cName="${cDir}_$file"
            cp "$file" "../target_directory/${cName}"
        fi
    done
    cd ..
done
