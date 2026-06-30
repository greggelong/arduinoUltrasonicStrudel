// Your Arduino is gamepad #0
const gp = gamepad(0);

// Map distance to pitch (100Hz to 2000Hz)
// Close = high pitch, Far = low pitch
let freq = gp.x1.range(100, 2000)

setCpm(140 / 4) // 140 BPM

// Drums
$: s("bd ~ bd ~")
   .stack(s("~ sd ~ sd"))
   .stack(s("hh ~ hh ~"))
   .gain(0.3)

// Melody controlled by distance
$: note("c4")
   .sound("sawtooth")
   .freq(freq)
   .gain(0.9)
   .release(0.2)
