//
//  AppDelegate.m
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/11.
//

#import "AppDelegate.h"
@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    self.window.backgroundColor = [UIColor whiteColor];
    UIStoryboard *sb = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    UIViewController *vc = sb.instantiateInitialViewController;
    self.window.rootViewController = vc;
    [self.window makeKeyAndVisible];
    return YES;
}

@end
