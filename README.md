# AVR - Arduino Uno: Timers in Compare Match Mode
A code demonstrating the use of timers. In this code a 16-bit timer, Timer 1, is used to turn the built-in LED ON and OFF at precise time intervals.

## Concept and Formula derivation
The system clock (16MHz) completes a cycle which is the period
T = 1/f = 1/16MHz = 6.25E-8 sec or every 6.25-ns.
	
16-bit is used in this code, 16-bit is 65,536) in decimal
2^16 = 0xFFFF = 65,536
In that sense, if prescaler is set to 1, every 6.25-ns,
TCNT1  begins ramping up in value from 0-65535 and goes
back to 0 after reaching the max value, 65535, or after
completing a period, which is every 6.25-ns.
	
And its counting speed is modified by the system clock and
the set prescaler value, in this case 1, so from 0 to peak
65535, the period is now, 
```
timer_bit/(system_clock/prescaler) = ~4ms
```	
A prescaler setting using the formula provided above would result to
a period of ~1.049s. If a more precise preiod is needed for example, 
exactly 1-sec, one must offset the waveform by a factor in order
to force the counter (TCNT1) to start counting at a certain value
and towards the maximum value. So instead of it counting from 0,
it would start at a target value.
	
To implement this idea mathematically, the steps within 1-sec is
first calculated (S) by modifying the first formula,knowing that
the value on the right side of the equation is the period,
```
S/(s/p) = T
```
where S is the steps completed within a period (T)
s is frequency and p is the set prescaler value. Therefore,
```
S = (T * s)/p
```
	
However that is not the correcting factor we want to use
that is just the new amount of steps that is completed
if the period is 1-sec. So to get the factor, 
```
factor = timer_bit - S
```
We then equate that factor to TCNT1 so that it will
start counting from that value instead of from 0
