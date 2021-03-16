//
//  LVTongCengWebController.m
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/12.
//

#import "LVTongCengWebController.h"
#import "LVTongCengWebView.h"
#import "LVWebViewBridge.h"
#import "LVTongCengWebMgr.h"

@interface LVTongCengWebController ()
@property (strong, nonatomic) WKWebView *webView;
@property (strong, nonatomic) LVTongCengWebMgr *tongCengWebMgr;
@property (strong, nonatomic) LVWebViewBridge *webBridge;
@end

@implementation LVTongCengWebController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    self.title = @"TongCeng WebView";
    
    self.tongCengWebMgr = [[LVTongCengWebMgr alloc] init];
    self.webBridge = [[LVWebViewBridge alloc] initWithDelegate:self.tongCengWebMgr];
    
    WKWebView *webView = [[[self webViewClass] alloc] initWithFrame:self.view.bounds configuration:[self.webBridge genBridgeOfWKUserContentController]];
    [self.view addSubview:webView];
    NSString *htmlPath = [[NSBundle mainBundle] pathForResource:@"tongceng.html" ofType:nil];
    NSString *html = [NSString stringWithContentsOfFile:htmlPath encoding:NSUTF8StringEncoding error:nil];
    [webView loadHTMLString:html baseURL:nil];
    self.webView = webView;
}

- (Class)webViewClass {
    return LVTongCengWebView.class;
}

@end
