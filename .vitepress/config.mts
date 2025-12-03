import { defineConfig } from 'vitepress'
import fs from 'fs'
import path from 'path'

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
}

function getDisplayName(name) {
  return DIR_MAPPING[name] || name
}

// Helper to find first MD file for nav links
function findFirstFile(dir) {
  try {
    const items = fs.readdirSync(dir)
    for (const item of items) {
      const fullPath = path.join(dir, item)
      const stat = fs.statSync(fullPath)
      if (stat.isDirectory()) {
        const found = findFirstFile(fullPath)
        if (found) return found
      } else if (item.endsWith('.md')) {
        return path.join(dir, item)
      }
    }
  } catch (e) {
    return null
  }
  return null
}

function getLinkForDir(dirName) {
  const root = process.cwd()
  const fullPath = path.join(root, dirName)
  if (fs.existsSync(fullPath)) {
    const file = findFirstFile(fullPath)
    if (file) {
      return '/' + path.relative(root, file)
    }
  }
  return '/'
}

// Helper to get direct children directories for dropdown
function getDirDropdownItems(dirName) {
  const root = process.cwd()
  const fullPath = path.join(root, dirName)
  if (!fs.existsSync(fullPath)) return []
  
  const items = fs.readdirSync(fullPath)
  const dropdown = []
  
  items.forEach(item => {
    if (item.startsWith('.') || item === 'draft.cpp' || item.endsWith('.cpp')) return
    const itemPath = path.join(fullPath, item)
    const stat = fs.statSync(itemPath)
    
    if (stat.isDirectory()) {
      const link = getLinkForDir(path.join(dirName, item))
      if (link !== '/') {
        dropdown.push({ text: getDisplayName(item), link: link })
      }
    }
  })
  
  return dropdown
}


function getSidebarItems(dir, base) {
  const items = fs.readdirSync(dir)
  const result = []

  // Sort items: directories first, then files
  items.sort((a, b) => {
    const aPath = path.join(dir, a)
    const bPath = path.join(dir, b)
    const aIsDir = fs.statSync(aPath).isDirectory()
    const bIsDir = fs.statSync(bPath).isDirectory()
    if (aIsDir && !bIsDir) return -1
    if (!aIsDir && bIsDir) return 1
    return a.localeCompare(b)
  })

  items.forEach(item => {
    if (item.startsWith('.') || item === 'node_modules' || item === 'draft.cpp' || item.endsWith('.cpp') || item.endsWith('.exe')) return
    
    const fullPath = path.join(dir, item)
    const stat = fs.statSync(fullPath)

    if (stat.isDirectory()) {
      const children = getSidebarItems(fullPath, `${base}${item}/`)
      // Only add directory if it has children
      if (children.length > 0) {
        result.push({
          text: getDisplayName(item),
          collapsed: true,
          items: children
        })
      }
    } else if (item.endsWith('.md')) {
      let text = item.replace('.md', '')
      if (text === 'note') text = '笔记'
      if (text === 'README') text = '简介'
      
      result.push({
        text: text,
        link: `${base}${item}`
      })
    }
  })
  return result
}

function generateSidebar() {
  const root = process.cwd()
  const ignore = ['.vitepress', 'node_modules', '.git', 'scripts', 'package.json', 'package-lock.json', 'README.md', 'index.md', '.gitignore', '.DS_Store']
  
  const sidebar = {}
  
  // Default sidebar for root
  sidebar['/'] = []

  const items = fs.readdirSync(root)
  
  items.forEach(item => {
    if (ignore.includes(item)) return
    const fullPath = path.join(root, item)
    const stat = fs.statSync(fullPath)
    
    if (stat.isDirectory()) {
      sidebar[`/${item}/`] = getSidebarItems(fullPath, `/${item}/`)
    }
  })
  
  return sidebar
}

export default defineConfig({
  title: "CPP 学习笔记",
  description: "Personal Algorithm & CPP Notes",
  ignoreDeadLinks: true, // Avoid build errors for missing links
  themeConfig: {
    nav: [
      { text: '首页', link: '/' },
      { 
        text: 'Leetcode', 
        items: [
          { text: '概览', link: getLinkForDir('Leetcode') },
          ...getDirDropdownItems('Leetcode')
        ]
      },
      { 
        text: '数据结构', 
        items: [
           { text: '概览', link: getLinkForDir('DataStructure') },
           ...getDirDropdownItems('DataStructure')
        ]
      },
      { text: 'PTA', link: getLinkForDir('PTA') },
      { text: 'STL', link: getLinkForDir('STL') },
    ],
    sidebar: generateSidebar(),
    socialLinks: [
      { icon: 'github', link: 'https://github.com/Jaxon1216/cpp-notes' }
    ],
    outline: {
      level: [2, 3],
      label: '页面导航'
    },
    lastUpdated: {
      text: '最后更新于',
      formatOptions: {
        dateStyle: 'full',
        timeStyle: 'medium'
      }
    }
  }
})
