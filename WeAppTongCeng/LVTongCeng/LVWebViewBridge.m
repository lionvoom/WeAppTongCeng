//
//  LVWebViewBridge.m
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/16.
//

#import "LVWebViewBridge.h"
#import "LVWeakProxy.h"

@interface LVWebViewBridge() <WKScriptMessageHandler>
@property (nonatomic, weak) id<LVTongCengWebDelegate> delegate;
@end

@implementation LVWebViewBridge

- (instancetype)initWithDelegate:(id<LVTongCengWebDelegate>)delegate {
    if (self = [super init]) {
        self.delegate = delegate;
    }
    return self;
}

- (WKWebViewConfiguration *)genBridgeOfWKUserContentController {
    WKUserContentController *userContentController = WKUserContentController.new;
    LVWeakProxy *weakProxy = [LVWeakProxy proxyWithTarget:self];
    [userContentController addScriptMessageHandler:(id<WKScriptMessageHandler>)weakProxy name:@"handle"];
    WKWebViewConfiguration *configuration = [WKWebViewConfiguration new];
    configuration.userContentController = userContentController;
    return configuration;
}

#pragma mark - WKScriptMessageHandler
- (void)userContentController:(WKUserContentController *)userContentController didReceiveScriptMessage:(WKScriptMessage *)message {
    NSString *name = message.name;
    id body = message.body;
    NSString *selName = [NSString stringWithFormat:@"webView:%@:", name];
    SEL selector = NSSelectorFromString(selName);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
    if (![self respondsToSelector:selector]) {
        NSLog(@"[NO IMP]：%@", selName);
        return;
    }
    [self performSelector:selector withObject:message.webView withObject:body];
#pragma clang diagnostic pop
}

- (void)webView:(WKWebView *)webView handle:(NSDictionary *)jsonData {
    [self.delegate.apiHandler webView:webView invoke:jsonData];
}

@end
