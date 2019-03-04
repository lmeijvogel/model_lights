* Goal

Create an Arduino-based appliance that can switch lights semi-automatically.

** Acceptance criteria

- Switch for each light,

- Three applicance states:
  * All lights off,
  * All lights on,
  * Lights off, transitioning to on,
  * Lights on, transitioning to off.

- Some display that shows what the current state is, for example: three lights:
  * red: off,
  * white: on,
  * red+yellow: off-> on,
  * yellow+white: on -> off.

- Three buttons to switch between states:
  * Turn all lights off,
  * Gradual switch lights on/off (second press reverses direction),
  * Turn all lights on immediately.

* Shopping list

** Core
- Power button: https://www.kiwi-electronics.nl/componenten-onderdelen/componenten/rocker-switch-spst-round
- 8 relay module: https://www.kiwi-electronics.nl/8-kanaals-relais-module
- Input/output expander?
  * 16-ports: https://www.kiwi-electronics.nl/componenten-onderdelen/componenten/ics-transistoren/MCP23017-i2c-16x-input-output-expander
  * 8-ports: https://www.kiwi-electronics.nl/MCP23008-i2c-8x-input-output-expander
  Tutorials:
  https://www.best-microcontroller-projects.com/mcp23017.html
  https://tronixstuff.com/2011/08/26/tutorial-maximising-your-arduinos-io-ports/
- Pulse buttons with lights:
  * https://www.kiwi-electronics.nl/16mm-verlichte-drukknop-aan-uit-wit
  * https://www.kiwi-electronics.nl/16mm-verlichte-drukknop-tijdelijk-geel
  * https://www.kiwi-electronics.nl/16mm-verlichte-drukknop-tijdelijk-rood


** For nice-to-have transition speed selection:
    - Rotary knob
      https://www.kiwi-electronics.nl/componenten-onderdelen/componenten/rotary-encoder-illuminated-red-green

    - 7-segment displays:
      - 1 digit:
        https://www.kiwi-electronics.nl/componenten-onderdelen/leds/led-segmenten/1-4cm-1-digit-7-segment-LED-Geel-SC56-11YWA

      - 4 digit:
        https://www.kiwi-electronics.nl/componenten-onderdelen/leds/led-segmenten/1-4cm-4-Digit-7-Segment-Display-Geel

* High level design:


** StateMachine

Sends to:
- LightsDriver
- StatusDriver

Gets from:
- Button[],
- LightsDriver? (send when all lights are on/off?)

** StatusDriver
- StatusLight[]

Gets from:
- State machine

** LightsDriver

Sends to:
- Light[]
- State machine?

Receives from:
- State machine
