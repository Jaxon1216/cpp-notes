---
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
  <div class="category-section">
    <div class="category-header">
      <span>📂 前端</span>
      <span class="category-meta">6 篇</span>
    </div>
    <div class="tree-container">
      <div class="tree-item tree-dir depth-0">
        <span class="tree-prefix"></span>
        <span class="tree-name">CSS/</span>
      </div>
      <a class="tree-item tree-file depth-1" href="/Frontend/CSS/display">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">display</span>
        <span class="tree-date">12/22</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Frontend/CSS/Pseudo-elements">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">Pseudo-elements</span>
        <span class="tree-date">12/13</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Frontend/CSS/selectors">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">selectors</span>
        <span class="tree-date">12/13</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Frontend/CSS/url">
        <span class="tree-prefix">└── </span>
        <span class="tree-name">url</span>
        <span class="tree-date">12/14</span>
      </a>
      <div class="tree-item tree-dir depth-0">
        <span class="tree-prefix"></span>
        <span class="tree-name">JavaScript/</span>
      </div>
      <a class="tree-item tree-file depth-1" href="/Frontend/JavaScript/ECMAScript">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">ECMAScript</span>
        <span class="tree-date">12/12</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Frontend/JavaScript/webAPIs">
        <span class="tree-prefix">└── </span>
        <span class="tree-name">webAPIs</span>
        <span class="tree-date">12/25</span>
      </a>
    </div>
  </div>
  <div class="category-section">
    <div class="category-header">
      <span>📂 Leetcode</span>
      <span class="category-meta">11 篇</span>
    </div>
    <div class="tree-container">
      <div class="tree-item tree-dir depth-0">
        <span class="tree-prefix"></span>
        <span class="tree-name">二分查找/</span>
      </div>
      <a class="tree-item tree-file depth-1" href="/Leetcode/BinarySearch/BinarySearch">
        <span class="tree-prefix">└── </span>
        <span class="tree-name">BinarySearch</span>
        <span class="tree-date">12/08</span>
      </a>
      <div class="tree-item tree-dir depth-0">
        <span class="tree-prefix"></span>
        <span class="tree-name">数据结构/</span>
      </div>
      <a class="tree-item tree-file depth-1" href="/Leetcode/DataStructure/Difference">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">Difference</span>
        <span class="tree-date">12/03</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Leetcode/DataStructure/Enumeration">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">Enumeration</span>
        <span class="tree-date">12/22</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Leetcode/DataStructure/Heap">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">Heap</span>
        <span class="tree-date">12/03</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Leetcode/DataStructure/Prefixsum">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">Prefixsum</span>
        <span class="tree-date">12/03</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Leetcode/DataStructure/Queue">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">Queue</span>
        <span class="tree-date">12/03</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Leetcode/DataStructure/Stack">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">Stack</span>
        <span class="tree-date">12/03</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Leetcode/DataStructure/Trie">
        <span class="tree-prefix">└── </span>
        <span class="tree-name">Trie</span>
        <span class="tree-date">12/03</span>
      </a>
      <div class="tree-item tree-dir depth-0">
        <span class="tree-prefix"></span>
        <span class="tree-name">入门题单/</span>
      </div>
      <a class="tree-item tree-file depth-1" href="/Leetcode/Intro/note">
        <span class="tree-prefix">└── </span>
        <span class="tree-name">笔记</span>
        <span class="tree-date">12/03</span>
      </a>
      <div class="tree-item tree-dir depth-0">
        <span class="tree-prefix"></span>
        <span class="tree-name">滑动窗口/</span>
      </div>
      <a class="tree-item tree-file depth-1" href="/Leetcode/SlidingWindow/不定长">
        <span class="tree-prefix">├── </span>
        <span class="tree-name">不定长</span>
        <span class="tree-date">12/03</span>
      </a>
      <a class="tree-item tree-file depth-1" href="/Leetcode/SlidingWindow/定长">
        <span class="tree-prefix">└── </span>
        <span class="tree-name">定长</span>
        <span class="tree-date">12/03</span>
      </a>
    </div>
  </div>
  <div class="category-section">
    <div class="category-header">
      <span>📂 STL</span>
      <span class="category-meta">1 篇</span>
    </div>
    <div class="tree-container">
      <a class="tree-item tree-file depth-0" href="/STL/STL">
        <span class="tree-prefix"></span>
        <span class="tree-name">STL</span>
        <span class="tree-date">12/13</span>
      </a>
    </div>
  </div>
  <div class="category-section">
    <div class="category-header">
      <span>📂 其他</span>
      <span class="category-meta">3 篇</span>
    </div>
    <div class="tree-container">
      <div class="tree-item tree-dir depth-0">
        <span class="tree-prefix"></span>
        <span class="tree-name">books/</span>
      </div>
      <a class="tree-item tree-file depth-1" href="/Misc/books/PurpleBook">
        <span class="tree-prefix">└── </span>
        <span class="tree-name">PurpleBook</span>
        <span class="tree-date">12/05</span>
      </a>
      <div class="tree-item tree-dir depth-0">
        <span class="tree-prefix"></span>
        <span class="tree-name">interview/</span>
      </div>
      <a class="tree-item tree-file depth-1" href="/Misc/interview/MockInterviews">
        <span class="tree-prefix">└── </span>
        <span class="tree-name">MockInterviews</span>
        <span class="tree-date">12/05</span>
      </a>
      <div class="tree-item tree-dir depth-0">
        <span class="tree-prefix"></span>
        <span class="tree-name">tricks/</span>
      </div>
      <a class="tree-item tree-file depth-1" href="/Misc/tricks/tips">
        <span class="tree-prefix">└── </span>
        <span class="tree-name">tips</span>
        <span class="tree-date">12/05</span>
      </a>
    </div>
  </div>
  <div class="category-section">
    <div class="category-header">
      <span>📂 文章</span>
      <span class="category-meta">2 篇</span>
    </div>
    <div class="tree-container">
      <a class="tree-item tree-file depth-0" href="/articles/algorithm">
        <span class="tree-prefix"></span>
        <span class="tree-name">algorithm</span>
        <span class="tree-date">11/06</span>
      </a>
      <a class="tree-item tree-file depth-0" href="/articles/basicK">
        <span class="tree-prefix"></span>
        <span class="tree-name">basicK</span>
        <span class="tree-date">11/06</span>
      </a>
    </div>
  </div>
</div>
