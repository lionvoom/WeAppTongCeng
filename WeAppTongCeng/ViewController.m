//
//  ViewController.m
//  WeAppTongCeng
//
//  Created by lionvoom on 2021/3/11.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (IBAction)toWKWebViewVC:(id)sender {
    [self.navigationController pushViewController:NSClassFromString(@"LVWKWebController").new animated:YES];
}

- (IBAction)toTongCengWebViewVC:(id)sender {
    [self.navigationController pushViewController:NSClassFromString(@"LVTongCengWebController").new animated:YES];
}


@end
