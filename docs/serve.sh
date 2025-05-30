#!/bin/bash

# Minishell Documentation Server
# Serves the documentation website locally for development and testing

DOCS_DIR="/sgoinfre/mkurkar/commandos0x2a/minishell/docs"
PORT=8000

echo "🚀 Starting Minishell Documentation Server..."
echo "📁 Serving from: $DOCS_DIR"
echo "🌐 URL: http://localhost:$PORT"
echo "📱 Mobile URL: http://$(hostname):$PORT (if accessible)"
echo ""
echo "Press Ctrl+C to stop the server"
echo "================================================"

# Check if Python 3 is available
if command -v python3 &> /dev/null; then
    cd "$DOCS_DIR"
    python3 -m http.server $PORT
elif command -v python &> /dev/null; then
    cd "$DOCS_DIR"
    python -m http.server $PORT
else
    echo "❌ Python not found. Please install Python or serve the files manually."
    echo "💡 Alternative: Open file://$DOCS_DIR/index.html directly in your browser"
    exit 1
fi
