---
layout: home

hero:
  name: "CPP Note"
  text: ""
  tagline: ""
  actions:
    - theme: brand
      text: "继续上次学习"
      link: "/HDU/SequentialList/note.md"
    - theme: alt
      text: "浏览目录"
      link: "/Leetcode/BinarySearch/BinarySearch.md"
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
    <a class="recent-item" href="/HDU/SequentialList/note">
      <span class="note-title">笔记</span>
      <span class="note-meta">
        <span class="note-category">📂 顺序表</span>
        <span class="note-time">🕒 12/03 22:23</span>
      </span>
    </a>
    <a class="recent-item" href="/HDU/Queue/queue">
      <span class="note-title">queue</span>
      <span class="note-meta">
        <span class="note-category">📂 队列</span>
        <span class="note-time">🕒 12/03 22:17</span>
      </span>
    </a>
    <a class="recent-item" href="/HDU/String/note">
      <span class="note-title">笔记</span>
      <span class="note-meta">
        <span class="note-category">📂 串</span>
        <span class="note-time">🕒 12/03 22:17</span>
      </span>
    </a>
    <a class="recent-item" href="/HDU/Stack/note">
      <span class="note-title">笔记</span>
      <span class="note-meta">
        <span class="note-category">📂 栈</span>
        <span class="note-time">🕒 12/03 22:17</span>
      </span>
    </a>
    <a class="recent-item" href="/HDU/SinglyLinkedList/note">
      <span class="note-title">笔记</span>
      <span class="note-meta">
        <span class="note-category">📂 单向链表</span>
        <span class="note-time">🕒 12/03 22:17</span>
      </span>
    </a>
    <a class="recent-item" href="/Leetcode/Intro/note">
      <span class="note-title">笔记</span>
      <span class="note-meta">
        <span class="note-category">📂 入门题单</span>
        <span class="note-time">🕒 12/03 22:17</span>
      </span>
    </a>
    <a class="recent-item" href="/Leetcode/SlidingWindow/定长">
      <span class="note-title">定长</span>
      <span class="note-meta">
        <span class="note-category">📂 滑动窗口</span>
        <span class="note-time">🕒 12/03 22:17</span>
      </span>
    </a>
    <a class="recent-item" href="/Leetcode/SlidingWindow/不定长">
      <span class="note-title">不定长</span>
      <span class="note-meta">
        <span class="note-category">📂 滑动窗口</span>
        <span class="note-time">🕒 12/03 22:03</span>
      </span>
    </a>
    <a class="recent-item" href="/Leetcode/BinarySearch/BinarySearch">
      <span class="note-title">BinarySearch</span>
      <span class="note-meta">
        <span class="note-category">📂 二分查找</span>
        <span class="note-time">🕒 12/03 15:03</span>
      </span>
    </a>
    <a class="recent-item" href="/PTA/onlinetest">
      <span class="note-title">onlinetest</span>
      <span class="note-meta">
        <span class="note-category">📂 PTA</span>
        <span class="note-time">🕒 12/02 22:05</span>
      </span>
    </a>
    <a class="recent-item" href="/STL/STL">
      <span class="note-title">STL</span>
      <span class="note-meta">
        <span class="note-category">📂 STL</span>
        <span class="note-time">🕒 11/17 21:01</span>
      </span>
    </a>
    <a class="recent-item" href="/articles/basicK">
      <span class="note-title">basicK</span>
      <span class="note-meta">
        <span class="note-category">📂 articles</span>
        <span class="note-time">🕒 11/04 19:43</span>
      </span>
    </a>
    <a class="recent-item" href="/articles/algorithm">
      <span class="note-title">algorithm</span>
      <span class="note-meta">
        <span class="note-category">📂 articles</span>
        <span class="note-time">🕒 10/31 01:11</span>
      </span>
    </a>
    <a class="recent-item" href="/HDU/confusion">
      <span class="note-title">confusion</span>
      <span class="note-meta">
        <span class="note-category">📂 HDU</span>
        <span class="note-time">🕒 10/05 22:18</span>
      </span>
    </a>
    <a class="recent-item" href="/如何调试">
      <span class="note-title">如何调试</span>
      <span class="note-meta">
        <span class="note-category">📂 .</span>
        <span class="note-time">🕒 09/18 16:09</span>
      </span>
    </a>
    <a class="recent-item" href="/HDU/SinglyLinkedList/问题汇总">
      <span class="note-title">问题汇总</span>
      <span class="note-meta">
        <span class="note-category">📂 单向链表</span>
        <span class="note-time">🕒 09/11 14:19</span>
      </span>
    </a>
  </div>
</div>
