//
//  LVApiHandleDelegate-Protocol.h
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/16.
//

#import <WebKit/WebKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol LVApiHandleDelegate <NSObject>

- (void)webView:(WKWebView *)webView invoke:(NSDictionary *)jsonData;

@end

NS_ASSUME_NONNULL_END
