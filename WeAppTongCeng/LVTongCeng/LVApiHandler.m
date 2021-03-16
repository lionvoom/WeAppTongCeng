//
//  LVApiHandler.m
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/16.
//

#import "LVApiHandler.h"
#import <WebKit/WebKit.h>
#import "LVContainerView.h"

@implementation LVApiHandler

#pragma mark - LVApiHandleDelegate
- (void)webView:(WKWebView *)webView invoke:(NSDictionary *)jsonData {
    NSString *api = jsonData[@"api"];
    NSDictionary *args = jsonData[@"args"];
    UIView *containerSuperview = [self dfsSearch:webView.scrollView containerId:args[@"cid"]];
    if (!containerSuperview) return;
    LVContainerView *containerView = [self insertContainerView:containerSuperview];
    if ([api isEqualToString:@"insertInput"]) {
        [self insertInput:containerView];
    } else if ([api isEqualToString:@"insertTextArea"]) {
        [self insertTextArea:containerView];
    } else if ([api isEqualToString:@"insertVideo"]) {
        [self insertVideo:containerView];
    }
}

- (UIView *)dfsSearch:(UIView *)view containerId:(NSNumber *)containerId {
    //TODO: optimize
    NSString *str = [NSString stringWithFormat:@"class='container cid_%@'", containerId];
    if ([view.description containsString:str]) {
        UIView *_WKChildScrollView = view.subviews.firstObject;
        if (![_WKChildScrollView isKindOfClass:NSClassFromString(@"WKChildScrollView")]) return nil;
        for (UIGestureRecognizer *ges in _WKChildScrollView.gestureRecognizers) {
            [_WKChildScrollView removeGestureRecognizer:ges];
        }
        return _WKChildScrollView;
    }
    for (UIView *subView in view.subviews) {
        UIView *findView = [self dfsSearch:subView containerId:containerId];
        if (findView) return findView;
    }
    return nil;
}

- (void)insertInput:(LVContainerView *)containerView {
    UITextField *textField = [[UITextField alloc] initWithFrame:containerView.bounds];
    textField.backgroundColor = UIColor.lightGrayColor;
    textField.placeholder = @"请输入";
    [containerView addSubview:textField];
}

- (void)insertTextArea:(LVContainerView *)containerView {
    UITextView *textView = [[UITextView alloc] initWithFrame:containerView.bounds];
    textView.backgroundColor = UIColor.brownColor;
    [containerView addSubview:textView];
}

- (void)insertVideo:(LVContainerView *)containerView {
    UIButton *btn = [[UIButton alloc] initWithFrame:containerView.bounds];
    btn.backgroundColor = UIColor.blueColor;
    [btn setTitle:@"请替换成video组件" forState:UIControlStateNormal];
    [containerView addSubview:btn];
    [btn addTarget:self action:@selector(btnAction:) forControlEvents:UIControlEventTouchUpInside];
}

- (LVContainerView *)insertContainerView:(UIView *)containerSuperview {
    LVContainerView *containerView = [[LVContainerView alloc] initWithFrame:containerSuperview.bounds];
    [containerSuperview addSubview:containerView];
    return containerView;
}

- (void)btnAction:(UIView *)view {
    UIColor * randomColor= [UIColor colorWithRed:((float)arc4random_uniform(256) / 255.0) green:((float)arc4random_uniform(256) / 255.0) blue:((float)arc4random_uniform(256) / 255.0) alpha:1.0];
    view.backgroundColor = randomColor;
}

@end
