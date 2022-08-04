# AVR - Arduino Uno: Normal mode with interrupt as timer interval indicator
A code demonstrating the use of timers operating in Normal mode, to indicate timer intervales/period as well as
to continue oscillation, an interrupt is used.

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
start counting from that value instead of from 0.

An interrupt would then be triggered everytime the Counter, TCNT1 reaches
the maximum value. This can be implemented by enabling bit TOIE1 in TIMSK1.

```diff
- NOTE THAT LED WOULD BLINK EVERY OTHER SECOND INSTEAD OF PER-SECOND
```
This is because of the characteristics of the waveform (sawtooth).
It is better understood by taking a clock with you and observe
the seconds value on the clock as the LED turns ON and OFF.

Another thing to note is after every interrupt trigger, we set the counter
value back to the factor we defined (TCINT1 = factor;), so that the counter
would begin counting again from starting value to max value and then trigger
the interrupt again and so on.

##  How to upload the code:
### A. Through Arduino IDE
       1. Copy main.c content as text
       2. Paste it to an empty Arduino sketch
       3. Connect Arduino-Uno through USB
       4. Upload code through the button
    
       
### B. Command line
       1. Make sure you have AVR-GCC toolchain installed, this include GNU-Make and AVRDude.
       2. The only files you are going to need for this method are "main.c" and "Makefile"
       3. Simply open CMD or terminal with its directory set to the location in which you
          have both of those files in.
       4. Type "make" as a command without the quotes.
       5. Makefile automates the process.



