#!/bin/bash

# Cleanup script for fixing double-encoded HTML in documentation files
# Usage: ./cleanup_html.sh

DOCS_DIR="/sgoinfre/mkurkar/commandos0x2a/minishell/docs"

echo "🧹 Cleaning up HTML encoding issues in documentation..."

# List of HTML files to clean
HTML_FILES=(
    "index.html"
    "architecture.html" 
    "tokenizer.html"
    "execution.html"
    "builtins.html"
    "resources.html"
)

for file in "${HTML_FILES[@]}"; do
    filepath="$DOCS_DIR/$file"
    if [[ -f "$filepath" ]]; then
        echo "  📄 Processing $file..."
        
        # Fix common double-encoding issues
        sed -i.bak \
            -e 's/<span class="<span class="\([^"]*\)"[^>]*>\([^<]*\)<\/span>/<span class="\1">\2<\/span>/g' \
            -e 's/code-keyword"> case of  <span class="<span[^>]*>/code-keyword">case<\/span> of <span class="code-keyword">/g' \
            -e 's/<span class="code-keyword"><span class="code-keyword">\([^<]*\)<\/span><\/span>/<span class="code-keyword">\1<\/span>/g' \
            "$filepath"
        
        # Remove backup file
        rm -f "$filepath.bak"
        
        echo "    ✅ Cleaned $file"
    else
        echo "    ❌ File not found: $file"
    fi
done

echo ""
echo "✨ HTML cleanup complete!"
echo "🌐 Open the documentation in your browser to verify the fixes."
echo "💡 If you still see issues, you can also run this in the browser console:"
echo "   MinishellDocs.cleanupHTML()"
