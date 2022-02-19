# Automatic Dam Shutter System
<img src="images/dam gate.jpg" width=900>

## Circuit Diagram:
<img src="images/circuit diagram for ADS.PNG" width=600>

## Algorithm:
1. Get distance of water from **SONAR** and convert distance to height using `damHeight`.
2. If the height of water is too high (`heightWater>heighOpen`) start opening the gate (start the motor).
3. Once enough time has passed (`openTok - openTik > openTime`) stop opening the gate (stop the motor).
4. If the height is neither too high nor too low (`heightClose<heightWater<heightOpen`) keep the motor off.
5. If gate is open(`isOpen=true`) and height of the water is too low (`heightWater<heightClose`) start closing nthe gate (start the motor in oposite direction).
6. Once enough time has passed (`closeTok - closeTik > closeTime`) stop closing the gate (stop the motor).

## Total States: 4
1. Opening
2. Opened
3. Closing
4. Closed

## Caution:
1. Keep `heightClose` & `heightOpen` value close.
2. Keep `heightClose` > Mininum water height when gate is open.
