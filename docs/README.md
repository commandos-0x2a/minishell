# Minishell Documentation Website

A comprehensive, interactive documentation website for the Minishell project built with modern web technologies.

## 🌟 Features

### Core Documentation
- **Homepage**: Project overview with flow diagrams and quick examples
- **Architecture**: Detailed project structure and component relationships
- **Tokenizer**: Step-by-step tokenization process with visual examples
- **Execution**: Command execution flow and pipeline handling
- **Built-ins**: Documentation of all built-in commands
- **Resources**: External links to GNU, Unix, and shell programming resources

### Interactive Features
- **🌙 Dark Mode Toggle**: Switch between light and dark themes (persisted in localStorage)
- **🔍 Smart Search**: Real-time search across all documentation content
- **📋 Table of Contents**: Floating TOC with scroll spy for easy navigation
- **🎨 Syntax Highlighting**: Enhanced code highlighting for C and shell examples
- **📱 Responsive Design**: Optimized for desktop, tablet, and mobile devices
- **✨ Animations**: Smooth page transitions and interactive elements

### Visual Elements
- **Mermaid Diagrams**: Interactive flowcharts and architectural diagrams
- **Color-coded Tokens**: Visual representation of tokenization process
- **Modern Typography**: Google Fonts integration (Inter + JetBrains Mono)
- **TailwindCSS Styling**: Clean, modern, and consistent design

## 🚀 Getting Started

### Local Development
1. Clone the repository and navigate to the docs folder:
   ```bash
   cd /sgoinfre/mkurkar/commandos0x2a/minishell/docs/
   ```

2. Serve the files using a local server:
   ```bash
   # Using Python (recommended)
   python3 -m http.server 8000
   
   # Using Node.js (if you have it)
   npx serve .
   
   # Using PHP (if available)
   php -S localhost:8000
   ```

3. Open your browser and navigate to:
   ```
   http://localhost:8000
   ```

### Direct File Access
You can also open the files directly in your browser:
```
file:///sgoinfre/mkurkar/commandos0x2a/minishell/docs/index.html
```

## 📁 File Structure

```
docs/
├── index.html          # Homepage with project overview
├── architecture.html   # Project structure and components
├── tokenizer.html      # Tokenization process documentation
├── execution.html      # Command execution flow
├── builtins.html       # Built-in commands reference
├── resources.html      # External resources and links
├── css/
│   └── custom.css      # Enhanced styling and theme system
├── js/
│   └── custom.js       # Interactive features and functionality
└── README.md          # This documentation
```

## 🎯 Key Enhancements

### Theme System
- **Automatic Detection**: Respects system preferences
- **Manual Toggle**: Floating button in top-right corner
- **Persistent Storage**: Remembers your choice across sessions
- **Complete Coverage**: All components adapt to theme changes

### Search Functionality
- **Instant Results**: Real-time search as you type
- **Content Indexing**: Searches through all headings and paragraphs
- **Contextual Results**: Shows relevant sections with highlighted matches
- **Keyboard Friendly**: Accessible and responsive input

### Navigation Enhancements
- **Floating TOC**: Always visible on larger screens
- **Scroll Spy**: Highlights current section automatically
- **Smooth Scrolling**: Enhanced user experience
- **Mobile Optimized**: Adapts to smaller screens

### Code Enhancement
- **Syntax Highlighting**: Automatic C and shell code highlighting
- **Custom Styling**: Enhanced readability with proper fonts
- **Interactive Examples**: Hover effects and visual feedback
- **Copy-friendly**: Easy to select and copy code snippets

## 🛠 Technical Details

### Dependencies
- **TailwindCSS**: Utility-first CSS framework (CDN)
- **Animate.css**: CSS animation library (CDN)
- **Mermaid**: Diagram and flowchart generation (CDN)
- **Google Fonts**: Inter (text) and JetBrains Mono (code)

### Browser Support
- Modern browsers (Chrome, Firefox, Safari, Edge)
- Progressive enhancement for older browsers
- Mobile-first responsive design

### Performance
- **Optimized Loading**: Minimal external dependencies
- **Lazy Features**: Interactive elements load on demand
- **Efficient Rendering**: CSS-only animations where possible
- **Fast Search**: Optimized indexing and matching algorithms

## 📖 Usage Guide

### Navigation
- Use the main navigation bar to switch between sections
- Click the floating TOC items for quick section jumping
- Use the search box to find specific content quickly

### Interactive Features
- **Theme Toggle**: Click the moon/sun icon in the top-right
- **Search**: Type in the search box and click results to navigate
- **Code Blocks**: Hover over code for enhanced highlighting
- **Diagrams**: Interact with Mermaid diagrams (zoom, pan)

### Mobile Experience
- **Responsive Layout**: Content adapts to screen size
- **Touch-friendly**: Buttons and links sized for touch
- **Simplified TOC**: Hidden on mobile to save space
- **Optimized Performance**: Reduced animations on slower devices

## 🔧 Customization

### Adding New Pages
1. Create a new HTML file in the docs directory
2. Include the standard header with CSS/JS references
3. Add navigation links to all existing pages
4. Follow the established design patterns

### Extending Features
- **Custom CSS**: Add styles to `css/custom.css`
- **JavaScript**: Extend functionality in `js/custom.js`
- **New Themes**: Extend the theme system with additional color schemes
- **Enhanced Search**: Add more sophisticated search algorithms

### Configuration
- **Mermaid Themes**: Customize diagram appearance
- **Animation Speed**: Adjust Animate.css timing
- **Color Schemes**: Modify CSS custom properties
- **Typography**: Change font selections and sizing

## 🔧 Troubleshooting

### Syntax Highlighting Issues

If you encounter double-encoding problems in syntax highlighting (like `code-keyword">else "code-keyword">if`), use these debugging tools:

#### Browser Console Commands
```javascript
// Check for encoding issues
MinishellDocs.debugEncodingIssues()

// Clean up and re-highlight all code
MinishellDocs.cleanupHTML()
```

#### Shell Scripts
```bash
# Run comprehensive HTML cleanup
./fix_encoding.sh

# Basic HTML cleanup
./cleanup_html.sh
```

#### Common Issues
- **Double-encoded spans**: Fixed automatically by the cleanup functions
- **Malformed HTML**: Use `debugEncodingIssues()` to identify problems
- **Broken syntax highlighting**: Run `cleanupHTML()` to reset and re-highlight

#### Test Pages
- `test_syntax.html`: Interactive debugging interface
- `test_fix.html`: Automated testing for encoding fixes

### Performance Issues
- **Slow loading**: Check network tab for large assets
- **Animation lag**: Reduce Animate.css usage or disable animations
- **Search delays**: Increase debounce timing in search configuration

### Browser Compatibility
- **Modern browsers**: Full feature support
- **Legacy browsers**: Graceful degradation for core functionality
- **Mobile devices**: Responsive design adapts automatically

## 🤝 Contributing

To contribute to the documentation:

1. **Content Updates**: Edit the relevant HTML files
2. **Style Changes**: Modify `css/custom.css`
3. **Feature Additions**: Extend `js/custom.js`
4. **Testing**: Verify changes across different browsers and devices

### Best Practices
- **Consistency**: Follow existing patterns and conventions
- **Accessibility**: Ensure features work with screen readers
- **Performance**: Test loading times and responsiveness
- **Documentation**: Update this README for significant changes

## 📄 License

This documentation website is part of the Minishell project and follows the same licensing terms.

## 🙏 Acknowledgments

- **Mermaid**: For excellent diagram generation
- **TailwindCSS**: For rapid UI development
- **Animate.css**: For smooth animations
- **Google Fonts**: For beautiful typography

---

**Note**: This documentation website was designed to be both informative and interactive, providing multiple ways to explore and understand the Minishell project architecture and implementation.
