#!/bin/bash
say() { local IFS=+;/usr/bin/mplayer -ao alsa -really-quiet -noconsolecontrols "https://translate.google.com/translate_tts?ie=UTF-8&q=test&tl=en&client=tw-ob"; }
say $*
