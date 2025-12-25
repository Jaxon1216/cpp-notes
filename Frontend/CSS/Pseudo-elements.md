<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<style>

.section-title::before {
    content: "✨ ";
    color: gold;
}

.section-title::after {
    content: "";
    display: block;
    width: 50px;
    height: 3px;
    background: linear-gradient(to right, #ff6b6b, #4ecdc4);
    margin-top: 5px;
}
</style>

<body>
    <h2 class="section-title">我们的服务</h2>
</body>
</html>