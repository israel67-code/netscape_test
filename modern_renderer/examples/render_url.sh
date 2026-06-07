#!/bin/bash

# Fetch URL and render with modern renderer

set -e

echo "=== Modern Blink Renderer - URL Rendering Tool ==="
echo ""

if [ $# -eq 0 ]; then
    echo "Usage: $0 <url> [output_file]"
    echo ""
    echo "Examples:"
    echo "  $0 https://example.com"
    echo "  $0 https://example.com output.html"
    exit 1
fi

URL="$1"
OUTPUT_FILE="${2:-rendered_page.html}"
TEMP_FILE=$(mktemp)

echo "URL: $URL"
echo "Output: $OUTPUT_FILE"
echo ""

echo "Downloading HTML..."
if command -v curl &> /dev/null; then
    curl -s "$URL" -o "$TEMP_FILE"
elif command -v wget &> /dev/null; then
    wget -q "$URL" -O "$TEMP_FILE"
else
    echo "Error: curl or wget not found"
    exit 1
fi

echo "Rendering..."
BUILD_DIR="$(cd "$(dirname "$0")/../build" && pwd)"

if [ ! -f "$BUILD_DIR/headless_renderer" ]; then
    echo "Building renderer..."
    cd "$(dirname "$0")/.."
    ./build.sh
fi

$BUILD_DIR/headless_renderer "$TEMP_FILE" "$OUTPUT_FILE"

rm "$TEMP_FILE"

echo ""
echo "✓ Done! Check $OUTPUT_FILE"
