#!/bin/bash

TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
OUTPUT="matter_poc_snapshot_$TIMESTAMP.txt"
MAX_SIZE=102400   # 100 KB

echo "Creating safe Matter POC snapshot..."

{
  echo "=== MATTER POC SNAPSHOT ==="
  echo "Timestamp: $TIMESTAMP"
  echo ""

  echo "=== MODIFIED FILES (git diff) ==="
  git diff
  echo ""

  echo "=== UNTRACKED FILES (SAFE AUTO MODE) ==="
  git ls-files --others --exclude-standard | while read -r f; do

    # Only allow known safe extensions
    case "$f" in
      *.bb|*.inc|*.conf|*.service|*.sh|*.md|*.txt) ;;
      *) continue ;;
    esac

    # Skip Yocto build output
    case "$f" in
      *tmp/*|*build/*|*deploy/*|*work/*) continue ;;
    esac

    # Skip large files
    SIZE=$(stat -c%s "$f" 2>/dev/null || echo 0)
    if [ "$SIZE" -gt "$MAX_SIZE" ]; then
      echo "----- SKIPPED LARGE FILE: $f -----"
      continue
    fi

    # Ensure text
    if ! file "$f" | grep -q text; then
      echo "----- SKIPPED BINARY FILE: $f -----"
      continue
    fi

    echo ""
    echo "----- BEGIN FILE: $f -----"
    sed 's/^/| /' "$f"
    echo "----- END FILE: $f -----"

  done

  echo ""
  echo "=== END SNAPSHOT ==="
} > "$OUTPUT"

echo "Snapshot saved as $OUTPUT"

