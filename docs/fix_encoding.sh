#!/bin/bash

# Comprehensive HTML encoding fix script
# This script fixes double-encoding issues in all documentation HTML files

DOCS_DIR="/sgoinfre/mkurkar/commandos0x2a/minishell/docs"

echo "🔧 Comprehensive HTML Encoding Fix"
echo "=================================="

# Function to fix file
fix_html_file() {
    local file="$1"
    local filepath="$DOCS_DIR/$file"
    
    if [[ ! -f "$filepath" ]]; then
        echo "  ❌ File not found: $file"
        return 1
    fi
    
    echo "  📄 Processing $file..."
    
    # Create backup
    cp "$filepath" "$filepath.backup"
    
    # Apply comprehensive fixes using sed
    sed -i \
        -e 's/<span class="code-keyword"><span class="code-keyword">\([^<]*\)<\/span><\/span>/<span class="code-keyword">\1<\/span>/g' \
        -e 's/<span class="code-string"><span class="code-string">\([^<]*\)<\/span><\/span>/<span class="code-string">\1<\/span>/g' \
        -e 's/<span class="code-comment"><span class="code-comment">\([^<]*\)<\/span><\/span>/<span class="code-comment">\1<\/span>/g' \
        -e 's/<span class="code-function"><span class="code-function">\([^<]*\)<\/span><\/span>/<span class="code-function">\1<\/span>/g' \
        -e 's/<span class="<span class="\([^"]*\)"[^>]*>\([^<]*\)<\/span>/<span class="\1">\2<\/span>/g' \
        -e 's/code-keyword"> case of  <span class="<span[^>]*>/code-keyword">case<\/span> of <span class="code-keyword">/g' \
        -e 's/<span class="\([^"]*\)"[^>]*><span class="[^"]*">\([^<]*\)<\/span>/<span class="\1">\2<\/span>/g' \
        "$filepath"
    
    # Check if changes were made
    if ! diff -q "$filepath" "$filepath.backup" > /dev/null 2>&1; then
        echo "    ✅ Fixed encoding issues in $file"
        
        # Show what was changed (first few differences)
        echo "    📝 Changes made:"
        diff "$filepath.backup" "$filepath" | head -5 | sed 's/^/      /'
    else
        echo "    ℹ️  No encoding issues found in $file"
    fi
    
    # Remove backup
    rm -f "$filepath.backup"
    
    return 0
}

# List of HTML files to process
HTML_FILES=(
    "index.html"
    "architecture.html"
    "tokenizer.html"
    "execution.html"
    "builtins.html"
    "resources.html"
    "test_syntax.html"
)

echo "📁 Processing HTML files in: $DOCS_DIR"
echo ""

# Process each file
for file in "${HTML_FILES[@]}"; do
    fix_html_file "$file"
done

echo ""
echo "✨ HTML encoding fix complete!"
echo ""
echo "🧪 Testing recommendations:"
echo "  1. Open test_syntax.html to verify syntax highlighting"
echo "  2. Check browser console for any remaining issues"
echo "  3. Use the debug functions in MinishellDocs.debugEncodingIssues()"
echo ""
echo "🌐 Test URLs:"
echo "  • file://$DOCS_DIR/test_syntax.html"
echo "  • file://$DOCS_DIR/builtins.html"
echo "  • file://$DOCS_DIR/index.html"
