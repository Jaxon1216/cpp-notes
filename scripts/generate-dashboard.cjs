const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

const ROOT = path.resolve(__dirname, '..');
const IGNORE = ['.vitepress', 'node_modules', '.git', 'scripts', 'README.md', 'index.md', 'package.json', 'package-lock.json', '.DS_Store', '.gitignore'];

// Directory name mapping (English -> Chinese)
const DIR_MAPPING = {
  'HDU': '数据结构',
  'Leetcode': 'Leetcode',
  'PTA': 'PTA',
  'STL': 'STL',
  'JavaScript': 'JavaScript',
  'CSS': 'CSS',
  'articles': '文章',
  'Miscellaneous': '杂项',
  'PurpleBook': '紫书',
  'TipsAndTricks': '技巧',
  'BinarySearch': '二分查找',
  'SlidingWindow': '滑动窗口',
  'DataStructure': '数据结构',
  'Intro': '入门题单',
  'String': '串',
  'SinglyLinkedList': '单向链表',
  'Stack': '栈',
  'StackAndQueue': '栈和队列',
  'Queue': '队列',
  'SequentialList': '顺序表'
};

function getDisplayName(name) {
  return DIR_MAPPING[name] || name;
}

// Get file's last git commit time
function getGitTime(filePath) {
  try {
    const result = execSync(
      `git log -1 --format="%at" -- "${filePath}"`,
      { cwd: ROOT, encoding: 'utf-8', stdio: ['pipe', 'pipe', 'pipe'] }
    ).trim();
    if (result) {
      return new Date(parseInt(result) * 1000);
    }
  } catch (e) {
    // File not in git or git error, fallback to mtime
  }
  try {
    return fs.statSync(filePath).mtime;
  } catch (e) {
    return new Date();
  }
}

// Get all markdown files in a directory recursively
function getAllMdFiles(dirPath, arrayOfFiles = []) {
  if (!fs.existsSync(dirPath)) return arrayOfFiles;
  
  const files = fs.readdirSync(dirPath);

  files.forEach(file => {
    if (IGNORE.includes(file) || file.startsWith('.')) return;
    const fullPath = path.join(dirPath, file);
    if (!fs.existsSync(fullPath)) return;
    
    const stat = fs.statSync(fullPath);
    if (stat.isDirectory()) {
      getAllMdFiles(fullPath, arrayOfFiles);
    } else if (file.endsWith('.md')) {
      arrayOfFiles.push({
        path: fullPath,
        gitTime: getGitTime(fullPath)
      });
    }
  });

  return arrayOfFiles;
}

// Build directory tree structure
function buildDirTree(dirPath, basePath = '') {
  if (!fs.existsSync(dirPath)) return [];
  
  const items = fs.readdirSync(dirPath);
  const result = [];

  // Sort: directories first, then files
  items.sort((a, b) => {
    const aPath = path.join(dirPath, a);
    const bPath = path.join(dirPath, b);
    const aIsDir = fs.existsSync(aPath) && fs.statSync(aPath).isDirectory();
    const bIsDir = fs.existsSync(bPath) && fs.statSync(bPath).isDirectory();
    if (aIsDir && !bIsDir) return -1;
    if (!aIsDir && bIsDir) return 1;
    return a.localeCompare(b);
  });

  items.forEach(item => {
    if (IGNORE.includes(item) || item.startsWith('.') || item.endsWith('.cpp') || item.endsWith('.exe')) return;
    
    const fullPath = path.join(dirPath, item);
    if (!fs.existsSync(fullPath)) return;
    
    const stat = fs.statSync(fullPath);
    const relativePath = basePath ? `${basePath}/${item}` : item;

    if (stat.isDirectory()) {
      const children = buildDirTree(fullPath, relativePath);
      if (children.length > 0) {
        result.push({
          type: 'dir',
          name: item,
          displayName: getDisplayName(item),
          path: relativePath,
          children: children
        });
      }
    } else if (item.endsWith('.md')) {
      const name = item.replace('.md', '');
      const displayName = name === 'note' ? '笔记' : name;
      const gitTime = getGitTime(fullPath);
      
      result.push({
        type: 'file',
        name: name,
        displayName: displayName,
        path: relativePath.replace('.md', ''),
        gitTime: gitTime
      });
    }
  });

  return result;
}

// Get root level categories
function getRootCategories() {
  const items = fs.readdirSync(ROOT);
  const categories = [];

  items.forEach(item => {
    if (IGNORE.includes(item) || item.startsWith('.')) return;
    const fullPath = path.join(ROOT, item);
    if (!fs.existsSync(fullPath)) return;
    
    const stat = fs.statSync(fullPath);
    if (stat.isDirectory()) {
      const tree = buildDirTree(fullPath, item);
      if (tree.length > 0) {
        // Get latest git time from all files in this category
        const allFiles = getAllMdFiles(fullPath);
        let latestTime = null;
        allFiles.forEach(f => {
          if (!latestTime || f.gitTime > latestTime) {
            latestTime = f.gitTime;
          }
        });

        categories.push({
          name: item,
          displayName: getDisplayName(item),
          tree: tree,
          fileCount: allFiles.length,
          latestTime: latestTime
        });
      }
    }
  });

  // Sort categories by latest update time
  categories.sort((a, b) => {
    if (!a.latestTime) return 1;
    if (!b.latestTime) return -1;
    return b.latestTime - a.latestTime;
  });

  return categories;
}

// Format date as MM/DD
function formatDate(date) {
  if (!date) return '';
  const month = String(date.getMonth() + 1).padStart(2, '0');
  const day = String(date.getDate()).padStart(2, '0');
  return `${month}/${day}`;
}

// Generate tree HTML for a category
function generateTreeHtml(items, depth = 0) {
  let html = '';
  
  items.forEach((item, index) => {
    const isLast = index === items.length - 1;
    const prefix = depth === 0 ? '' : (isLast ? '└── ' : '├── ');
    
    if (item.type === 'dir') {
      html += `      <div class="tree-item tree-dir depth-${depth}">
        <span class="tree-prefix">${prefix}</span>
        <span class="tree-name">${item.displayName}/</span>
      </div>\n`;
      html += generateTreeHtml(item.children, depth + 1);
    } else {
      const dateStr = formatDate(item.gitTime);
      html += `      <a class="tree-item tree-file depth-${depth}" href="/${item.path}">
        <span class="tree-prefix">${prefix}</span>
        <span class="tree-name">${item.displayName}</span>
        <span class="tree-date">${dateStr}</span>
      </a>\n`;
    }
  });

  return html;
}

function generateDashboard() {
  const categories = getRootCategories();
  
  // Find most recently updated file for "继续学习" button
  let mostRecentFile = null;
  let mostRecentTime = null;
  categories.forEach(cat => {
    const allFiles = getAllMdFiles(path.join(ROOT, cat.name));
    allFiles.forEach(f => {
      if (!mostRecentTime || f.gitTime > mostRecentTime) {
        mostRecentTime = f.gitTime;
        mostRecentFile = f.path;
      }
    });
  });

  const continueLink = mostRecentFile 
    ? '/' + path.relative(ROOT, mostRecentFile).replace(/\\/g, '/').replace('.md', '')
    : '/';

  let content = `---
layout: doc
---

<style>
:root {
  --vp-home-hero-name-color: transparent;
  --vp-home-hero-name-background: -webkit-linear-gradient(120deg, #bd34fe 30%, #41d1ff);
}

.VPHero {
  padding-top: calc(var(--vp-nav-height) + 20px) !important;
  padding-bottom: 20px !important;
}

.VPHomeHero .name {
  font-size: 36px !important;
  line-height: 44px !important;
}

.VPHomeHero .tagline {
  font-size: 16px !important;
  color: var(--vp-c-text-2);
}

.directory-container {
  max-width: 900px;
  margin: 0 auto;
  padding: 20px 24px 60px;
}

.category-section {
  margin-bottom: 32px;
}

.category-header {
  display: flex;
  align-items: center;
  gap: 8px;
  font-size: 18px;
  font-weight: 600;
  color: var(--vp-c-text-1);
  padding-bottom: 8px;
  border-bottom: 1px solid var(--vp-c-divider);
  margin-bottom: 12px;
}

.category-meta {
  font-size: 13px;
  font-weight: 400;
  color: var(--vp-c-text-3);
  margin-left: auto;
}

.tree-container {
  font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, monospace;
  font-size: 14px;
  line-height: 1.8;
}

.tree-item {
  display: flex;
  align-items: center;
  padding: 2px 0;
  color: var(--vp-c-text-2);
}

.tree-file {
  text-decoration: none !important;
  border-radius: 4px;
  padding: 2px 6px;
  margin: -2px -6px;
  transition: background-color 0.2s;
}

.tree-file:hover {
  background-color: var(--vp-c-bg-soft);
  color: var(--vp-c-brand);
}

.tree-prefix {
  color: var(--vp-c-text-3);
  white-space: pre;
}

.tree-name {
  flex: 1;
}

.tree-dir .tree-name {
  color: var(--vp-c-text-1);
  font-weight: 500;
}

.tree-date {
  color: var(--vp-c-text-3);
  font-size: 12px;
  margin-left: 16px;
}

.depth-0 { padding-left: 0; }
.depth-1 { padding-left: 20px; }
.depth-2 { padding-left: 40px; }
.depth-3 { padding-left: 60px; }
.depth-4 { padding-left: 80px; }
</style>

<div class="directory-container">
`;

  categories.forEach(cat => {
    content += `  <div class="category-section">
    <div class="category-header">
      <span>📂 ${cat.displayName}</span>
      <span class="category-meta">${cat.fileCount} 篇</span>
    </div>
    <div class="tree-container">
${generateTreeHtml(cat.tree)}    </div>
  </div>
`;
  });

  content += `</div>
`;

  fs.writeFileSync(path.join(ROOT, 'index.md'), content);
  console.log('Dashboard generated at index.md');
}

generateDashboard();
