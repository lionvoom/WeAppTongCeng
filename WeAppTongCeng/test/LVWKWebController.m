//
//  LVWKWebController.m
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/16.
//

#import "LVWKWebController.h"

@interface LVWKWebController ()

@end

@implementation LVWKWebController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"WKWebView(native no respond)";
}

- (Class)webViewClass {
    return NSClassFromString(@"WKWebView");
}

@end
