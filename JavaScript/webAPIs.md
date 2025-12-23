## day1DOM元素获取与操作
- DOM对象，DOM树
- 获取`querySelectorALL`,`queryselector`
- 属性`innerText`不解析标签,`innnerHTML`解析标签
- `style`属性,宽高背景色等
- 类名或者`classList`控制css，追加类名，`add,remove,toggle(classname)`
- 表单属性`value` ,`type`
- 自定义属性`data-id`,`对象.dataset.id`，获取的时候别忘记`#`号
- 间歇函数`setInterval`,m级别单位set对应clear
- 案例：轮播图定时版，注意li标签下标从1开始 

## day2DOM事件基础
- 事件监听`addEventListener`
- 事件类型:`click,mouseenter,mouseleave`,表单`focus,blur`,键盘`Keydown,keyup`,表单输入触发`input`
- 事件对象：回调函数的第一个参数，一般命名`event,ev,e`比如
```JavaScript
元素.addEventListener(`click`,fuction(e){

})
```
> 部分属性
> - type,clientX,clientY,offset/offsetY,key

- 环境对象this
- 回调函数
- tab栏目切换案例：
    - `href = javascript:;`
    - a标签专门用来存图片
    - `querySelectorALL`得到伪数组，有下标


## day3DOM进阶
1. 表单全选反选案例：
    - 如果点了大框框那用循环给所有小框打true or false，对于大框框绑定点击事件，函数：`cks[i].checked = checkedAll.checked//or this.checked`
    - css伪类选择器，`.ck:checked`，只选择了被勾选的复选框,所以小复选框的状态都被勾了，那就大框也true
    ```JavaScript
    for..
        cks[i].addEventListener('click',function(){
        checkAll.checked = document.querySelectorAll('.ck:checked').length === cks.length;
        //小框框选满了就给大框框打上true
        })
2. 事件冒泡
- 当一个元素的事件被触发时，同样的事件会被依次在祖先元素被触发
- 事件冒泡的必要性：

3. 事件委托
- 减少注册提升性能，给父元素
- 找到真正触发的元素`e.target`,其属性有个`tagName`
案例：
```JavaScript
<ul id="tabs">
  <li><a class="active" data-id="0" href="javascript:;">Tab 1</a></li>
  <li><a data-id="1" href="javascript:;">Tab 2</a></li>
  <li><a data-id="2" href="javascript:;">Tab 3</a></li>
</ul>

<div id="contents">
  <div class="item active">Content 1</div>
  <div class="item">Content 2</div>
  <div class="item">Content 3</div>
</div>

<script>
  const ul = document.querySelector('#tabs')
  const items = document.querySelectorAll('#contents .item')

  // 事件委托：事件绑定在 ul 上
  ul.addEventListener('click', function (e) {
    // 只处理 a 标签
    if (e.target.tagName !== 'A') return

    // tab 切换（排他）
    document.querySelector('#tabs .active').classList.remove('active')
    e.target.classList.add('active')

    // 内容切换
    const i = +e.target.dataset.id
    document.querySelector('#contents .active').classList.remove('active')
    items[i].classList.add('active')
  })
</script>
//这就是事件委托，一个监听器，处理所有 a
```
- 在事件委托中，e.target 可以是 this（或 e.currentTarget）内部的任意后代元素——包括子元素、孙子元素、曾孙元素。
- 采用事件委托，将 click 事件绑定在父元素 ul 上，利用事件冒泡机制在回调中通过 e.target 获取真实触发元素。通过判断 tagName 过滤事件源，并借助 data-id 建立 tab 与内容区的映射关系，使用排他思想完成 tab 切换。
4. 阻止冒泡 
- 需要阻止什么时间传递就给这个区域最大的盒子注册该事件`e.stopPropagation()`
5. 阻止元素默认行为
```JavaScript
dom.addEventListener('submit',function(e){
  e.preventDefault();
})
```
6. 页面加载
- `scrollWidth,scrollLeft,scrollTop,scrollHeight`,可读写，无单位
```JavaScript
document.documentElement.scrollTop = 800
window.addEventListener('scroll',function(){
  const n = document.documentElement.scrollTop//中间是返回html标签，body就直接是body
})
```
- 返回顶部两种方法，一是`document.documentElement.scrllTop = 0`, 二是`window.scrollTo(0,0)`

7. client 家族
- resize事件
- 获取可视宽高offsetWidth,offsetHeight
- offsetLeft/Top 是只读属性，受定位影响，看最近有定位的祖先元素


8. 电梯导航案例
- 初次点击没有可移除的`active`:获取A，判断再移除，没有就null
- 小盒子和大盒子有类似的自定义属性；
```JavaScript
const elevator = document.querySelector('.xtx-elevator-list')

elevator.addEventListener('click', e => {
  if (e.target.tagName === 'A') {
    // 切换 active
    document.querySelector('.xtx-elevator-list .active')?.classList.remove('active')
    e.target.classList.add('active')

    // 滚动到对应楼层
    const index = e.target.dataset.name
    const floorTop = document.querySelector(`.xtx_goods_${index}`).offsetTop
    document.documentElement.scrollTop = floorTop
  }
})

```
-  滚动条丝滑滚动
```css
html {
  scroll-behavior: smooth;
}
```
- 页面滚动，根据大盒子，改动小盒子的高亮
```JavaScript
window.addEventListener('scroll',function(){
  const old = document.querySelector('... .active')
  if(old) old.classList.remove('active')
  ...
  if .. scrollTop >= a.offsetTop && ..< b.offsetTop{
    ..selector('[data-name=new]').classList.add('active')//属性选择器
  }
  })
```
- 属性选择器
```html
...
input[type=text] {
  ...
}
<input type = "text" value = "123" ...>...
<input type = "password">
...
slector..('input[value]')
```



## day4DOM节点&移动端滑动

1. 日期对象
- 实例化`const date = new date()`;
  - 实例化之后可以用方法`get`+`Fullyear`/`Month`/`Date`/`Day`/`Hours`/`Minutes`/`Seconds`,边界从0开始；
  - 老外星期0就是星期天
  - 借助三目运算符，加上`+`号的隐式转换来自动补零`'0'`;
  - 定时器来自动刷新，隔一秒调用一次
  - tolocal系列函数
- 时间戳，直接隐式转换`+new date()`/实例化之后`dom.getTime()`/当前`dom.now()`
  - 倒计时涉及`setInterval`
  - 注意是ms级别，不要忘记`/1000`
  - 定时器前面调用一下获取时间的函数可以取消默认数值

2. 节点操作
- DOM节点
  - 元素节点：所有标签，主要操作这个，增删改查
  - 属性节点：链接，id，calss
  - 文本节点
- 查找节点，基于dom树呈现的关系
  - parentNode，跟链表里的`cur->next`差不多
  - 子节点`childNodes`/一般用`children`但是不是节点，得到的是**伪数组**
  - 兄弟节点`nextElementSibiling`，也可以改成`previous`
- 创建节点`document.createElement('div')`
  - `father.appendChild(son)`,`father.insertBefore(son,beforewhich?)`
  - 应用：之前做的学成在线案例，现在不需要在html里面画盒子了，可以直接把数组搞到数组，for循环到length，创建盒子
```JavaScript
// 1. 获取ul元素
const ul = document.querySelector('.box-bd ul')

// 2. 遍历数据数组
for (let i = 0; i < data.length; i++) {
    // 创建li元素
    const li = document.createElement('li')
    
    // 使用模板字符串填充内容
    li.innerHTML = `
        <a href="#">
            <img src=${data[i].src} alt="">
            <h4>${data[i].title}</h4>
            <div class="info">
                <span>高级</span> • <span>${data[i].num}</span>人在学习
            </div>
        </a>
    `
    
    // 将li添加到ul中
    ul.appendChild(li)
}
```
我的疑问：怎么确定下来每行多少个盒子？
```css
/* 容器设置 */
.box-bd ul {
    width: 1225px;  /* ul的宽度 */
}

.box-bd ul li {
    float: left;    /* 左浮动 */
    width: 228px;   /* 每个li的固定宽度 */
    margin-right: 15px;  /* 右侧间距 */
    margin-bottom: 15px; /* 底部间距 */
}
```

- 克隆与删除节点
  - `ul.appendChild(ul.children[0].cloneNode(true))`如果默认不写true，是浅克隆，只拿过来标签，
  - `removeChild(child)`

3. M端（mobile）事件
- `touchstart`/`touchend`/
- [www.swiper.com.cn](www.swiper.com.cn)
  - 选-下载-看文档-引入-调试

4. 案例：
- form
  - 阻止submit事件，因为点击提交不需要跳转，button点击会冒泡到表单？
  - 表单`reset`
- 手写渲染函数，因为增加和删除都需要渲染
  - 清空`tbody`
  - 循环，模版字符串`tr.innerHTML`，对象属性
  - `tbody.appendChild(tr)`
  - 调用函数
