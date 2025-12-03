const fs = require('fs');
const path = require('path');

const ROOT = path.resolve(__dirname, '..');
const IGNORE = ['.vitepress', 'node_modules', '.git', 'scripts', 'README.md', 'index.md', 'package.json', 'package-lock.json', '.DS_Store'];

// Directory name mapping (English -> Chinese)
const DIR_MAPPING = {
  'DataStructure': '数据结构',
  'Leetcode': 'Leetcode',
  'PTA': 'PTA',
  'STL': 'STL',
  'BinarySearch': '二分查找',
  'SlidingWindow': '滑动窗口',
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

function getAllFiles(dirPath, arrayOfFiles) {
  const files = fs.readdirSync(dirPath);

  arrayOfFiles = arrayOfFiles || [];

  files.forEach(function(file) {
    if (IGNORE.includes(file) || file.startsWith('.')) return;
    const fullPath = path.join(dirPath, file);
    // check if file exists (symlinks might break)
    if (!fs.existsSync(fullPath)) return;
    
    const stat = fs.statSync(fullPath);
    if (stat.isDirectory()) {
      arrayOfFiles = getAllFiles(fullPath, arrayOfFiles);
    } else {
      if (file.endsWith('.md')) {
        arrayOfFiles.push({
          path: fullPath,
          mtime: stat.mtime
        });
      }
    }
  });

  return arrayOfFiles;
}

// Helper to find the first MD file in a directory for linking
function findFirstMd(dirName) {
    const all = getAllFiles(path.join(ROOT, dirName));
    if (all.length > 0) {
        return '/' + path.relative(ROOT, all[0].path).replace(/\\/g, '/');
    }
    return '/';
}

function generateDashboard() {
  const allMds = getAllFiles(ROOT);
  
  // Sort by mtime desc
  allMds.sort((a, b) => b.mtime - a.mtime);

  const recent = allMds.slice(0, 20); // Top 20

  // Dynamic browse link
  const browseLink = findFirstMd('Leetcode') !== '/' ? findFirstMd('Leetcode') : '/';

  let content = `---
layout: home

hero:
  name: "CPP Note"
  text: ""
  tagline: ""
  actions:
    - theme: brand
      text: "继续上次学习"
      link: "${recent.length > 0 ? '/' + path.relative(ROOT, recent[0].path).replace(/\\/g, '/') : '/'}"
    - theme: alt
      text: "浏览目录"
      link: "${browseLink}"
---

<style>
:root {
  --vp-home-hero-name-color: transparent;
  --vp-home-hero-name-background: -webkit-linear-gradient(120deg, #bd34fe 30%, #41d1ff);
}

/* Custom override to make hero smaller */
@media (min-width: 640px) {
  .VPHero {
    padding-top: calc(var(--vp-nav-height) + 32px) !important;
    padding-bottom: 12px !important;
  }
}
.VPHero {
  padding-top: calc(var(--vp-nav-height) + 20px) !important;
  padding-bottom: 12px !important;
}

.VPHomeHero .container {
  padding-top: 0 !important;
  padding-bottom: 0 !important;
}

.VPHomeHero .name {
  font-size: 32px !important;
  line-height: 40px !important;
}
.VPHomeHero .text {
  display: none !important;
}
.VPHomeHero .tagline {
  display: none !important;
}

/* Adjust action buttons margin */
.VPHomeHero .actions {
  margin-top: 10px !important;
}

.recent-notes-container {
  margin-top: 20px;
  max-width: 1152px;
  margin-left: auto;
  margin-right: auto;
  padding: 0 24px;
}
.recent-title {
  font-size: 24px;
  font-weight: 600;
  margin-bottom: 16px;
  border-bottom: 1px solid var(--vp-c-divider);
  padding-bottom: 10px;
}
.recent-list {
  display: flex;
  flex-direction: column;
  gap: 10px;
}
.recent-item {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 12px 20px;
  background-color: var(--vp-c-bg-soft);
  border: 1px solid var(--vp-c-bg-soft);
  border-radius: 8px;
  text-decoration: none !important;
  transition: all 0.3s ease;
  color: var(--vp-c-text-1) !important;
}
.recent-item:hover {
  border-color: var(--vp-c-brand);
  background-color: var(--vp-c-bg-mute);
  transform: translateX(5px);
}
.note-title {
  font-size: 16px;
  font-weight: 500;
  flex: 1;
}
.note-meta {
  display: flex;
  gap: 20px;
  font-size: 14px;
  color: var(--vp-c-text-2);
}
@media (max-width: 640px) {
  .recent-item {
    flex-direction: column;
    align-items: flex-start;
    gap: 8px;
  }
  .note-meta {
    width: 100%;
    justify-content: space-between;
    font-size: 13px;
  }
}
</style>

<div class="recent-notes-container">
  <h2 class="recent-title">📅 最近更新笔记</h2>
  <div class="recent-list">
`;

  recent.forEach(item => {
    const dateStr = item.mtime.toLocaleString('zh-CN', { month: '2-digit', day: '2-digit', hour: '2-digit', minute: '2-digit' });
    let relPath = path.relative(ROOT, item.path).replace(/\\/g, '/');
    // Remove .md extension for correct VitePress routing
    relPath = relPath.replace(/\.md$/, '');
    
    const filename = path.basename(relPath);
    const title = filename === 'note' ? '笔记' : filename;
    
    // Category: use the immediate parent folder name
    const parentDir = path.dirname(relPath);
    const categoryName = path.basename(parentDir); // Get just the last folder name
    const categoryDisplay = getDisplayName(categoryName); // Translate to Chinese
    
    content += `    <a class="recent-item" href="/${relPath}">
      <span class="note-title">${title}</span>
      <span class="note-meta">
        <span class="note-category">📂 ${categoryDisplay}</span>
        <span class="note-time">🕒 ${dateStr}</span>
      </span>
    </a>
`;
  });

  content += `  </div>
</div>
`;

  fs.writeFileSync(path.join(ROOT, 'index.md'), content);
  console.log('Dashboard generated at index.md');
}

generateDashboard();
