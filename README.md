> 自微信小程序火了后, 个大头部厂商也纷纷效仿, 给自己的客户端提供了小程序框架支持. 然而小程序框架为了提升小程序页面的极致用户体验, 做了**同层渲染**.

​        **抛砖引玉:**

​        **我们今天的目标就是: 从0到1实现iOS端`WKWebView`同层渲染, 文章末尾有DEMO演示, 也有源码地址.**

![weapp.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/cd50590ab184460883662eb935017b1d~tplv-k3u1fbpfcp-watermark.image)





# 同层渲染原理 

「同层渲染」就是把原生组件绘制在 `WebView` 所渲染的页面中，与其他 `HTML` 控件在同一层级，效果如下图所示:
![同层渲染原理.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/f137ab9d5bd84220a1ffdef641912882~tplv-k3u1fbpfcp-watermark.image)

这里我给大家找到三篇比较官方的文章, 建议跳过看总结:

- 腾讯 [微信小程序同层渲染原理剖析](https://developers.weixin.qq.com/community/develop/article/doc/000c4e433707c072c1793e56f5c813?page=1)
- 百度[【走进小程序原理】揭秘组件同层渲染](https://blog.csdn.net/Smartprogram/article/details/108124407) **(推荐)**
- 阿里 [亿级用户高稳定性视频播放器养成计划|618淘系前端技术分享](https://mp.weixin.qq.com/s/jgsG-XrAKV6AHSrUCRhKtQ)


> 总结
>
> 这些文章只阐述了基本实现思路, 并没有教你怎么实现, 然并卵. 
>
> 看完之后各大技术论坛的“同层渲染原理分析”的你, 还是实现不了.
> **下面我们一起来实现一个.**



# 实现同层渲染

## 1. 我们在前端H5页面上创建一个需要生成原生组件的`DOM`节点.

```html
<div class="container cid_1" data-component-type="input" style="width: 200px; height: 40px">
    <div style="width: 101%; height: 101%">&nbsp;</div>
</div>

<style>
    .container { 
        /* insert WKChildView in WKWebView */
        overflow: scroll;
        -webkit-overflow-scrolling: touch;
    }
</style>
```

## 2. 前端会把原生组件类型如`cid`、`position`等信息通过`window.webkit.messageHandlers.handle.postMessage`发送给iOS端.

```javascript
<script>
    // 管理同层渲染组件, 通知原生创建同层渲染组件
    function insertNativeComponents() {
        var containers = document.getElementsByClassName("container");
        console.log(containers);
        for (var i = 0; i < containers.length; i++) {
            var ct = containers[i];
            var component_type = ct.getAttribute("data-component-type");
            if (!component_type) continue;
            var cid = ct.getAttribute("class").split(" ")[1];
            var cid_num = cid.slice("cid_".length);
            var frame = ct.getBoundingClientRect();
            var args = {
                "position": {
                    "top": frame.top,
                    "left": frame.left,
                    "width": frame.width,
                    "height": frame.height
                },
                "cid": cid_num
            };
            switch (component_type) {
                case "input": {
                    nativeInvoke("insertInput", args);
                }
                break;

                case "textArea": {
                    nativeInvoke("insertTextArea", args);
                }
                break;
    
                case "video": {
                    nativeInvoke("insertVideo", args);
                }
                break;
            }
        }
    }

    function nativeInvoke(api, args) {
        console.log(api, args);
        //TODO: judge platform iOS / Android
        var platform = "ios";
        if (platform === "ios") {
            window.webkit.messageHandlers.handle.postMessage({
                "api": api,
                "args": args
            });
        }
    }   
    
    setTimeout("insertNativeComponents()", 100);
</script>
```

## 3. iOS端WKWebView消息代理接收到前端发来的消息

```objective-c
- (void)userContentController:(WKUserContentController *)userContentController didReceiveScriptMessage:(WKScriptMessage *)message {
        // 收到前端的消息
        // message.name: handle
    // message.body: {"api":"insertInput","args":{"cid":"1","position":{"top":30,"width":200,"left":87.5,"height":40}}}
}
```

## 4. iOS端可以通过消息中的`cid`匹配查找相应`WKChildScrollView`，并将原生组件挂载到该节点上作为其子View.

![图片](https://note.youdao.com/yws/api/personal/file/WEB5d27628125737e47e5547909cf3f6c90?method=download&shareKey=bcf19a277ca029ac0169efcd1c4a32a2)



## 5. 最后我们发现WKWebView中插入的原生组件是无法响应交互事件的，需要特殊处理.

这里我们需要处理两件事，一是屏蔽`WKContentView`手势拦截事件响应链的传递，让事件可以传递到原生组件中，命令如下：

```objective-c
@implementation LVTongCengWebView

- (void)_handleWKContentGestrues {
    UIScrollView *webViewScrollView = self.scrollView;
    if ([webViewScrollView isKindOfClass:NSClassFromString(@"WKScrollView")]) {
        UIView *_WKContentView = webViewScrollView.subviews.firstObject;
        if (![_WKContentView isKindOfClass:NSClassFromString(@"WKContentView")]) return;
        NSArray *gestrues = _WKContentView.gestureRecognizers;
        for (UIGestureRecognizer *gesture in gestrues) {
            gesture.cancelsTouchesInView = NO;
            gesture.delaysTouchesBegan = NO;
            gesture.delaysTouchesEnded = NO;
        }
    }
}

@end
```

二是重写iOS端`原生组件`容器`LVContainerView`协议检测方法`-conformsToProtocol:`，目的是绕过`WKNativelyInteractible`协议检测，从而在点击WKWebView的时候，容器`LVContainerView`及其子view（原生组件）可以正常进行事件响应。

```objective-c
@implementation LVContainerView

- (BOOL)conformsToProtocol:(Protocol *)aProtocol {
    if (aProtocol == NSProtocolFromString(@"WKNativelyInteractible")) {
        return YES;
    }
    return [super conformsToProtocol:aProtocol];
}

@end
```



到这里，经过前面这些步骤，我们就实现了iOS端`WKWebView`的`同层渲染`，下面让我们来看看实现效果：

1. 我们可以看到原生组件`UITextField`、`UITextView`响应聚焦输入，`UIButton`可以点击变颜色，实现了正常交互；
2. H5蒙层可以遮挡住`原生组件`，解决了`WKWebView`内嵌原生组件的层级限制问题，完美体现了`同层`的含义。

<div>
    <img src="https://note.youdao.com/yws/api/personal/file/WEB879018ffe384866e1d46431b6564e25c?method=download&shareKey=0715a0d76413c10dac2a50736ec4141f" style="width: 300px"/>
</div>

**Talk is cheap. Show me the code.**  
DEMO地址: [https://github.com/lionvoom/WeAppTongCeng](https://github.com/lionvoom/WeAppTongCeng)

**极客时间-每日一课**
[iOS小程序同层渲染到底怎么实现?](https://time.geekbang.org/dailylesson/detail/100075719)
