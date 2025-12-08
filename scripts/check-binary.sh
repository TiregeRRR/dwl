#!/usr/bin/env bash
set -euo pipefail

# Identify tracked files that are not recognized as text or XML and fail if any are found.
status=0
while IFS= read -r -d '' file; do
    mime_type=$(file --mime-type -b "$file")
    case "$mime_type" in
        text/*|application/xml)
            ;; # allowed textual file
        *)
            printf 'Non-text file detected: %s (%s)\n' "$file" "$mime_type" >&2
            status=1
            ;;
    esac
done < <(git ls-files -z)

if [ $status -ne 0 ]; then
    echo "Binary files are not supported; please remove or convert the files listed above." >&2
fi

exit $status
