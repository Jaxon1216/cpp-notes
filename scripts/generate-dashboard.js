const fs = require('fs');
const path = require('path');

const ROOT = path.resolve(__dirname, '..');
const IGNORE = ['.vitepress', 'node_modules', '.git', 'scripts', 'README.md', 'index.md', 'package.json', 'package-lock.json', '.DS_Store'];

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

function generateDashboard() {
  const allMds = getAllFiles(ROOT);
  
  // Sort by mtime desc
  allMds.sort((a, b) => b.mtime - a.mtime);

  const recent = allMds.slice(0, 20); // Top 20

  let content = `---
layout: home

hero:
  name: "CPP 学习笔记"
  text: "温故而知新"
  tagline: "持续积累，厚积薄发"
  actions:
    - theme: brand
      text: "继续上次学习"
      link: "${recent.length > 0 ? '/' + path.relative(ROOT, recent[0].path) : '/'}"
    - theme: alt
      text: "浏览目录"
      link: "/Leetcode/"

features:
  - title: 自动同步
    details: 内容基于本地 Markdown 文件自动生成，无需额外维护。
  - title: 复习助手
    details: 首页展示最近修改的笔记，方便快速回溯思路。
  - title: 知识体系
    details: 按照目录结构生成侧边栏，构建完整的知识图谱。
---

<div style="margin-top: 40px; max-width: 900px; margin-left: auto; margin-right: auto; padding: 0 20px;">

## 📅 最近更新笔记

| 📝 笔记 | 📂 分类 | 🕒 修改时间 |
|---------|---------|-------------|
`;

  recent.forEach(item => {
    const dateStr = item.mtime.toLocaleString('zh-CN', { hour12: false });
    let relPath = path.relative(ROOT, item.path).replace(/\\/g, '/');
    const filename = path.basename(relPath, '.md');
    const title = filename === 'note' ? '笔记' : filename;
    const folder = path.dirname(relPath);
    
    // Fix spacing for table
    content += `| [${title}](/${relPath}) | \`${folder}\` | ${dateStr} |\n`;
  });

  content += `\n</div>\n`;

  fs.writeFileSync(path.join(ROOT, 'index.md'), content);
  console.log('Dashboard generated at index.md');
}

generateDashboard();

