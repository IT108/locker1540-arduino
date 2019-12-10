# DipTrace Auto-Generated DO File
bestsave off
grid via 0.0039
grid wire 0.0039
define (class Dip_Net_Class_0 button_exit gerkon_on gerkon_open Locker@- Net@0 Net@1 Net@2 Net@3 Net@4 Net@5 Net@6 Net@7 Net@8 Net@9 Net@10 Net@11 Net@12 Net@13 Net@14 Net@15 Net@16 Net@17 Net@18 Net@19 Net@20 Net@21 Net@22 Net@23 Net@24 Net@25 Net@26 Net@27 Net@28 Net@29 Net@30 Net@31 Net@32 Net@33 Net@34 Net@35 Net@36 Net@37 Net@38 Net@39 Net@43 Net@44 Net@45 Net@47 Net@48 Net@49 Net@51 Net@53 Net@54 Net@55 Net@56 Net@57 Net@58 Net@59 Net@60 Net@61 Net@62 Net@63 Net@64 Net@65 Net@66 Net@68 Net@69 Net@70 Net@71 Net@72 Net@73 Net@74 Net@75 Net@77 Net@78 Net@79 Net@80 Net@81 Net@82 Net@83)
circuit class Dip_Net_Class_0 (use_via DipViaStyle_0)
rule class Dip_Net_Class_0 (width 15.748)
rule class Dip_Net_Class_0 (clearance 15.748)
define (class Dip_Net_Class_1 12V 5V GND)
circuit class Dip_Net_Class_1 (use_via DipViaStyle_0)
rule class Dip_Net_Class_1 (width 25.9843)
rule class Dip_Net_Class_1 (clearance 15.748)
define (class Dip_Net_Class_2)
circuit class Dip_Net_Class_2 (use_via DipViaStyle_0)
rule class Dip_Net_Class_2 (width 7.874)
rule class Dip_Net_Class_2 (clearance 7.874)
rule pcb (pin_width_taper down)
bus diagonal
route 20
clean 2
route 25 16
clean 2
filter 5
recorner diagonal
