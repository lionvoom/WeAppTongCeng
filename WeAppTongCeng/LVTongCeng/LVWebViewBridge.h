//
//  LVWebViewBridge.h
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/16.
//

#import <WebKit/WebKit.h>
#import "LVTongCengWebDelegate-Protocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface LVWebViewBridge : NSObject

- (instancetype)initWithDelegate:(id<LVTongCengWebDelegate>)delegate;

- (WKWebViewConfiguration *)genBridgeOfWKUserContentController;

@end

NS_ASSUME_NONNULL_END
