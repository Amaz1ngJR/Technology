# CSS 

## CSS语法
```css
selector {
    property: value;
}
```

## CSS选择器
### 元素选择器
```css
p {
    color: red;
}
```

### 类选择器
```css
p.class {
    color: red;
}
```

### ID选择器
```css
#id {
    color: red;
}
```

### 属性选择器
```css
p[class="class"] {
    color: red;
}
```

### 伪类选择器
```css
p:hover {
    color: red;
}
```

### 伪元素选择器
```css
p::before {
    content: "Hello ";
}
```

### 组合选择器
```css
p, div {
    color: red;
}
```