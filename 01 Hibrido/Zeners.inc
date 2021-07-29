* class-a mosfet amp 30W, gain of 30dB
* variation with current opposing 1st stage, fixed current source opposing 2nd stage
* ideal power supply
x1 vdd1 vss1 vdd2 vss2 pwrideal
* simulated power supply with ripple
*x1 vdd1 vss1 vdd2 vss2 pwrreal
* input drive for 30W into 8ohm
*v1 vin 0 dc 0 ac 1 distof1 1 0 sin (0 692.82m 1k)
* input drive for 30W into 4ohm
*v1 vin 0 dc 0 ac 1 distof1 1 0 sin (0 489.898m 1k)
* input drive for 2.828Vrms
*v1 vin 0 dc 0 ac 1 distof1 1 0 sin (0 126.491m 1k)
* input drive for peak
*v1 vin 0 dc 0 ac 1 distof1 1 0 sin (0 692.82m 1k)
* input drive for clip
*v1 vin 0 dc 0 ac 1 distof1 1 0 sin (0 1.07331 1k)
* input for 0V ac to use fourier to measure hum at output
*v1 vin 0 dc 0 ac 1 distof1 1 0 sin (0 0 120)
* input to measure slew rate
v1 vin 0 dc 0 ac 1 distof1 1 0 pulse (-0.7 0.7 0 0 0 5u 10u)
*v1 vin 0 dc 0 ac 1 distof1 1 0 sin (0 0.7 20k)
*input load
r1 vin 0 100k
*coupling capacitor c1 commented out because
*  it interferes with dc transfer curve analysis
*c1 vin vinac 10u
r2 vin 0 100k
* slew rate analysis has not been done to obtain a final value for c2
*c2 vinac 0 30p
rg vs 0 221
* open loop analysis: change vout here to vloop, and vin to vloop at source
rf vout vs 4.99k
* open loop analysis: uncomment vgndvin to connect input to ground
*vgndvin vin 0 dc 0
* input stage
j1 vdj1 vin vs lsk170c
j2 vd vz3 vdj1 lsk170c
j3 vdj1 vin vs lsk170c
j4 vd vz3 vdj1 lsk170c
r6 vs vz1 620
r5 vd vdd1 2k
q1 vb1 ve1 vdd1 2n3906
q2 vd vb1 ve1 2n3906 
* adjust r3 to bias second stage for vout=0
r3 vdd1 ve1 74.27
r4 vz3 vb1 5.6k
* bias
xbias vz1 vz2 vz3 vdd1 vss1 biaszener
*xbias vz1 vz2 vz3 vdd1 vss1 biasideal
* second stage amplifier
r10 vd vg1 56
m1 A vg1 vdd1 vdd1 irf9510 L=2u W=200m
* second stage current source load
r12 vz2 vbias 10k
q3 vbias vsm2 vss1 2n3904
r13 vbias vg2 56
m2 B vg2 vsm2 vsm2 irf510 L=2u W=640m
r14 vsm2 vss1 5.1
* second stage resistive load (best place to alter open loop gain)
* inital values, low open-loop gain
*r15 A 0 1.5k
*r16 B 0 1.5k
* medium open-loop gain
*r15 A 0 1.8k
*r16 B 0 1.8k
* matched to give same distortion as vfb at r11/12=1.8k
*r15 A 0 3.6k
*r16 B 0 3.6k
* high open-loop gain
r15 A 0 6k
r16 B 0 6k
* ammeters for second stage adjustment normally commented out
*vaa A 0 dc 0
*vab 0 B dc 0
* follower bias
* 4A bias
r17 A B 68
c6 A B 100u ic=7.618
* output follower
* original m3/m4 L=2U W=680M, adjust up 5% as hand picked higher
r18 A vg3 56
m3 vdd2 vg3 vout vout irfp240 L=2U W=714M
r19 A vg4 56
m4 vdd2 vg4 vout vout irfp240 L=2U W=714M
* original m5/m6 L=2U W=1.4, adjust down 5% as hand picked lower
r20 B vg5 56
m5 vss2 vg5 vout vout irfp9240 L=2U W=1.33
r21 B vg6 56
m6 vss2 vg6 vout vout irfp9240 L=2U W=1.33
* load
rl vout 0 8
.subckt biaszener vz1 vz2 vz3 vdd1 vss1
r11 vdd1 vz3 1.6k
d3 0 vz3 1N4744
c5 vz3 0 100u ic=14.6
d1 vz1 0 1n4735
c3 0 vz1 100u ic=6
j5 vz1 vgj5 vs5 2n3819
r7 vs5 vgj5 10
j6 vz1 vgj5 vs6 2n3819
r8 vs6 vgj5 10
r9 vgj5 vz2 300
d2 vss1 vz2 1n4735
c4 vz2 vss1 100u ic=6
.ends
.subckt biasideal vz1 vz2 vz3 vdd1 vss1
vbias1 0 vz1 dc 6.11506
vbias2 vz2 vss1 dc 6.123507
vbias3 vz3 0 dc 14.9749
.ends
* models
.MODEL 1N4735 D IS=15N N=2.22 BV=6.2 IBV=41M 
+      RS=169M CJO=4P VJ=750M M=330M TT=100N
.MODEL 1N4744 D IS=15N N=2.22 BV=15 IBV=17M 
+      RS=169M CJO=4P VJ=750M M=330M TT=100N
.MODEL LSK170A NJF
+ BETA   = 0.0378643       VTO    = -0.4025156      LAMBDA = 4.783719E-3        
+ IS     = 3.55773E-14      
+ RD     = 10.6565         RS     = 6.8790487                    
+ CGD    = 3.99E-11        CGS    = 4.06518E-11        
+ PB     = 0.981382        FC     = 0.5                
+ KF     = 0               AF     = 1
.MODEL LSK170B NJF
+ BETA   = 0.0350699       VTO    = -0.5375582      LAMBDA = 4.951E-3           
+ IS     = 2.76212E-14
+ RD     = 7.82168         RS     = 6.9525888
+ CGD    = 4.36E-11        CGS    = 4.36E-11           
+ PB     = 1.2             FC     = 0.5                
+ KF     = 0               AF     = 1
*
.MODEL LSK170C NJF          
+ BETA   = 0.0278541       VTO    = -0.800434       LAMBDA = 0.0122435          
+ IS     = 2.45217E-14  
+ RD     = 12              RS     = 5.8             CGD    = 4.22E-11           
+ CGS    = 4.23E-11        PB     = 0.9265487
+ FC     = 0.5             KF     = 0               AF     = 1                       
.MODEL 2N3819 NJF VTO=-2.9985 BETA=1.3046M LAMBDA=2.2507M RD=1 RS=1 
+      CGD=1.5964P CGS=2.4199P PB=500M IS=33.582F KF=0 AF=1
.MODEL 2N3904 NPN IS=9.99F NF=1 NR=1 RE=2.51 RC=1 
+      RB=10 VAF=40 VAR=20 ISE=4.03P ISC=4.03P 
+      NE=1.78 NC=1.78 BF=679 
+      BR=5 IKF=13.8M IKR=13.8M CJC=3.6P CJE=3.99P 
+      CJS=0 VJC=878M VJE=16.1 VJS=750M MJC=307M 
+      MJE=2.01 MJS=0 TF=531P TR=69N EG=1.11 
+      KF=0 AF=1
.MODEL 2N3906 PNP IS=1.77F RE=732M RC=1 RB=10 VAF=23.3 
+      VAR=11.7 ISE=73.2F ISC=73.2F NE=1.62 NC=1.62 
+      BF=289 BR=5 IKF=29.2M IKR=29.2M CJC=6.95P 
+      CJE=6.86P VJC=374M VJE=100M MJC=340M MJE=199M 
+      TF=637P TR=82.8N
.MODEL IRF510 NMOS LEVEL=3 VTO=3.699 KP=20.82U RD=21.08M 
+      RS=450.8M IS=202.7F CBD=366.6P 
+      CGSO=604.9P CGDO=62.62P
.MODEL IRF9510 PMOS LEVEL=3 VTO=-3.919 KP=10.45U UO=300 
+      RD=452.3M RS=371.5M IS= 2.891E-18 
+      CBD=333.8P CGSO=2.533N CGDO=313.6P 
.MODEL IRFP240 NMOS LEVEL=3 VTO=3.76 KP=20.79U RD=75.29M 
+      RS=20.68M IS=2.9P CBD=1.933N 
+      CGSO=1.457N CGDO=317.1P
.MODEL IRFP9240 PMOS LEVEL=3 VTO=-3.828 KP=10.65U UO=300 
+      RD=279.3M RS=76.83M IS=2.08P 
+      N=2 CBD=1.534N CGSO=961.9P CGDO=138.4P
.include ./pwr.txt
.end
.control
set units=degrees
op
print all
*ac dec 25 10Hz 1GHz
*setplot ac1
*plot db(5)
noise v(5) v1 dec 25 20Hz 20kHz
setplot noise2
print all
*setplot noise1
*plot onoise_spectrum
*set fourgridsize=1024
set nfreqs=16
set polydegree=3
* transient analysis for 1k fourier
*tran 1u 0.1 0 1u uic
*fourier 1k vout
* transient analysis for 20k fourier
*tran 50n 5m 0 50n uic
*fourier 20k vout
* transient analysis for 1M squarewave slew
tran 1n 100u 0 1n uic
plot vout xindices 80000 100000
* transfer error plots
dc v1 -0.1 0.1 0.001
plot vout-(vin*(vout[200]-vout[0])/0.2)
dc v1 -0.7 0.7 0.007
plot vout-(vin*(vout[200]-vout[0])/1.4)
.endc
