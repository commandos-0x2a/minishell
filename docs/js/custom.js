// Custom JavaScript for Minishell Documentation

// Theme management
class ThemeManager {
    constructor() {
        this.theme = localStorage.getItem('theme') || 'light';
        this.init();
    }

    init() {
        this.applyTheme();
        this.createThemeToggle();
    }

    applyTheme() {
        document.body.setAttribute('data-theme', this.theme);
        localStorage.setItem('theme', this.theme);
    }

    toggleTheme() {
        this.theme = this.theme === 'light' ? 'dark' : 'light';
        this.applyTheme();
        this.updateToggleIcon();
    }

    createThemeToggle() {
        const toggle = document.createElement('button');
        toggle.className = 'theme-toggle';
        toggle.innerHTML = this.theme === 'light' ? '🌙' : '☀️';
        toggle.onclick = () => this.toggleTheme();
        document.body.appendChild(toggle);
    }

    updateToggleIcon() {
        const toggle = document.querySelector('.theme-toggle');
        if (toggle) {
            toggle.innerHTML = this.theme === 'light' ? '🌙' : '☀️';
        }
    }
}

// Table of Contents generator
class TOCGenerator {
    constructor() {
        this.headings = [];
        this.init();
    }

    init() {
        this.collectHeadings();
        if (this.headings.length > 2) {
            this.createTOC();
            this.setupScrollSpy();
        }
    }

    collectHeadings() {
        this.headings = Array.from(document.querySelectorAll('h2, h3, h4'))
            .map((heading, index) => {
                if (!heading.id) {
                    heading.id = `heading-${index}`;
                }
                return {
                    id: heading.id,
                    text: heading.textContent,
                    level: parseInt(heading.tagName.substring(1))
                };
            });
    }

    createTOC() {
        const tocContainer = document.createElement('div');
        tocContainer.className = 'toc-container';
        
        const tocTitle = document.createElement('div');
        tocTitle.className = 'toc-title';
        tocTitle.textContent = 'Table of Contents';
        tocContainer.appendChild(tocTitle);

        this.headings.forEach(heading => {
            const link = document.createElement('a');
            link.href = `#${heading.id}`;
            link.className = 'toc-link';
            link.textContent = heading.text;
            link.style.paddingLeft = `${(heading.level - 2) * 8 + 8}px`;
            link.onclick = (e) => {
                e.preventDefault();
                document.getElementById(heading.id).scrollIntoView({
                    behavior: 'smooth'
                });
            };
            tocContainer.appendChild(link);
        });

        document.body.appendChild(tocContainer);
    }

    setupScrollSpy() {
        const links = document.querySelectorAll('.toc-link');
        const headingElements = this.headings.map(h => document.getElementById(h.id));

        const observer = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                const link = document.querySelector(`a[href="#${entry.target.id}"]`);
                if (entry.isIntersecting) {
                    links.forEach(l => l.classList.remove('active'));
                    link?.classList.add('active');
                }
            });
        }, { threshold: 0.7 });

        headingElements.forEach(heading => {
            if (heading) observer.observe(heading);
        });
    }
}

// Search functionality
class SearchManager {
    constructor() {
        this.searchData = [];
        this.init();
    }

    init() {
        this.createSearchBox();
        this.buildSearchIndex();
    }

    createSearchBox() {
        // Find the main content area to add search
        const main = document.querySelector('main');
        if (!main) return;

        const searchContainer = document.createElement('div');
        searchContainer.className = 'search-container';
        searchContainer.innerHTML = `
            <div style="position: relative;">
                <input type="text" class="search-input" placeholder="Search documentation...">
                <div class="search-icon">🔍</div>
                <div class="search-results" style="display: none;"></div>
            </div>
        `;

        // Insert search box after the first section
        const firstSection = main.querySelector('section');
        if (firstSection) {
            firstSection.insertAdjacentElement('afterend', searchContainer);
        }

        this.setupSearchHandlers();
    }

    buildSearchIndex() {
        // Get all text content from headings and paragraphs
        const elements = document.querySelectorAll('h1, h2, h3, h4, p, li');
        elements.forEach((element, index) => {
            const text = element.textContent.trim();
            if (text.length > 10) {
                this.searchData.push({
                    id: index,
                    text: text,
                    element: element,
                    heading: this.findNearestHeading(element)
                });
            }
        });
    }

    findNearestHeading(element) {
        let current = element;
        while (current && current !== document.body) {
            if (current.tagName?.match(/^H[1-6]$/)) {
                return current.textContent;
            }
            current = current.previousElementSibling || current.parentElement;
        }
        return 'Documentation';
    }

    setupSearchHandlers() {
        const searchInput = document.querySelector('.search-input');
        const searchResults = document.querySelector('.search-results');

        if (!searchInput || !searchResults) return;

        let searchTimeout;
        searchInput.addEventListener('input', (e) => {
            clearTimeout(searchTimeout);
            searchTimeout = setTimeout(() => {
                this.performSearch(e.target.value, searchResults);
            }, 300);
        });

        // Hide results when clicking outside
        document.addEventListener('click', (e) => {
            if (!e.target.closest('.search-container')) {
                searchResults.style.display = 'none';
            }
        });
    }

    performSearch(query, resultsContainer) {
        if (query.length < 2) {
            resultsContainer.style.display = 'none';
            return;
        }

        const results = this.searchData.filter(item =>
            item.text.toLowerCase().includes(query.toLowerCase())
        ).slice(0, 5);

        if (results.length === 0) {
            resultsContainer.innerHTML = '<div class="search-result-item">No results found</div>';
        } else {
            resultsContainer.innerHTML = results.map(result => {
                const highlightedText = this.highlightMatch(result.text, query);
                return `
                    <div class="search-result-item" onclick="document.querySelector('h2, h3, h4').scrollIntoView({behavior: 'smooth'})">
                        <div style="font-weight: 600; font-size: 0.875rem; color: #3b82f6;">${result.heading}</div>
                        <div style="font-size: 0.75rem; margin-top: 4px;">${highlightedText.substring(0, 100)}...</div>
                    </div>
                `;
            }).join('');
        }

        resultsContainer.style.display = 'block';
    }

    highlightMatch(text, query) {
        const regex = new RegExp(`(${query})`, 'gi');
        return text.replace(regex, '<mark style="background-color: yellow;">$1</mark>');
    }
}

// Code syntax highlighting
class CodeHighlighter {
    constructor() {
        this.init();
    }

    init() {
        this.cleanupDoubleEncoding();
        this.highlightCodeBlocks();
    }

    cleanupDoubleEncoding() {
        // Fix double-encoded spans that might exist
        const allElements = document.querySelectorAll('*');
        allElements.forEach(element => {
            let html = element.innerHTML;
            let originalHtml = html;
            
            // Fix the specific pattern you reported
            html = html.replace(/code-keyword">else "code-keyword">if/g, 'code-keyword">else</span> <span class="code-keyword">if');
            html = html.replace(/code-keyword">([^<]+) "code-keyword">/g, 'code-keyword">$1</span> <span class="code-keyword">');
            
            // Fix nested span tags with same class
            html = html.replace(/<span class="code-keyword"><span class="code-keyword">([^<]*)<\/span><\/span>/g, '<span class="code-keyword">$1</span>');
            html = html.replace(/<span class="code-string"><span class="code-string">([^<]*)<\/span><\/span>/g, '<span class="code-string">$1</span>');
            html = html.replace(/<span class="code-comment"><span class="code-comment">([^<]*)<\/span><\/span>/g, '<span class="code-comment">$1</span>');
            html = html.replace(/<span class="code-function"><span class="code-function">([^<]*)<\/span><\/span>/g, '<span class="code-function">$1</span>');
            
            // Fix malformed span opening tags
            html = html.replace(/<span class="<span class="([^"]+)"[^>]*>([^<]+)<\/span>/g, '<span class="$1">$2</span>');
            
            // Fix any remaining malformed spans
            html = html.replace(/<span class="([^"]*)"[^>]*><span class="[^"]*">([^<]*)<\/span>/g, '<span class="$1">$2</span>');
            
            // Fix broken closing tags pattern like ">else "
            html = html.replace(/">([^<]+) "([^"]+)">/g, '>$1</span> <span class="$2">');
            
            // Update element if changes were made
            if (html !== originalHtml) {
                element.innerHTML = html;
                console.log('Fixed encoding in element:', element.tagName, element.className);
            }
        });
    }

    highlightCodeBlocks() {
        const codeBlocks = document.querySelectorAll('code, pre');
        codeBlocks.forEach(block => {
            // Skip if already highlighted or has specific language class
            if (block.classList.contains('highlighted') || 
                block.classList.contains('language-c') ||
                block.classList.contains('language-shell') ||
                block.innerHTML.includes('code-keyword')) {
                return;
            }
            
            // Only highlight if it contains code-like content
            const content = block.textContent || block.innerText;
            if (this.looksLikeCode(content)) {
                this.highlightC(block);
                block.classList.add('highlighted');
            }
        });
    }

    looksLikeCode(content) {
        // Simple heuristic to detect if content looks like code
        const codeIndicators = [
            /\b(int|char|void|if|else|while|for|return|static|const)\b/,
            /[{}();]/,
            /\/\/|\/\*/,
            /\$[A-Z_]+/,
            /echo|ls|cat|grep|cd/
        ];
        
        return codeIndicators.some(regex => regex.test(content));
    }

    highlightC(element) {
        let content = element.innerHTML;
        
        // Skip if already highlighted (prevent double encoding)
        if (content.includes('code-keyword') || content.includes('code-string') || content.includes('code-comment')) {
            return;
        }
        
        // Escape existing HTML entities to prevent conflicts
        content = content.replace(/&lt;/g, '<').replace(/&gt;/g, '>').replace(/&amp;/g, '&');
        
        // C keywords - improved to avoid replacing inside existing spans
        const keywords = ['int', 'char', 'void', 'if', 'else', 'while', 'for', 'return', 'static', 'const', 'struct', 'typedef', 'enum', 'case', 'switch', 'break', 'continue', 'default'];
        keywords.forEach(keyword => {
            // Split content by existing spans to avoid processing inside them
            const parts = content.split(/(<span[^>]*>.*?<\/span>)/);
            content = parts.map(part => {
                // Only process parts that are not spans
                if (part.startsWith('<span')) {
                    return part;
                }
                const regex = new RegExp(`\\b(${keyword})\\b`, 'g');
                return part.replace(regex, '<span class="code-keyword">$1</span>');
            }).join('');
        });

        // String literals - improved to avoid replacing inside existing spans
        const stringParts = content.split(/(<span[^>]*>.*?<\/span>)/);
        content = stringParts.map(part => {
            if (part.startsWith('<span')) {
                return part;
            }
            return part.replace(/"([^"]*?)"/g, '<span class="code-string">"$1"</span>');
        }).join('');
        
        // Comments - improved to avoid replacing inside existing spans
        const commentParts = content.split(/(<span[^>]*>.*?<\/span>)/);
        content = commentParts.map(part => {
            if (part.startsWith('<span')) {
                return part;
            }
            return part
                .replace(/\/\*.*?\*\//g, '<span class="code-comment">$&</span>')
                .replace(/\/\/.*$/gm, '<span class="code-comment">$&</span>');
        }).join('');
        
        // Function calls - improved to avoid replacing inside existing spans
        const functionParts = content.split(/(<span[^>]*>.*?<\/span>)/);
        content = functionParts.map(part => {
            if (part.startsWith('<span')) {
                return part;
            }
            return part.replace(/\b([a-zA-Z_][a-zA-Z0-9_]*)\s*\(/g, '<span class="code-function">$1</span>(');
        }).join('');

        element.innerHTML = content;
    }
}

// Enhanced Mermaid configuration
function setupMermaid() {
    if (typeof mermaid !== 'undefined') {
        mermaid.initialize({
            theme: document.body.getAttribute('data-theme') === 'dark' ? 'dark' : 'default',
            themeVariables: {
                primaryColor: '#3b82f6',
                primaryTextColor: '#1f2937',
                primaryBorderColor: '#2563eb',
                lineColor: '#6b7280',
                tertiaryColor: '#f3f4f6'
            }
        });
    }
}

// Initialize everything when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
    new ThemeManager();
    new TOCGenerator();
    new SearchManager();
    new CodeHighlighter();
    setupMermaid();

    // Re-initialize Mermaid when theme changes
    const themeToggle = document.querySelector('.theme-toggle');
    if (themeToggle) {
        themeToggle.addEventListener('click', () => {
            setTimeout(setupMermaid, 100);
        });
    }
});

// Export for potential use in other scripts
window.MinishellDocs = {
    ThemeManager,
    TOCGenerator,
    SearchManager,
    CodeHighlighter,
    
    // Utility function to clean up encoding issues
    cleanupHTML: function() {
        console.log('Starting complete HTML cleanup...');
        
        // Remove all existing syntax highlighting
        document.querySelectorAll('code, pre').forEach(element => {
            // Remove highlighted class
            element.classList.remove('highlighted');
            
            // Strip all syntax highlighting spans
            let content = element.innerHTML;
            content = content.replace(/<span class="code-[^"]*">([^<]*)<\/span>/g, '$1');
            element.innerHTML = content;
        });
        
        // Clean up any remaining encoding issues
        const codeHighlighter = new CodeHighlighter();
        codeHighlighter.cleanupDoubleEncoding();
        
        // Re-highlight everything cleanly
        codeHighlighter.highlightCodeBlocks();
        
        console.log('HTML cleanup complete');
    },
    
    // Debug function to detect encoding issues
    debugEncodingIssues: function() {
        const issues = [];
        
        // Check for double-encoded spans
        document.querySelectorAll('*').forEach((element, index) => {
            const html = element.innerHTML;
            if (html.includes('<span class="<span')) {
                issues.push({
                    element: element,
                    index: index,
                    tagName: element.tagName,
                    className: element.className,
                    issue: 'Double-encoded span detected',
                    content: html.substring(0, 100) + '...'
                });
            }
            if (html.includes('code-keyword"> case of  <span class="<span')) {
                issues.push({
                    element: element,
                    index: index,
                    tagName: element.tagName,
                    className: element.className,
                    issue: 'Specific case encoding issue detected',
                    content: html.substring(0, 100) + '...'
                });
            }
        });
        
        if (issues.length > 0) {
            console.error('🚨 Encoding issues detected:', issues);
            return issues;
        } else {
            console.log('✅ No encoding issues found');
            return [];
        }
    }
};
