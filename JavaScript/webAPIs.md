# day1DOM元素获取与操作
- DOM对象，DOM树
- 获取`querySelectorALL`,`queryselector`
- 属性`innerText`不解析标签,`innnerHTML`解析标签
- `style`属性,宽高背景色等
- 类名或者`classList`控制css，追加类名，`add,remove,toggle(classname)`
- 表单属性`value` ,`type`
- 自定义属性`data-id`,`对象.dataset.id`，获取的时候别忘记`#`号
- 间歇函数`setInterval`,m级别单位set对应clear
- 案例：轮播图定时版，注意li标签下标从1开始 

# day2DOM事件基础
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


# day3DOM进阶
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