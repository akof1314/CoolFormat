// Program to evaluate simple expressions of the form number operator number
// Implement a Calculator number

#import <Foundation/Foundation.h>

@interface Calculator: NSObject
{
    double accumulator;
}

// accumulator methods
-(void)        setAccumulator: (double) value;
-(void)        clear;
-(double)    accumulator;

// arithmetic methods
-(void)        add: (double) value;
-(void)        subtract: (double) value;
-(void)        multiply: (double) value;
-(void)        divide: (double) value;

@end


@implementation Calculator

-(void)        setAccumulator: (double) value
{
    accumulator = value;
}

-(void)        clear
{
    accumulator = 0;
}

-(double)    accumulator
{
    return accumulator;
}

-(void)        add: (double) value
{
    accumulator += value;
}

-(void)        subtract: (double) value
{
    accumulator -= value;
}

-(void)        multiply: (double) value
{
    accumulator *= value;
}

-(void)        divide: (double) value
{
    accumulator /= value;
}

@end


int main (int argc, const char * argv[])
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    double        value1, value2;
    char        operator;
    Calculator    *deskCalc = [[Calculator alloc] init];
    
    NSLog(@"Type in your expression.");
    scanf("%lf %c %lf", &value1, &operator, &value2);
    
    [deskCalc setAccumulator: value1];
    
    if (operator == '+')
        [deskCalc add: value2];
    else if (operator == '-')
        [deskCalc subtract: value2];
    else if (operator == '*')
        [deskCalc multiply: value2];
    else if (operator == '/')
        if (value2 == 0)
            NSLog(@"Division by zero.");
        else
            [deskCalc divide: value2];
    else
        NSLog(@"Unknown operator.");
    
    NSLog(@"%.2f", [deskCalc accumulator]);
    [deskCalc release];
    
    [pool drain];
    return 0;
}