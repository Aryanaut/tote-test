.phony: verify upload

ARDUINO=arduino-1.6.4
ARDUINO_OPTS=--board arduino:avr:pro:cpu=8MHzatmega328 --port /dev/ttyUSB0
SKETCH=start.ino

verify: start.ino
	$(ARDUINO) --verify $(ARDUINO_OPTS) $(SKETCH)

upload: start.ino
	$(ARDUINO) --upload $(ARDUINO_OPTS) $(SKETCH)
