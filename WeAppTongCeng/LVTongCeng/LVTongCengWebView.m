//
//  LVTongCengWebView.m
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/11.
//

#import "LVTongCengWebView.h"

@interface LVTongCengWebView()
@property (nonatomic, assign) BOOL didHandleWKContentGestrues;
@end

@implementation LVTongCengWebView

- (void)_handleWKContentGestrues {
    UIScrollView *webViewScrollView = self.scrollView;
    if ([webViewScrollView isKindOfClass:NSClassFromString(@"WKScrollView")]) {
        UIView *_WKContentView = webViewScrollView.subviews.firstObject;
        if (![_WKContentView isKindOfClass:NSClassFromString(@"WKContentView")]) return;
        NSArray *gestrues = _WKContentView.gestureRecognizers;
        Class clz = NSClassFromString(@"UITextTapRecognizer");
        for (UIGestureRecognizer *gesture in gestrues) {
            // fix: 原生输入框聚焦时, 再次点击会失焦
            if ([gesture isKindOfClass:clz]) {
                gesture.enabled = NO;
                continue;
            }
            gesture.cancelsTouchesInView = NO;
            gesture.delaysTouchesBegan = NO;
            gesture.delaysTouchesEnded = NO;
        }
    }
}

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event {
    UIView *wkHitView = [super hitTest:point withEvent:event];
    
    // Handling the WKContentView GestureRecognizers interception event causing the inserted native control to fail to respond
    if (!self.didHandleWKContentGestrues) {
        [self _handleWKContentGestrues];
        self.didHandleWKContentGestrues = YES;
    }
    
    // Plan A: LVContainerView conforms to protocol WKNativelyInteractible
    // Plan B: WKChildScrollView -[hitTest:withEvent:]
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
