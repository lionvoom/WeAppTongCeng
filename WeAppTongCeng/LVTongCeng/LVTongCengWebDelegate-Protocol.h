//
//  LVTongCengWebDelegate-Protocol.h
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/16.
//

#import <Foundation/Foundation.h>
#import "LVApiHandleDelegate-Protocol.h"

NS_ASSUME_NONNULL_BEGIN

@protocol LVTongCengWebDelegate <NSObject>
@property (readonly) id<LVApiHandleDelegate> apiHandler;
@end

NS_ASSUME_NONNULL_END
