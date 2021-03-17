[TOC]

# 引言

> 自微信小程序火了后, 个大头部厂商也纷纷效仿, 给自己的客户端提供了小程序框架支持.
>
> 小程序框架为了提升小程序页面的极致用户体验,做了同层渲染. (小程序页面是`webview实现的`)
>
> 抛砖引玉: **我们今天的目的就是实现 `WKWebView同层渲染`**

![weapp.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/cd50590ab184460883662eb935017b1d~tplv-k3u1fbpfcp-watermark.image)





# 同层渲染原理 

**熟悉的可跳过本小节**, 不了解的请先看 [【走进小程序原理】揭秘组件同层渲染](https://blog.csdn.net/Smartprogram/article/details/108124407) 

- 腾讯 [微信小程序同层渲染原理剖析](https://developers.weixin.qq.com/community/develop/article/doc/000c4e433707c072c1793e56f5c813?page=1)
- 百度[【走进小程序原理】揭秘组件同层渲染](https://blog.csdn.net/Smartprogram/article/details/108124407) **(推荐)**
- 阿里 [亿级用户高稳定性视频播放器养成计划|618淘系前端技术分享](https://mp.weixin.qq.com/s/jgsG-XrAKV6AHSrUCRhKtQ)


> 总结一下这些文章, 比如[微信小程序同层渲染原理剖析](https://developers.weixin.qq.com/community/develop/article/doc/000c4e433707c072c1793e56f5c813?page=1), 讲到最后还是只阐述了基本实现思路, 并没有教你怎么实现, 然并卵. 

> 看完之后各大技术论坛的“同层渲染原理分析”的你, 还是实现不了.

> 年轻人想太多, 怎么可能教你, 这属于核心技术诶.

![wx-blog.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/c71269a729e74bcd890056b26f283ad4~tplv-k3u1fbpfcp-watermark.image)






# 总结同层渲染原理

同层渲染, 就是在webview中内嵌原生组件, 再通过`JS - Native`交互进行控制, 达到融合效果. 

如下图最后的效果所示, 插入原生同层组件后, H5组件仍然可以覆盖在其上面.
![tongceng.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/2a6ee6be963b4db38339762b34ccb837~tplv-k3u1fbpfcp-watermark.image)





# **实现**同层渲染

## 1. H5代码范例

```
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

```
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


## 2. 在`WKChildScrollView`上添加`LVContainerView(自定义UIView)`

![insert-native.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/de6fc5818cef4abb87440967a1ae6bf2~tplv-k3u1fbpfcp-watermark.image)



## 3. `LVContainerView`上添加相应原生组件(同层渲染组件)

比如: `input` ` textarea` ` video` ` live-player` `live-pusher` 等



## 4. 处理`WKContentView`手势拦截

```
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



## 5. 查找同层渲染组件响应者, 以实现交互
```
@implementation LVTongCengWebView

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event {
    UIView *wkHitView = [super hitTest:point withEvent:event];
    
    // Handling the WKContentView GestureRecognizers interception event causing the inserted native control to fail to respond
    // 处理 WKContentView gestureRecognizers 拦截事件,导致插入的原生控件无法响应
    if (!self.didHandleWKContentGestrues) {
        [self _handleWKContentGestrues];
        self.didHandleWKContentGestrues = YES;
    }
    
    // WKChildScrollView -[hitTest:withEvent:]
    if ([wkHitView isKindOfClass:NSClassFromString(@"WKChildScrollView")]) {
        for (UIView *subview in [wkHitView.subviews reverseObjectEnumerator]) {
            CGPoint convertedPoint = [subview convertPoint:point fromView:self];
            UIView *hitTestView = [subview hitTest:convertedPoint withEvent:event];
            if (hitTestView) {
                wkHitView = hitTestView;
                break;
            }
        }
    }
    
    // NSLog(@"hitTest: %@", wkHitView);
    return wkHitView;
}

@end
```



## 6. 验证同层渲染
![demo-blur.png](https://p1-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/6a8415a716e942669482a2339073ddd1~tplv-k3u1fbpfcp-watermark.image)


---
**Talk is cheap. Show me the code.**  
[https://github.com/lionvoom/WeAppTongCeng](https://github.com/lionvoom/WeAppTongCeng)
