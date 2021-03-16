//
//  LVTongCengWebMgr.m
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/16.
//

#import "LVTongCengWebMgr.h"
#import "LVApiHandler.h"

@interface LVTongCengWebMgr()
@property (nonatomic, strong) LVApiHandler *apiHandler;
@end

@implementation LVTongCengWebMgr

- (instancetype)init {
    self = [super init];
    if (self) {
        self.apiHandler = [[LVApiHandler alloc] init];
    }
    return self;
}

@end
